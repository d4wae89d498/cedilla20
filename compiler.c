#include <ft>


int	is_token(int remaining, char *begin, char *word)
{
	int	i;

	i = 0;
	while (remaining > i && word[i] && begin[i] == word[i])
		i += 1;
	if (!word[i])
		return (1);
	return (0);
}

int	is_word(int remaining, char *begin, char *word)
{
	int	i;

	i = 0;
	while (remaining > i && word[i] && begin[i] == word[i])
		i += 1;
	if (!word[i] && !isalpha(begin[i]))
		return (1);
	return (0);
}

typedef struct s_macros
{
	char			*data;
	struct s_macros	*next;
}	t_macros;

t_macros	*parse(const char *path)
{
	char		*src_str			;
	struct stat buf					;
	off_t		size				;
	size_t		i					;
	size_t		remaining			;
	struct
	{
		int	parentheses				:16;
		int	brackets				:16;
		int	braces					:16;
		int	lines					:16;
		int	cols					:16;
	}			level = {0,0,0,1,1};
	struct
	{
		int	comment					:1;
		int	comments				:1;
		int	quote					:1;
		int	quotes					:1;
		int	escaped					:1;
		int	cpp						:1;
		int	rule					:1;
		/**
		 *	macro -> -1
		 *	macro rules -> 1
		 */
		int	macro					:2;
	}			is = {0, 0, 0, 0, 0, 0, 0, 0};
	int			src_fd;
	t_macros	*macros;
	char		macro_name[1024];
	size_t		macro_name_i;

	printf("parsing: %s...\n", path);
	macros = 0;
	src_fd = open(path, O_RDONLY);
	fstat(src_fd, &buf);
	size = buf.st_size;
	src_str = malloc(size);
	read(src_fd, src_str, size);
	i = 0;
	while (i < size)
	{
		remaining = size - i;
		if (is.macro == 1)
		{
			macro_name[macro_name_i] = src_str[i];
			if (src_str[i] == '(')
			{
				macro_name[macro_name_i] = 0;	
				is.macro = 0;
				list_add(&macros, strdup(macro_name));
			}
			else
				macro_name_i += 1;
		}


		if (src_str[i] == '\n')
		{
			if (!is.escaped)
			{
				level.cols = 1;
				level.lines += 1;
				is.comment = 0;
				is.quote = 0;
				is.cpp = 0;
			}
		}
		else if (src_str[i] == '\\')
			is.escaped = 1;
		else if (src_str[i] == '(' && !is.quote && !is.quotes && !is.comment && !is.comments)
		{
			if (is.macro && !level.parentheses)
				is.macro = 0;
			level.parentheses += 1;
		}
		else if (src_str[i] == '[' && !is.quote && !is.quotes && !is.comment && !is.comments)
			level.brackets += 1;
		else if (src_str[i] == '{' && !is.quote && !is.quotes && !is.comment && !is.comments)
			level.braces += 1;
		else if (src_str[i] == ')' && !is.quote && !is.quotes && !is.comment && !is.comments)
			level.parentheses -= 1;
		else if (src_str[i] == ']' && !is.quote && !is.quotes && !is.comment && !is.comments)
			level.brackets -= 1;
		else if (src_str[i] == '}' && !is.quote && !is.quotes && !is.comment && !is.comments)
			level.braces -= 1;
		else if (src_str[i] == '#' &&
				!is.comment && !is.comments && !is.quote && !is.quotes)
		{	
			is.cpp = 1;
		}
		else if (src_str[i] == '\'' && !is.escaped && !is.quote && !is.quotes && is.comment && !is.comments)
			is.quote = 1;
		else if (src_str[i] == '"'  && !is.escaped && !is.quote && !is.quotes && is.comment && !is.comments)
			is.quotes = 1;
		else if (is_token(remaining, src_str + i, "//") && !is.comment && !is.quote && !is.quotes && !is.comments)
			is.comment = 1;
		else if (is_token(remaining, src_str + i, "/*") && !is.comment && !is.quote && !is.quotes && !is.comments)
			is.comments = 1;
		else if (is_token(remaining, src_str + i, "*/") && is.comments)
			is.comments = 0;
		else if (is_word(remaining, src_str + i, "macro"))
		{
			is.macro = -1;
		}
		else if (
				is.macro == -1
				&&	is_word(remaining, src_str + i, "rule")
				&& !is.comment && !is.comments && !is.quote && !is.quotes)
		{
			i += 4;
			macro_name_i = 0;	
			is.macro = 1;
		}
		else if (is.cpp && is_token(remaining, src_str + i, "import"))
		{
			t_macros	*tmp;
			char		import_buffer[1024];
			int			y;
			int			p;

			i += 6;
			remaining -= 6;
			y = 0;
			p = 0;
			while (remaining)
			{
				if (src_str[i] == '<' || src_str[i] == '"')
					p = 1;
				else if (p && src_str[i] == '>' || src_str[i] == '"')
					break ;	
				else if (p)
					import_buffer[y++] = src_str[i];
				remaining -= 1;
				i += 1;
			}
			import_buffer[y + 1] = 0;
			printf("import=%s\n", import_buffer);
			tmp = parse(import_buffer);
			while(tmp)
			{
				list_add(&macros, tmp->data);
				tmp = tmp->next;
			}
			list_clear((void*)&tmp, 0);
		}
		if (!(src_str[i] == '\n') && !is.escaped)
			level.cols += 1;
		i += 1;
	}
	close(src_fd);
	return (macros);
}

static void	list_macros(t_macros *macros)
{
	while (macros)
	{
		printf("-- macro rule: %s (char*, size_t);\n", macros->data);
		macros = macros->next;
	}
}

void	compile(const char *src, const char *dst)
{
	int			dst_fd;
	t_macros	*macros;

	macros = parse(src);
	list_macros(macros);
	mkpath(dst);
	dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dprintf
	(
	 	dst_fd,
	 	_(
/*
 *============================================================
 *	B E G I N   O F   G E N E R A T E D   S E C T I O N
 *============================================================
 */
\n\x23 include <ft>\n

%s

void	compile(const char *src, const char *dst)
{
	int			src_fd;
	int			dst_fd;
	char		*src_str;
	struct stat buf;
	off_t		size;
	size_t		i;

	src_fd = open(src, O_RDONLY);
	mkpath(dst);
	dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fstat(src_fd, &buf);
	size = buf.st_size;
	src_str = malloc(size);
	read(src_fd, src_str, size);
	i = 0;
	while (i < size)
	{
		%s
		i += 1;
	}
	/* 
 	 *
 	 *	at each index, try a macro 
 	 *
 	 * for each i 
 	 * 		for each macros
 	 *
 	 *			if macro ret != 0
 	 *				replace match, and retry on same index
 	 *			else
 	 *				try an other macro
	 *
	 *	reset counter and repeat until no more change or deepth max
 	 *
 	 */
\n\x23 define P _\n
	dprintf
	(
	 	dst_fd,
		P(
			\\x23include <ft>\\x20 \\n


			%%s

			int main()
			{
				printf("ok!\n");
			}
		),
		""
	);

	close(src_fd);
	close(dst_fd);
}

int		main(int ac, char **av)
{
	if (ac != 3)
		return (!!printf("Error\nusage: %%s <src> <dst>\n", av[0]));
	compile(av[1], av[2]);
		

	return (0);
/*
 *============================================================
 *	E N D   O F   G E N E R A T E D   S E C T I O N
 *============================================================
 */
}
		), 
	 	"", ""
	);

	close(dst_fd);
}

int		main(int ac, char **av)
{
	if (ac  != 3)
		return (!!printf("Error: usage %s <source.ç> <dest.c>\n", av[0]));
	compile(av[1], av[2]);
	return (0);
}
