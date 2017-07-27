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
	void	*ptr1 = malloc(128);
	void	*ptr2 = malloc(256);
	void	*ptr3 = malloc(512);
	void	*ptr4 = malloc(4097);
	void	*ptr5 = malloc(4097);
	void	*ptr6 = malloc(4097);
	void	*ptr7 = malloc(4096 * 4 + 1);
	void	*ptr8 = malloc(4096 * 4 + 1);
	void	*ptr9 = malloc(4096 * 4 + 1);
	show_alloc_mem();
	free(ptr9);
	free(ptr8);
	free(ptr7);
	free(ptr5);
	free(ptr2);
	free(ptr4);
	free(ptr1);
	free(ptr3);
	free(ptr6);
	
	show_alloc_mem();
	return(0);
}
