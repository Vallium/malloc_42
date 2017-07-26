/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 16:55:28 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/26 17:14:39 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static void		print_alloc(t_alloc *alloc)
{
	ft_putptr((char*)alloc + sizeof(t_alloc));
	ft_putstr(" - ");
	ft_putptr((char*)alloc + sizeof(t_alloc) + JUMPOF(alloc->size));
	ft_putstr(" : ");
	ft_putnbr(alloc->size);
	ft_putstr(alloc->size > 1 ? " octets\n" : " octet\n");
}

static void		print_zone_type(e_type type)
{
	if (type == TINY)
		ft_putstr("TINY : ");
	else if (type == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
}

static void		print_total(size_t total)
{
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(total ? " octets\n" : " octet\n");
}

void			show_alloc_mem(void)
{
	t_zone	*zone;
	t_alloc	*alloc;
	size_t	total;

	zone = g_allocs.zones;
	total = 0;
	while (zone)
	{
		print_zone_type(zone->type);
		ft_putptr(zone);
		ft_putchar('\n');
		alloc = zone->allocs;
		while (alloc->last == FALSE)
		{
			if (alloc->freed == TRUE)
				continue;
			print_alloc(alloc);
			total += alloc->size;
			alloc = alloc->next;
		}
		print_alloc(alloc);
		total += alloc->size;
		zone = zone->next;
	}
	print_total(total);
}
