/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 17:52:05 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/04 11:47:16 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

static t_alloc		*ret_alloc(t_alloc **alloc, t_zone **zone)
{
	(*zone)->nb_allocs++;
	(*alloc)->freed = FALSE;
	return (*alloc);
}

static t_alloc		*find_place_to_alloc(size_t size, t_type type)
{
	t_zone	*zone;
	t_alloc	*alloc;

	zone = g_allocs.zones;
	while (zone)
	{
		if (zone->type == type)
		{
			alloc = zone->allocs;
			while (alloc->last == FALSE)
			{
				if (alloc->freed == TRUE && alloc->size >= size)
					return (ret_alloc(&alloc, &zone));
				alloc = alloc->next;
			}
			if (alloc->freed == TRUE && alloc->size >= size)
				return (ret_alloc(&alloc, &zone));
		}
		zone = zone->next;
	}
	return (NULL);
}

void				*new_alloc_large(size_t size)
{
	t_zone	*zone;
	t_alloc	*alloc;

	zone = new_zone_large(size);
	alloc = zone->allocs;
	alloc->a = A_MAGIC;
	alloc->b = B_MAGIC;
	alloc->size = size;
	alloc->freed = FALSE;
	alloc->next = NULL;
	alloc->prev = NULL;
	alloc->last = TRUE;
	alloc->zone = zone;
	zone->nb_allocs++;
	return ((void*)alloc + sizeof(t_alloc));
}

void				*new_alloc(size_t size, t_type type)
{
	t_zone	*zone;
	t_alloc	*alloc;
	t_alloc *tmp;

	if ((alloc = find_place_to_alloc(size, type)))
		return ((void*)alloc + sizeof(t_alloc));
	zone = find_valid_zone(size, type);
	if ((alloc = zone->allocs) && zone->nb_allocs)
	{
		while (alloc->last == FALSE)
			alloc = alloc->next;
		alloc->last = FALSE;
		tmp = alloc;
		alloc = alloc->next;
		alloc->prev = tmp;
		alloc->last = TRUE;
	}
	else
	{
		alloc->last = TRUE;
		alloc->prev = NULL;
	}
	alloc->a = A_MAGIC;
	alloc->b = B_MAGIC;
	alloc->size = size;
	alloc->freed = FALSE;
	alloc->zone = zone;
	alloc->next = (void*)alloc + sizeof(t_alloc) + JUMPOF(alloc->size);
	zone->nb_allocs++;
	zone->mem_left -= size + sizeof(t_alloc);
	return ((void*)alloc + sizeof(t_alloc));
}
