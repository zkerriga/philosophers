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

void	philosopher_take_a_fork(t_philosopher *self, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	self->say(self, SAY_FORK, 0);
}

void	philosopher_eating(t_philosopher *self)
{
	set_time_usec(&self->eat_time);
	self->say(self, SAY_EAT, 0);
	ft_usleep(self->stats->time_to_eat);
	pthread_mutex_unlock(self->forks.right);
	pthread_mutex_unlock(self->forks.left);
}

void	philosopher_sleeping(t_philosopher *self)
{
	self->say(self, SAY_SLEEP, 0);
	ft_usleep(self->stats->time_to_sleep);
}

void	*philosopher_action(t_philosopher *self)
{
	D(printf("[+] Start actions for %ld philosopher!\n", self->id);)
	while (!(*self->born))
		;
	while (self->eat_counter)
	{
		if (!*self->someone_died)
			philosopher_take_a_fork(self, (self->id % 2) ? self->forks.left : self->forks.right);
		if (!*self->someone_died)
			philosopher_take_a_fork(self, (self->id % 2) ? self->forks.right : self->forks.left);
		if (!*self->someone_died)
			philosopher_eating(self);
		if (!*self->someone_died)
			philosopher_sleeping(self);
		if (!*self->someone_died)
			self->say(self, SAY_THINK, 0);
		if (self->stats->number_of_times_each_philosopher_must_eat > 0)
			--self->eat_counter;
		if (!self->eat_counter)
			*self->someone_died = 1;
	}
	D2(puts("[-] STOP CYCLE");)
	return (THREAD_SUCCESS);
}
