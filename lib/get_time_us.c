/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_us.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:51:50 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/06 12:51:51 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

/*
** Returns the time in microseconds.
*/

size_t	get_time_usec(void)
{
	struct timeval	tv;
	const int		sec_to_usec = 1000000;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec + tv.tv_sec * sec_to_usec);
}

/*
** Writes the time in microseconds to `dest'.
*/

void	set_time_usec(size_t *dest)
{
	struct timeval	tv;
	const int		sec_to_usec = 1000000;

	gettimeofday(&tv, NULL);
	*dest = tv.tv_usec + tv.tv_sec * sec_to_usec;
}
