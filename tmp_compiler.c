 # include <ft> 
  # define main main2 
  # include "spec.ç" 
  # undef main 
 void compile(const char *src, const char *dst) { int src_fd; int dst_fd; char *src_str; struct stat buf; off_t size; size_t i; printf("Translating %s -> %s\n", src, dst); src_fd = open(src, O_RDONLY); mkpath(dst); dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644); fstat(src_fd, &buf); size = buf.st_size; src_str = malloc(size); read(src_fd, src_str, size); i = 0; while (i < size) { 																		
																											
		rule r_test42 = test42(src_str + i);																		
		if (r_test42.i)																							
		{																									
			printf("Macro rule match at src_str[i=%zu r.s=%s r.i=%i]\n", i,  r_test42.s, r_test42.i);			
			write(dst_fd, r_test42.s, strlen(r_test42.s));															
			i += r_test42.i;																					
			continue ;																						
		}																									
																				
																											
		rule r_test = test(src_str + i);																		
		if (r_test.i)																							
		{																									
			printf("Macro rule match at src_str[i=%zu r.s=%s r.i=%i]\n", i,  r_test.s, r_test.i);			
			write(dst_fd, r_test.s, strlen(r_test.s));															
			i += r_test.i;																					
			continue ;																						
		}																									
																				
																											
		rule r_lol = lol(src_str + i);																		
		if (r_lol.i)																							
		{																									
			printf("Macro rule match at src_str[i=%zu r.s=%s r.i=%i]\n", i,  r_lol.s, r_lol.i);			
			write(dst_fd, r_lol.s, strlen(r_lol.s));															
			i += r_lol.i;																					
			continue ;																						
		}																									
		 write(dst_fd, src_str + i, 1); i += 1; } close(src_fd); close(dst_fd); } int main(int ac, char **av) { if (ac != 3) return (!!printf("Error\nusage: %s <src> <dst>\n", av[0])); compile(av[1], av[2]); return (0); }