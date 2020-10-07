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

void	ft_usleep(size_t time_usec)
{
	size_t		start_time;
	size_t		current_time;
	const int	inaccuracy = 0;

	time_usec -= inaccuracy;
	set_time_usec(&start_time);
	set_time_usec(&current_time);
	while (current_time - start_time < time_usec)
	{
		set_time_usec(&current_time);
	}
}
