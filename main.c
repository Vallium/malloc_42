#include "libft_malloc.h"
#include <stdio.h>

int		main()
{
	char	*str;
	int		i;

	printf("----------------------------~~ Main Test ~~-----------------------------\n");
//	malloc(10);
	//malloc(4096);
	//malloc(8192);
	
		malloc(16385);
	for (i = 0; i < 99; i++) {
		malloc(4096);
	}
		malloc(1218);
	for (i = 0; i < 100; i++) {
		malloc(4096*4);
	}
	
	show_alloc_mem();
	return(0);
}
