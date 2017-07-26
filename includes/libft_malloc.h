/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:54:02 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/26 17:50:28 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <libft.h>
# include <unistd.h> 

# define MMAP_PROTS				PROT_READ | PROT_WRITE
# define MMAP_MAPS				MAP_ANONYMOUS | MAP_PRIVATE

# define TINY_MAX_SIZE 			1 * getpagesize() * sizeof(char)
# define MIN_NB_TINY_ALLOCS		100
# define TINY_ZONE_SIZE			(TINY_MAX_SIZE + sizeof(t_alloc)) * MIN_NB_TINY_ALLOCS + sizeof(t_zone)

# define SMALL_MAX_SIZE			4 * getpagesize() * sizeof(char) 
# define MIN_NB_SMALL_ALLOCS	100
# define SMALL_ZONE_SIZE		(SMALL_MAX_SIZE + sizeof(t_alloc)) * MIN_NB_SMALL_ALLOCS + sizeof(t_zone)

# define JUMPOF(size)			sizeof(char) * size

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
	bool			last;
	struct s_alloc	*next;
}				t_alloc;

typedef struct	s_zone
{
	e_type			type;
	t_alloc			*allocs;
	size_t				mem_left;
	int				nb_allocs;
	struct s_zone	*next;
}				t_zone;

typedef struct	s_allocs
{
	t_zone		*zones;
	short		nb_zones;
}				t_allocs;

extern t_allocs g_allocs;

void	show_alloc_mem();

t_zone	*new_zone_large(size_t size);
t_zone	*find_valid_zone(size_t size, e_type type);

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

#endif
