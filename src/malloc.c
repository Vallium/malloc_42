/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:51:55 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/26 17:27:26 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

t_allocs g_allocs = { 
	.nb_zones = 0,
	.zones = NULL
};

void	*new_alloc_large(int size)
{
	t_zone	*zone;
	t_alloc	*alloc;
	
	zone = new_zone_large(size);
	alloc = zone->allocs;
	alloc->size = size;
	alloc->freed = FALSE;
	alloc->next = NULL;
	alloc->last = TRUE;
	zone->nb_allocs++;
	return (alloc + sizeof(t_alloc));
}

void	*find_valid_zone(size_t size, e_type type)
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

void	*new_alloc(size_t size, e_type type)
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
		alloc = alloc->next;
		alloc->last = TRUE;
	}
	else
		alloc->last = TRUE;
	alloc->size = size;
	alloc->freed = FALSE;
	alloc->next = (void*)alloc + sizeof(t_alloc) + JUMPOF(alloc->size);
	zone->nb_allocs++;
	zone->mem_left -= size + sizeof(t_alloc);
	return (alloc + sizeof(t_alloc));
}

void	*malloc(size_t size)
{
	void	*ret;

	if (size <= TINY_MAX_SIZE)	
		ret = new_alloc(size, TINY);
	else if (size <= SMALL_MAX_SIZE)
		ret = new_alloc(size, SMALL);
	else
		ret = new_alloc_large(size);
	return (ret);
}
