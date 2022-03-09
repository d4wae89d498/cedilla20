#include <ft>
#ifndef MACRO_SIZE
# define MACRO_SIZE 1024
#endif
#ifndef IMPORT_SIZE
# define IMPORT_SIZE 1024
#endif

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
		int	amacro					:2;
	}			is = {0, 0, 0, 0, 0, 0, 0, 0};
	int			src_fd;
	t_macros	*macros;
	char		macro_name[MACRO_SIZE];
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
		if (is.amacro == 1)
		{
			if (macro_name_i < MACRO_SIZE)
			{
				macro_name[macro_name_i] = src_str[i];
				if (src_str[i] == '(')
				{
					macro_name[macro_name_i] = 0;	
					is.amacro = 0;
					list_add(&macros, strdup(macro_name));
				}
				else
					macro_name_i += 1;
			}
			else
			{
				is.amacro = 0;
				printf("%s:%i:%i: Error - macro name can not be longer than %i characters.\n", 
				path, level.lines, level.cols, MACRO_SIZE);
			}
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
			if (is.amacro && !level.parentheses)
				is.amacro = 0;
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
			is.amacro = -1;
		}
		else if (
				is.amacro == -1
				&&	is_word(remaining, src_str + i, "rule")
				&& !is.comment && !is.comments && !is.quote && !is.quotes)
		{
			i += 4;
			macro_name_i = 0;	
			is.amacro = 1;
		}
		else if (is.cpp && is_token(remaining, src_str + i, "import"))
		{
			t_macros	*tmp;
			char		import_buffer[IMPORT_SIZE + 1];
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
				else if (p && (src_str[i] == '>' || src_str[i] == '"'))
					break ;	
				else if (p && y < (IMPORT_SIZE - 1))
					import_buffer[y++] = src_str[i];
				else if (y >= (IMPORT_SIZE - 1))
				{
					printf("%s:%i:%i: Error - import statement can not be longer than %i characters.\n", 
					path, level.lines, level.cols, MACRO_SIZE);
					y = -1;
					break ;
				}
				remaining -= 1;
				i += 1;
			}
			if (y >= 0)
			{
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
		printf("-- macro rule: %s;\n", macros->data);
		macros = macros->next;
	}
}

void	compile(const char *src, const char *dst)
{
	int			dst_fd;
	t_macros	*macros;
	t_macros	*it;
	char		*macro_engine;

	char		*macro_engine_swp;

	macros = parse(src);
	list_macros(macros);
	printf("generating intermediate compiler: %s...\n", dst);

	macro_engine = 0;
	it = macros;
	while (it)
	{
		asprintf(&macro_engine_swp, "%s																		\n\
																											\n\
		rule r_%s = %s(src_str + i);																		\n\
		if (r_%s.i)																							\n\
		{																									\n\
			printf(\"Macro rule match at src_str[i=%%zu r.s=%%s r.i=%%i]\\n\", i,  r_%s.s, r_%s.i);			\n\
			write(dst_fd, r_%s.s, strlen(r_%s.s));															\n\
			i += r_%s.i;																					\n\
			continue ;																						\n\
		}																									\n\
		", macro_engine ? macro_engine : "" , 
		it->data, it->data, it->data, it->data, it->data, it->data, it->data, it->data);
		free(macro_engine);
		macro_engine = macro_engine_swp;
		it = it->next;
	}

	mkpath(dst);
	dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dprintf
	(
	 	dst_fd,
	 	__(
/*
 *============================================================
 *	B E G I N   O F   G E N E R A T E D   S E C T I O N
 *============================================================
 */

\x20\x23 include <ft>		\n
\x20\x23 define main main2	\n
\x20\x23 include "%s"		\n
\x20\x23 undef main			\n

void	compile(const char *src, const char *dst)
{
	int			src_fd;
	int			dst_fd;
	char		*src_str;
	struct stat buf;
	off_t		size;
	size_t		i;


	printf("Translating %%s -> %%s\n", src, dst);
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
		write(dst_fd, src_str + i, 1);
		i += 1;
	}
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
		), src, macro_engine 
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
