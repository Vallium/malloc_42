/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 17:27:06 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/26 17:50:53 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"
#include <sys/mman.h>

static void		zone_pushback(t_zone *new)
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

static void		zone_smartpushback(t_zone *new)
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
}

static t_zone	*new_zone(t_type type)
{
	t_zone	*zone;

	if (type == TINY)
	{
		zone = mmap(0, TINY_ZONE_SIZE, MMAP_PROTS, MMAP_MAPS, -1, 0);
		zone->type = TINY;
		zone->mem_left = TINY_ZONE_SIZE - sizeof(t_zone);
	}
	else
	{
		zone = mmap(0, SMALL_ZONE_SIZE, MMAP_PROTS, MMAP_MAPS, -1, 0);
		zone->type = SMALL;
		zone->mem_left = SMALL_ZONE_SIZE - sizeof(t_zone);
	}
	zone->next = NULL;
	zone->allocs = (void*)zone + sizeof(t_zone);
	zone->nb_allocs = 0;
	zone_smartpushback(zone);
	return (zone);
}

t_zone			*new_zone_large(size_t size)
{
	t_zone	*zone;
	size_t	s;

	size = size + sizeof(t_zone) + sizeof(t_alloc);
	s = (size / getpagesize()) + (size % getpagesize() ? 1 : 0);
	zone = mmap(0, s * getpagesize(), MMAP_PROTS, MMAP_MAPS, -1, 0);
	zone->type = LARGE;
	zone->next = NULL;
	zone->allocs = (void*)zone + sizeof(t_zone);
	zone->nb_allocs = 0;
	zone_smartpushback(zone);
	return (zone);
}

t_zone			*find_valid_zone(size_t size, t_type type)
{
	t_zone	*tmp;

	tmp = g_allocs.zones;
	while (tmp)
	{
		if (tmp->type == type && (size + sizeof(t_alloc) <= tmp->mem_left))
			return (tmp);
		tmp = tmp->next;
	}
	return (new_zone(type));
}
