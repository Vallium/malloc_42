/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 17:52:05 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/26 18:58:59 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

void	*new_alloc_large(size_t size)
{
	t_zone	*zone;
	t_alloc	*alloc;

	zone = new_zone_large(size);
	alloc = zone->allocs;
	alloc->size = size;
	alloc->freed = FALSE;
	alloc->next = NULL;
	alloc->last = TRUE;
	alloc->zone = zone;
	zone->nb_allocs++;
	return ((void*)alloc + sizeof(t_alloc));
}

void	*new_alloc(size_t size, t_type type)
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
	alloc->zone = zone;
	alloc->next = (void*)alloc + sizeof(t_alloc) + JUMPOF(alloc->size);
	zone->nb_allocs++;
	zone->mem_left -= size + sizeof(t_alloc);
	return ((void*)alloc + sizeof(t_alloc));
}
