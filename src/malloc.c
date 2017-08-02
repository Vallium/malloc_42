/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:51:55 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/02 14:34:26 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

t_allocs g_allocs = {
	.zones = NULL,
};

void	*malloc(size_t size)
{
	void	*ret;

	pthread_mutex_lock(mutex_sglton());
	if (size <= 0)
		return (NULL);
	if (size <= TINY_MAX_SIZE)
		ret = new_alloc(size, TINY);
	else if (size <= SMALL_MAX_SIZE)
		ret = new_alloc(size, SMALL);
	else
		ret = new_alloc_large(size);
	pthread_mutex_unlock(mutex_sglton());
	return (ret);
}
