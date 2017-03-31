#include <libft_malloc.h>
#include <stdio.h>

int		main()
{
	char	*str;
	int		i;

	str = (char*)malloc(sizeof(char) * 10);
	i = 0;

	while(i < 10)
		str[i++] = '#';
	str[i] = 0;

	printf("%s\n", str);
	return(0);
}
