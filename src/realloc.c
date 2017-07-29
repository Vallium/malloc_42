/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:05:37 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/29 18:21:17 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>
#include <sys/mman.h>

static void		*realloc_new(void **ptr, t_alloc *alloc, size_t size)
{
	void	*ret;

	ret = malloc(size);
	ft_memcpy(ret, *ptr, alloc->size);
	free(*ptr);
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
	pthread_mutex_unlock(&g_thread_lock);
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	t_alloc	*alloc;

	if (!ptr && size)
		return (malloc(size));
	else if (ptr && !size)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_thread_lock);
	alloc = (t_alloc*)(ptr - JUMPOF(sizeof(t_alloc)));
	if (alloc->a != A_MAGIC || alloc->b != B_MAGIC)
		return (return_ptr(ptr));
	zone = alloc->zone;
	if (size <= alloc->size)
		alloc->size = size;
	else if (alloc->last == TRUE && (size - alloc->size) <= zone->mem_left)
		realloc_same_place(&alloc, &zone, size);
	else
		return (return_ptr(realloc_new(&ptr, alloc, size)));
	return (return_ptr(ptr));
}
