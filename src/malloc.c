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
