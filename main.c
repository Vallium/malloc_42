#include <libft_malloc.h>
#include <stdio.h>
#include <unistd.h>
int		main()
{
	char	*str;
	int		i;

	write(1, "AA", 2);
	malloc(10);
	return 0;
	write(1, "BB", 2);
	i = 0;

	//while(i < 10)
	//	str[i] = 'A' + i, i++;
	//str[i] = 0;

	//printf("%p\n", str);
	return(0);
}
