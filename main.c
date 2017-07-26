#include "libft_malloc.h"
#include <stdio.h>

int		main()
{
	int		i;

	printf("----------------------------~~ Main Test ~~-----------------------------\n");
/*	malloc(16385);
	for (i = 0; i < 99; i++) {
		malloc(4096);
	}
	malloc(1218);
	for (i = 0; i < 100; i++) {
		malloc(4096*4);
	}
*/
	void	*ptr = malloc(128);
	void	*ptr2 = malloc(256);
	void	*ptr3 = malloc(512);
	show_alloc_mem();
	printf("-----------------------------");
	free(ptr);
	show_alloc_mem();
	return(0);
}
