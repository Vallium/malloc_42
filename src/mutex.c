/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 14:21:37 by aalliot           #+#    #+#             */
/*   Updated: 2017/08/01 17:37:38 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_malloc.h>

pthread_mutex_t		*mutex_sglton()
{
	//static pthread_mutex_t	*mutex = NULL;

	//if (mutex == NULL)
	//	pthread_mutex_init(mutex, NULL);
	return (&g_mutex);
}

