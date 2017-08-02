/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 14:21:37 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/02 14:57:03 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>

pthread_mutex_t		*mutex_sglton(void)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	return (&mutex);
}
