/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:05:37 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/27 19:07:36 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>
#include <sys/mman.h>

void	*realloc_new(void **ptr, t_alloc *alloc, size_t size)
{
	void	*ret;

	ret = malloc(size);
	ft_memcpy(ret, *ptr, alloc->size);
	free(*ptr);
	return (ret);
}

void	realloc_same_place(t_alloc **alloc, t_zone **zone, size_t size)
{
	(*alloc)->size = size;
	(*alloc)->next += JUMPOF(size - (*alloc)->size);
	(*zone)->mem_left -= size - (*alloc)->size;
}

void	*realloc(void *ptr, size_t size)
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
	alloc = (t_alloc*)(ptr - JUMPOF(sizeof(t_alloc)));
	if (alloc->a != A_MAGIC || alloc->b != B_MAGIC)
		return (ptr);
	zone = alloc->zone;
	if (size <= alloc->size)
		alloc->size = size;
	else if (alloc->last == TRUE && (size - alloc->size) <= zone->mem_left)
		realloc_same_place(&alloc, &zone, size);
	else
		return (realloc_new(&ptr, alloc, size));
	return (ptr);
}
