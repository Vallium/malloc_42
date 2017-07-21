/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:51:55 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/21 16:59:10 by aalliot          ###   ########.fr       */
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

void	alloc_pushback(t_alloc **start, t_alloc *new)
{
	t_alloc	*alloc;

	alloc = *start;
	if (!(*start))
		*start = new;
	else
	{
		while (alloc->next)
			alloc = alloc->next;
		alloc->next = new;
	}
}

t_zone		*new_zone(e_type type)
{
	t_zone	*zone;

	if (type == TINY)
	{
		zone = mmap(0, TINY_ZONE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		zone->type = TINY;
		zone->mem_left = TINY_ZONE_SIZE - sizeof(t_zone);
	}
	else
	{
		zone = mmap(0, SMALL_ZONE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		zone->type = SMALL;
		zone->mem_left = SMALL_ZONE_SIZE - sizeof(t_zone);
	}
	zone->next = NULL;
	zone->allocs = (void*)zone + sizeof(t_zone);
	zone_smartpushback(zone);
	return (zone);
}

void	*new_zone_large(int	size)
{
	t_zone	*zone;

	(void)size;
	zone = mmap(0, 10 * getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	zone->type = LARGE;
	zone->next = NULL;
	zone->allocs = (void*)zone + sizeof(t_zone);
	zone_smartpushback(zone);
	return (zone);
}

void	*alloc_large(int size)
{
	t_zone	*zone;
	t_alloc	*alloc;
	
	zone = new_zone_large(size);
	
	return (ret);
}

void	*new_alloc(int size, e_type type)
{
	if (type == LARGE)
	{
		alloc_large(size);
	}
	return NULL;
}

void	*alloc(int size, e_type type)
{

}

void	*malloc(size_t size)
{
	void	*ret;

	if ((int)size <= TINY_MAX_SIZE)	
		ret = alloc((int)size, TINY);
	else if ((int)size <= SMALL_MAX_SIZE)
		ret = alloc((int)size, SMALL);
	else
		ret = alloc((int)size, LARGE);
	return (ret);
}
