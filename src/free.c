/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:04:47 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/03 17:31:10 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>
#include <sys/mman.h>

static void		delete_zone(t_zone **zone)
{
	if (*zone == g_allocs.zones)
	{
		if ((*zone)->next != NULL)
			(*zone)->next->prev = NULL;
		else
			(*zone)->next = NULL;
		g_allocs.zones = (*zone)->next;
	}
	else if ((*zone)->next == NULL)
		(*zone)->prev->next = NULL;
	else
	{
		(*zone)->next->prev = (*zone)->prev;
		(*zone)->prev->next = (*zone)->next;
	}
}

void			free(void *ptr)
{
	t_alloc	*alloc;
	t_zone	*zone;

	pthread_mutex_lock(mutex_sglton());
	if (ptr == NULL)
		return ((void)pthread_mutex_unlock(mutex_sglton()));
	alloc = (t_alloc*)(ptr - JUMPOF(sizeof(t_alloc)));
	if (alloc->a != A_MAGIC || alloc->b != B_MAGIC)
		return ((void)pthread_mutex_unlock(mutex_sglton()));
	zone = alloc->zone;
	alloc->freed = TRUE;
	zone->nb_allocs--;
	if (zone->nb_allocs == 0)
	{
		delete_zone(&zone);
		if (zone->type == TINY)
			munmap(zone, TINY_ZONE_SIZE);
		else if (zone->type == SMALL)
			munmap(zone, SMALL_ZONE_SIZE);
		else
			munmap(zone, sizeof(t_zone) + \
					sizeof(t_alloc) + JUMPOF(zone->allocs->size));
	}
	pthread_mutex_unlock(mutex_sglton());
}
