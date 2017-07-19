/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:05:37 by aalliot           #+#    #+#             */
/*   Updated: 2017/07/19 16:12:51 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

#include <libft_malloc.h>
#include <sys/mman.h>

void	*realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;

	char *ret;

	write(1, "realloc", 7);

	ret = mmap(0, (50 * getpagesize()), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ret);
}
