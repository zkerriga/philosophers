/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:49:30 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/06 12:49:31 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_usleep(time_t time_usec)
{
	time_t		start_time;
	time_t		current_time;
	const int	inaccuracy = 35;

	time_usec -= inaccuracy;
	set_time_usec(&start_time);
	set_time_usec(&current_time);
	while (current_time - start_time < time_usec)
	{
		usleep(10);
		set_time_usec(&current_time);
	}
}
