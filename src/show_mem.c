/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 16:55:28 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/07 15:50:14 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>

void			show_alloc_mem(void)
{
	pthread_mutex_lock(mutex_sglton());
	print_mem(FALSE);
	pthread_mutex_unlock(mutex_sglton());
}

void			show_freed_mem(void)
{
	pthread_mutex_lock(mutex_sglton());
	ft_putstr("Memory freed:\n");
	print_mem(TRUE);
	pthread_mutex_unlock(mutex_sglton());
}
