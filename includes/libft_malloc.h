/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:54:02 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/21 14:24:59 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <libft.h>
# include <unistd.h> 

# define TINY_MAX_SIZE 			1 * getpagesize()
# define MIN_NB_TINY_ALLOCS		100
# define TINY_ZONE_SIZE			(TINY_MAX_SIZE + sizeof(t_alloc)) * MIN_NB_TINY_ALLOCS + sizeof(t_zone)

# define SMALL_MAX_SIZE			4 * getpagesize() 
# define MIN_NB_SMALL_ALLOCS	100
# define SMALL_ZONE_SIZE		(SMALL_MAX_SIZE + sizeof(t_alloc)) * MIN_NB_SMALL_ALLOCS + sizeof(t_zone)

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
	int				mem_left;
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
