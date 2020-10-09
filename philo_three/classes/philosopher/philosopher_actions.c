/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:17:58 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 14:18:00 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philosopher_take_a_forks(t_philosopher *self)
{
	sem_wait(self->waiter);
	sem_wait(self->forks);
	self->say(self, SAY_FORK, 0);
	sem_wait(self->forks);
	self->say(self, SAY_FORK, 0);
	sem_post(self->waiter);
}

void	philosopher_eating(t_philosopher *self)
{
	sem_wait(self->eat_mutex);
	set_time_usec(&self->eat_time);
	sem_post(self->eat_mutex);
	self->say(self, SAY_EAT, 0);
	ft_usleep(self->stats->time_to_eat);
	sem_post(self->forks);
	sem_post(self->forks);
}

void	philosopher_sleeping(t_philosopher *self)
{
	self->say(self, SAY_SLEEP, 0);
	ft_usleep(self->stats->time_to_sleep);
}

int		philosopher_action(t_philosopher *self)
{
	int		is_limited;

	is_limited = (self->stats->n_of_times > 0);
	sem_wait(self->eat_mutex);
	if (pthread_create(&self->lifetime, NULL,
							(void *(*)(void *))philosopher_lifetime, self))
	{
		return (1);
	}
	set_time_usec(&self->eat_time);
	sem_post(self->eat_mutex);
	while (self->eat_counter)
	{
		if (!self->i_am_alive)
			break ;
		philosopher_take_a_forks(self);
		if (!self->i_am_alive)
			break ;
		philosopher_eating(self);
		philosopher_sleeping(self);
		self->say(self, SAY_THINK, 0);
		if (is_limited)
			--self->eat_counter;
		if (!self->i_am_alive)
			break ;
	}
	self->i_am_alive = 0;
	return (0);
}
