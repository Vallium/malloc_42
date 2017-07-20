#include <libft_malloc.h>
#include <stdio.h>
#include <unistd.h>
int		main()
{
	char	*str;
	int		i;

	printf("\n\n\n\n---------------------------------------------------------\n~~ Main Test ~~\n");
	printf("1st Call to malloc:\n");	
	malloc(10);
	printf("\n2nd Call to malloc:\n");	
	malloc(10);
	
	return(0);
}
