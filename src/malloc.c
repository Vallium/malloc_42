/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:51:55 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/20 18:51:04 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>
#include <sys/mman.h>
#include <unistd.h>

t_allocs g_allocs = { 
	.nb_zones = 0,
	.zones = NULL
};

void	print_zones() 
{
	t_zone *zone;

	zone = g_allocs.zones;
	while (zone->next)
	{
		ft_putptr(zone);
		ft_putchar(' ');
		zone = zone->next;
	}
	ft_putstr("\n\n----------------------------\n\n");
}

void	zone_pushback(t_zone *new)
{
	t_zone	*zone;

	zone = g_allocs.zones;
	if (!(g_allocs.zones))
		g_allocs.zones = new;
	else
	{
		while (zone->next)
			zone = zone->next;
		zone->next = new;
	}
}

void	zone_smartpushback(t_zone *new)
{
	static t_zone	*zonestart = NULL;
	static t_zone	*zoneend = NULL;

	if (zonestart && g_allocs.zones == zonestart)
	{
		zoneend->next = new;
		zoneend = new;
	}
	else
	{
		zone_pushback(new);
		zonestart = g_allocs.zones;
		zoneend = new;
	}
	print_zones();
}

void	*new_zone(size_t size)
{
	t_zone	*zone;

	if ((int)size <= TINY_MAX_SIZE)
		zone = mmap(0, TINY_ZONE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else if ((int)size <= SMALL_MAX_SIZE)
		zone = mmap(0, SMALL_ZONE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else
		zone = mmap(0, (10 * getpagesize()), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	
	zone->type = TINY;
	zone->allocs = NULL;
	zone->next = NULL;

	zone_smartpushback(zone);
	return (zone + sizeof(t_zone));
}

void	*malloc(size_t size)
{
	void *ret = new_zone(size);

	return (ret);
}
