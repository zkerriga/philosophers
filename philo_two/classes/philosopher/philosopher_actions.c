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

void	philosopher_eating(t_philosopher *self, int is_limited)
{
	sem_wait(self->eat_mutex);
	set_time_usec(&self->eat_time);
	sem_post(self->eat_mutex);
	self->say(self, SAY_EAT, 0);
	ft_usleep(self->stats->time_to_eat);
	sem_post(self->forks);
	sem_post(self->forks);
	if (is_limited)
	{
		--self->eat_counter;
		if (self->eat_counter == 0)
			--(*self->all_eat_counter);
	}
}

void	philosopher_sleeping(t_philosopher *self)
{
	self->say(self, SAY_SLEEP, 0);
	ft_usleep(self->stats->time_to_sleep);
}

void	*philosopher_action(t_philosopher *self)
{
	int	is_limited;

	is_limited = (self->stats->n_of_times > 0);
	while (!(*self->born))
		;
	set_time_usec(&self->eat_time);
	sem_post(self->eat_mutex);
	while (*self->all_eat_counter)
	{
		if (*self->someone_died)
			break ;
		philosopher_take_a_forks(self);
		if (*self->someone_died)
			break ;
		philosopher_eating(self, is_limited);
		philosopher_sleeping(self);
		self->say(self, SAY_THINK, 0);
	}
	*self->someone_died = 1;
	return (THREAD_SUCCESS);
}
