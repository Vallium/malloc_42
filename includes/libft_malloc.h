/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:54:02 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/20 17:16:44 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdio.h>
# include <libft.h>

# define TINY_MAX_SIZE 			(2 * getpagessize() - sizeof(t_alloc))
# define MIN_NB_TINY_ALLOCS		100

# define SMALL_MAX_SIZE			(8 * getpagessize() - sizeof(t_alloc))
# define MIN_NB_SMALL_ALLOCS	100

# define TRUE	1
# define FALSE	0

typedef enum	s_type {
	TINY,
	SMALL,
	LARGE
}				e_type;

typedef short	bool;

typedef struct	s_alloc
{
	short			size;
	bool			freed;
	struct s_alloc	*prev;
	struct s_alloc	*next;
}				t_alloc;

typedef struct	s_zone
{
	e_type			type;
	t_alloc			*allocs;
	short			nb_allocs;
	struct s_zone	*next;
}				t_zone;

typedef struct	s_allocs
{
	t_zone		*zones;
	short		nb_zones;
}				t_allocs;

extern t_allocs g_allocs;

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

#endif
