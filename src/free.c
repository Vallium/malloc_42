/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:04:47 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/26 19:28:41 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>
#include <sys/mman.h>

void	free(void *ptr)
{
	t_alloc	*alloc;
	t_zone	*zone;

	alloc = ptr - JUMPOF(sizeof(t_alloc));
	zone = alloc->zone;
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("ptr: ");
	ft_putptr(ptr);
	ft_putstr(" | alloc: ");
	ft_putptr(alloc);
	ft_putstr(" | zone: ");
	ft_putptr(zone);
	ft_putchar('\n');
	ft_putchar('\n');
	//alloc->freed = TRUE;

	/*zone->nb_allocs--;
	if (zone->nb_allocs == 0)
	{
		if (zone->type == TINY)
			munmap(zone, TINY_ZONE_SIZE);
	}*/
}
