#include <ft>

typedef struct macros
{
	int x;
}	t_macros;

t_macros	parse(const char *src)
{
	char		*str				;
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
		int	cols					:16
	}			level = {0,0,0,0, 0};
	struct
	{
		int	comment					:1;
		int	comments				:1;
		int	quote					:1;
		int	quotes					:1;
		int	escaped					:1;
		int	cpp						:1;
		int	rule					:1;
	}			is = {0, 0, 0, 0, 0, 0, 0};

	src_fd = open(src, O_RDONLY);
	fstat(src_fd, &buf);
	size = buf.st_size;
	str = malloc(size);
	read(src_fd, src_str, size);
	i = 0;
	while (i < size)
	{
		remaining = size - i;
		if (ctx.macro)+


		if (str[i] == '\n')
		{
			if (!is.escaped)
			{
				first_of_line = 1;
				is.comment = 0;
				is.quote = 0;
				is.cpp = 0;
			}
		}
		else if (str[i] == '\\')
			is.escaped = 1;
		else if (str[i] == '(' && !is.quote && !is.quotes && !is.comment && !is.comments)
			ctx.parentheses_level += 1;
		else if (str[i] == '[' && !is.quote && !is.quotes && !is.comment && !is.comments)
			ctx.brackets_level += 1;
		else if (str[i] == '{' && !is.quote && !is.quotes && !is.comment && !is.comments)
			ctx.braces += 1;
		else if (str[i] == ')' && !is.quote && !is.quotes && !is.comment && !is.comments)
			ctx.parentheses_level -= 1;
		else if (str[i] == ']' && !is.quote && !is.quotes && !is.comment && !is.comments)
			ctx.brackets_level -= 1;
		else if (str[i] == '}' && !is.quote && !is.quotes && !is.comment && !is.comments)
		{
			ctx.braces -= 1;
			if (!ctx.braces)
				is.macro = 0;
		}
		else if (!level.lines && str[i] == '#' && 
				!comment && !comments && !quote && !quotes)
			is.cpp = 1;
		else if (str[i] == '\'' && !is.escaped && !is.quote && !is.quotes && is.comment && !is.comments)
			is.quote = 1;
		else if (str[i] == '"'  && !is.escaped && !is.quote && !is.quotes && is.comment && !is.comments)
			is.quotes = 1;
		else if (remaing > 2 && !strcmp(str + i, "//") && !is.comment && !is.quote && !is.quotes && !is.comments)
			is.comment = 1;
		else if (!strcmp(str + i, "/*") && !is.comment && !is.quote && !is.quotes && !is.comments)
			is.comments = 1;
		else if (!strcmp(str + i, "*/") && is.comments)
			is.comments = 0;
	//	else if (remaining > 5 && !strcmp(str + i, "macro"))
//		{
//		}
		else if (remaining > 5 && !strcmp(str + i, "rule") && !ctx.comment && !ctx.comments && !ctx.quote && !ctx.quotes)
		{
			is.macro = 1;
		}
		else if (is.cpp && remaining > 6 && 
				!strcmp(str + i, "import"))
		{}
		first_of_line = 0;
		i += 1;
	} 
	return ((t_macros) {0});
}

void	compile(const char *src, const char *dst)
{
	int			dst_fd;
	t_macros	macros;

	mkpath(dst);
	dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dprintf
	(
	 	dst_fd,
	 	_(
\x23line 115 compiler.c\n\
			/*
 *============================================================
 *	B E G I N   O F   G E N E R A T E D   S E C T I O N
 *============================================================
 */
\x23include <ft>\n

%s
\x23line 124 compiler.c\n\

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

	close(src_fd);
	close(dst_fd);
}

int		main(int ac, char **av)
{
	if (ac  != 3)
		return (!!printf("Error: usage %s <source.ç> <dest.c>\n", av[0]));
	compile(av[1], av[2]);
	return (0);
}
