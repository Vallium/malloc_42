/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:51:55 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/24 18:21:15 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>
#include <sys/mman.h>
#include <unistd.h>

t_allocs g_allocs = { 
	.nb_zones = 0,
	.zones = NULL
};

void	show_alloc_mem() 
{
	t_zone	*zone;
	t_alloc	*alloc;
	int		total;

	alloc = NULL;
	zone = g_allocs.zones;
	total = 0;
	while (zone)
	{
		if (zone->type == TINY)
			ft_putstr("TINY : ");
		else if (zone->type == SMALL)
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
		ft_putptr(zone);
		ft_putchar('\n');

		alloc = zone->allocs;
		while (alloc->last == FALSE)
		{
			ft_putptr(alloc + sizeof(t_alloc));
			ft_putstr(" - ");
			ft_putptr(alloc + sizeof(t_alloc) + alloc->size * sizeof(char));
			ft_putstr(" : ");
			ft_putnbr(alloc->size);
			ft_putstr(alloc->size > 1 ? " octets\n" : " octet\n");
			total += alloc->size;
			alloc = alloc->next;
		}
		ft_putptr(alloc + sizeof(t_alloc));
		ft_putstr(" - ");
		ft_putptr(alloc + sizeof(t_alloc) + alloc->size * sizeof(char));
		ft_putstr(" : ");
		ft_putnbr(alloc->size);
		ft_putstr(alloc->size > 1 ? " octets\n" : " octet\n");
		total += alloc->size;
		zone = zone->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(total ? " octets\n" : " octet\n");
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
}

t_zone		*new_zone(e_type type)
{
	t_zone	*zone;

	if (type == TINY)
	{
		zone = mmap(0, TINY_ZONE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		zone->type = TINY;
		zone->mem_left = (char)TINY_ZONE_SIZE - sizeof(t_zone);
	}
	else
	{
		zone = mmap(0, SMALL_ZONE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		zone->type = SMALL;
		zone->mem_left = (char)SMALL_ZONE_SIZE - sizeof(t_zone);
	}
	zone->next = NULL;
	zone->allocs = (void*)zone + sizeof(t_zone);
	zone->nb_allocs = 0;
	zone_smartpushback(zone);
	return (zone);
}

void	*new_zone_large(int	size)
{
	t_zone	*zone;
	int		s;

	size = size + sizeof(t_zone) + sizeof(t_alloc);
	s = (size / getpagesize()) + (size % getpagesize() ? 1 : 0);
	zone = mmap(0, s * getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	zone->type = LARGE;
	zone->next = NULL;
	zone->allocs = (void*)zone + sizeof(t_zone);
	zone->nb_allocs = 0;
	zone_smartpushback(zone);
	return (zone);
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

void	*alloc_large(int size)
{
	t_zone	*zone;
	t_alloc	*alloc;
	
	zone = new_zone_large(size);
	alloc = zone->allocs;
	alloc->size = size;
	alloc->freed = FALSE;
	alloc->next = NULL;
	zone->nb_allocs++;
	return (alloc + sizeof(t_alloc));
}

#include <stdlib.h>

void	*find_valid_zone(int size, e_type type)
{
	t_zone	*tmp;

	tmp = g_allocs.zones;
	while (tmp)
	{
		if (tmp->type == type && ((int)(size * sizeof(char) + sizeof(t_alloc)) <= tmp->mem_left))
			return (tmp);
		tmp = tmp->next;
	}
	return (new_zone(type));
}

void	*alloc(int size, e_type type)
{
	t_zone	*zone;
	t_alloc	*alloc;

	zone = find_valid_zone(size, type);
	alloc = zone->allocs;
	if (zone->nb_allocs)
	{
		while (alloc->last == FALSE)
			alloc = alloc->next;
		alloc->last = FALSE;
		alloc = alloc + sizeof(t_alloc) + JUMPOF(alloc->size);
		alloc->last = TRUE;
	}
	else
		alloc->last = TRUE;
	alloc->size = size;
	alloc->freed = FALSE;
	alloc->next = alloc + sizeof(t_alloc) + JUMPOF(alloc->size);
	zone->nb_allocs++;
	zone->mem_left -= size + sizeof(t_alloc);
	return (alloc + sizeof(t_alloc));
}

void	*new_alloc(int size, e_type type)
{
	void	*ret;

	ret = NULL;
	if (type == LARGE)
		ret = alloc_large(size);
	else
		ret = alloc(size, type);
	return ret;
}

void	*malloc(size_t size)
{
	void	*ret;

	//ret = alloc(size, TINY);
	//show_alloc_mem();
	ft_putstr("\n-----------------------------------------------------\n");
	//if (g_allocs.zones->nb_allocs == 16)
	//	exit(0);
	//return ret;

	if (size <= TINY_MAX_SIZE)	
		ret = new_alloc((int)size, TINY);
	else if (size <= SMALL_MAX_SIZE)
		ret = new_alloc((int)size, SMALL);
	else
		ret = new_alloc((int)size, LARGE);
	show_alloc_mem();
	return (ret);
}