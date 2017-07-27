/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:54:02 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/27 19:06:46 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <libft.h>
# include <unistd.h>

# define MMAP_PROTS			PROT_READ | PROT_WRITE
# define MMAP_MAPS			MAP_ANONYMOUS | MAP_PRIVATE

# define S(x)				sizeof(x)

# define TINY_MAX_SIZE 		1 * getpagesize() * sizeof(char)
# define NB_TINYS			100
# define TINY_ZONE_SIZE		(TINY_MAX_SIZE + S(t_alloc)) * NB_TINYS + S(t_zone)

# define SMALL_MAX_SIZE		4 * getpagesize() * sizeof(char)
# define NB_SMAL			100
# define SMALL_ZONE_SIZE	(SMALL_MAX_SIZE + S(t_alloc)) * NB_SMAL + S(t_zone)

# define JUMPOF(size)		sizeof(char) * size

# define A_MAGIC			985256
# define B_MAGIC			-212858

# define TRUE				1
# define FALSE				0

typedef enum			e_type {
	TINY,
	SMALL,
	LARGE
}						t_type;

typedef short			t_bool;

typedef struct			s_alloc
{
	int				a;
	size_t			size;
	t_bool			freed;
	t_bool			last;
	void			*zone;
	struct s_alloc	*next;
	int				b;
}						t_alloc;

typedef struct			s_zone
{
	t_type			type;
	t_alloc			*allocs;
	size_t			mem_left;
	size_t			nb_allocs;
	struct s_zone	*next;
	struct s_zone	*prev;
}						t_zone;

typedef struct			s_allocs
{
	t_zone	*zones;
}						t_allocs;

extern					t_allocs g_allocs;

void					show_alloc_mem();

t_zone					*new_zone_large(size_t size);
t_zone					*find_valid_zone(size_t size, t_type type);

void					*new_alloc_large(size_t size);
void					*new_alloc(size_t size, t_type type);

void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					free(void *ptr);

#endif
