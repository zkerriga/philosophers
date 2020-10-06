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

static int	time_was_changed(t_philosopher *self, size_t last_eat_time)
{
	int		time_was_changed;

	pthread_mutex_lock(&self->eat_mutex);
	time_was_changed = (self->eat_time > last_eat_time);
	pthread_mutex_unlock(&self->eat_mutex);
	return (time_was_changed);
}

/*
** This method is a thread that keeps track of the philosopher's lifetime.
** As soon as the philosopher dies, the table object receives information
** about this via the `someone_died` field, after which it begins waiting
** for the death message to finish printing.
*/

void		*philosopher_lifetime(t_philosopher *self)
{
	size_t		next_sleep_time;
	size_t		last_eat_time;

	while (!(*self->born))
		;
	set_time_usec(&last_eat_time);
	ft_usleep(self->stats->time_to_die);
	while (time_was_changed(self, last_eat_time))
	{
		last_eat_time = self->eat_time;
		next_sleep_time = self->eat_time - last_eat_time;
		ft_usleep(next_sleep_time);
	}
	if (!*self->someone_died && self->eat_counter != 0)
	{
		*self->someone_died = 1;
		pthread_join(self->say(self, SAY_DIE, 1), NULL);
	}
	return (THREAD_SUCCESS);
}
