/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:54:02 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/19 14:26:01 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdio.h>
# include <libft.h>

#define TINY_ALLOC_SIZE_MAX (2 * getpagessize() - sizeof(t_alloc))

#define TRUE	1
#define FALSE	0

typedef int bool;

typedef struct	s_alloc
{
	short		size;
	bool		freed;
}				t_alloc;

typedef struct	s_zone
{
	t_list		*allocs;
	short		nb_allocs;
}				t_zone;

typedef struct	s_allocs
{
	t_list		*zones;
	short		nb_zones;
}				t_allocs;

extern t_allocs *g_allocs;

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

#endif
