/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 15:42:44 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/07 15:43:01 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>

static void		print_alloc(t_alloc *alloc)
{
	ft_putptr((char*)alloc + sizeof(t_alloc));
	ft_putstr(" - ");
	ft_putptr((char*)alloc + sizeof(t_alloc) + JUMPOF(alloc->size));
	ft_putstr(" : ");
	ft_putnbr(alloc->size);
	ft_putstr(alloc->size > 1 ? " octets\n" : " octet\n");
}

static void		print_zone(t_zone *zone)
{
	if (zone->type == TINY)
		ft_putstr("TINY : ");
	else if (zone->type == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	ft_putptr(zone);
	ft_putchar('\n');
}

static void		print_total(size_t total)
{
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(total ? " octets\n" : " octet\n");
}

void			print_mem(t_bool freed)
{
	t_zone	*zone;
	t_alloc	*alloc;
	size_t	total;

	zone = g_allocs.zones;
	total = 0;
	while (zone && (alloc = zone->allocs))
	{
		print_zone(zone);
		while (alloc->last == FALSE)
		{
			if (alloc->freed == freed)
			{
				print_alloc(alloc);
				total += alloc->size;
			}
			alloc = alloc->next;
		}
		alloc->freed == freed ? print_alloc(alloc) : 0;
		total += alloc->freed == freed ? alloc->size : 0;
		zone = zone->next;
	}
	print_total(total);
}
