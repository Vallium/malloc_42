#include "libft_malloc.h"
//#include <stdio.h>

int		main()
{
	int		i;

	//printf("----------------------------~~ Main Test ~~-----------------------------\n");
/*	malloc(16385);
	for (i = 0; i < 99; i++) {
		malloc(4096);
	}
	malloc(1218);
	for (i = 0; i < 100; i++) {
		malloc(4096*4);
	}
*/
	void	*ptr1 = malloc(100);
	void	*ptr2 = malloc(200);
	void	*ptr3 = malloc(300);
	void	*ptr4 = malloc(400);
	void	*ptr5 = malloc(500);
	void	*ptr6 = malloc(6);
	void	*ptr7 = malloc(7);
	void	*ptr8 = malloc(8);
	void	*ptr9 = malloc(9);
	
	show_alloc_mem();
	ft_putchar('\n');
	show_freed_mem();
	ft_putchar('\n');

	free(ptr2);
	
	show_alloc_mem();
	ft_putchar('\n');
	show_freed_mem();
	ft_putchar('\n');

	//ptr1 = malloc(87);
	free(ptr3);

	show_alloc_mem();
	ft_putchar('\n');
	show_freed_mem();
	ft_putchar('\n');
	
	//malloc(58);
	free(ptr5);
	
	///ptr1 = malloc(32768);
	//malloc(57);	
	
	show_alloc_mem();
	ft_putchar('\n');
	show_freed_mem();
	ft_putchar('\n');

//	free(ptr9);
//	free(ptr8);
//	free(ptr7);
//	free(ptr6);
//	free(ptr6);
//	free(ptr4);
//	free(ptr5);
//	free(ptr3);
//	free(ptr1);
//	free(ptr2);

//	malloc(127);	

//	show_alloc_mem();
//	show_freed_mem();
	return(0);
}
