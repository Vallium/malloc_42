/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:04:47 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/07 16:08:07 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>
#include <sys/mman.h>
#include <stdlib.h>

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

static int		defrag(t_alloc *this)
{
	this->freed = TRUE;
	if ((this->prev && this->prev->freed) && this->next->freed)
	{
		this->prev->size += this->size + this->next->size + 2 * sizeof(t_alloc);
		if (this->next->last == TRUE)
			this->prev->last = TRUE;
		this->next->next->prev = this->prev;
		this->prev->next = this->next->next;
	}
	else if (this->prev && this->prev->freed)
	{
		this->prev->size += this->size + sizeof(t_alloc);
		this->next->prev = this->prev;
		this->prev->next = this->next;
	}
	else if (!this->last && this->next->freed)
	{
		this->size += this->next->size + sizeof(t_alloc);
		if (this->next->last == TRUE)
			this->last = TRUE;
		this->next = this->next->next;
		this->next->prev = this;
	}
	return (0);
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
	zone->nb_allocs--;
	if (getenv("MallocScribble") != NULL)
		ft_memset((void*)alloc + sizeof(t_alloc), 0x55, alloc->size);
	if (zone->nb_allocs == 0 || defrag(alloc))
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
