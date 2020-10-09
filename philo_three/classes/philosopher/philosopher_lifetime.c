/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_lifetime.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:17:50 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 14:17:51 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void		*philosopher_lifetime(t_philosopher *self)
{
	const int	delay = 500;
	time_t		time_to_die;
	time_t		current_time;

	time_to_die = self->stats->time_to_die;
	while (self->i_am_alive)
	{
		sem_wait(self->eat_mutex);
		set_time_usec(&current_time);
		if (current_time - self->eat_time > time_to_die)
		{
			if (self->i_am_alive)
			{
				self->say(self, SAY_DIE, 1);
				self->i_am_alive = 0;
				sem_post(self->simulation);
			}
		}
		sem_post(self->eat_mutex);
		usleep(delay);
	}
	return (THREAD_SUCCESS);
}
