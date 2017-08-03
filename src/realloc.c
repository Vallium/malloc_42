/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:05:37 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/03 17:33:05 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>
#include <sys/mman.h>

static void		*realloc_new(void **ptr, t_alloc *alloc, size_t size)
{
	void	*ret;

	pthread_mutex_unlock(mutex_sglton());
	ret = malloc(size);
	pthread_mutex_lock(mutex_sglton());
	ft_memcpy(ret, *ptr, alloc->size);
	pthread_mutex_unlock(mutex_sglton());
	free(*ptr);
	pthread_mutex_lock(mutex_sglton());
	return (ret);
}

static void		realloc_same_place(t_alloc **alloc, t_zone **zone, size_t size)
{
	(*alloc)->size = size;
	(*alloc)->next += JUMPOF(size - (*alloc)->size);
	(*zone)->mem_left -= size - (*alloc)->size;
}

static void		*return_ptr(void *ptr)
{
	pthread_mutex_unlock(mutex_sglton());
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	t_alloc	*alloc;

	if (ptr == NULL)
		return (malloc(size));
	pthread_mutex_lock(mutex_sglton());
	if (size == 0)
	{
		pthread_mutex_unlock(mutex_sglton());
		free(ptr);
		pthread_mutex_lock(mutex_sglton());
		return (return_ptr(NULL));
	}
	alloc = (t_alloc*)(ptr - JUMPOF(sizeof(t_alloc)));
	if (alloc->a != A_MAGIC || alloc->b != B_MAGIC)
		return (return_ptr(NULL));
	zone = alloc->zone;
	if (size <= alloc->size)
		alloc->size = size;
	else if (alloc->last == TRUE && (size - alloc->size) <= zone->mem_left)
		realloc_same_place(&alloc, &zone, size);
	else
		return (return_ptr(realloc_new(&ptr, alloc, size)));
	return (return_ptr(ptr));
}
