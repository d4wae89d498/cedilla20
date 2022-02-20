#include <ft>

void	compile(const char *src, const char *dst)
{
	int			src_fd;
	int			dst_fd;
	char		*src_str;
	char		*macro_rules;
	char		*macro_sequence;
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
/*
 *	find all macros def, generate a true name, count 'em,
 *
 *	generate a call sequence
 *
 *
 *
 */
		i += 1;
	}
	macro_rules = "";
	dprintf
	(
	 	dst_fd,
	 	_(
/*
 *============================================================
 *	B E G I N   O F   G E N E R A T E D   S E C T I O N
 *============================================================
 */
\x23include <ft>\n

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
	 	macro_rules, macro_sequence
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
