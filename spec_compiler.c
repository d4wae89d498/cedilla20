
# include <ft>
  void compile(const char *src, const char *dst) { int src_fd; int dst_fd; char *src_str; struct stat buf; off_t size; size_t i; src_fd = open(src, O_RDONLY); mkpath(dst); dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644); fstat(src_fd, &buf); size = buf.st_size; src_str = malloc(size); read(src_fd, src_str, size); i = 0; while (i < size) {  i += 1; } 
# define P _
 dprintf ( dst_fd, P( \x23include <ft>\x20 \n %s int main() { printf("ok!\n"); } ), "" ); close(src_fd); close(dst_fd); } int main(int ac, char **av) { if (ac != 3) return (!!printf("Error\nusage: %s <src> <dst>\n", av[0])); compile(av[1], av[2]); return (0); }