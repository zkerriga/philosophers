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
	self->say(self, SAY_FORK);
}

static int	set_time(size_t *dest) //TODO: две одинаковые функции
{
	const int		success_code = 0;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		put_error("A `gettimeofday` error. Critical!");
		return (errno);
	}
	*dest = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (success_code);
}

void	philosopher_eating(t_philosopher *self)
{
	const int	ms_to_us = 1000;

	set_time(&self->eat_time);
	self->say(self, SAY_EAT);
	usleep(self->stats->time_to_eat * ms_to_us);
	pthread_mutex_unlock(self->forks.right);
	pthread_mutex_unlock(self->forks.left);
}

void	philosopher_sleeping(t_philosopher *self)
{
	const int	ms_to_us = 1000; //TODO: перевести всё naher на миллисекунды

	self->say(self, SAY_SLEEP);
	usleep(self->stats->time_to_sleep * ms_to_us);
}

void	*philosopher_action(t_philosopher *self)
{
	D(printf("[+] Start actions for %ld philosopher!\n", self->id);)
	while (!(*self->born))
		;
	while (self->eat_counter)
	{
		philosopher_take_a_fork(self, self->forks.left);
		philosopher_take_a_fork(self, self->forks.right);
		philosopher_eating(self);
		philosopher_sleeping(self);
		self->say(self, SAY_THINK);
		if (self->stats->number_of_times_each_philosopher_must_eat > 0)
			--self->eat_counter;
	}
	return (THREAD_SUCCESS);
}
