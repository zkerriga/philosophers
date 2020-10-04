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

static int	set_time(size_t *dest)
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

/*
** This method is a stream that keeps track of the philosopher's lifetime.
** As soon as the philosopher dies, the table object receives information
** about this via the `someone_died` field, after which it begins waiting
** for the death message to finish printing.
*/

void		*philosopher_lifetime(t_philosopher *self)
{
	const int	ms_to_us = 1000;
	size_t		start_time;
	size_t		next_sleep_time;

	D(printf("[+] Start lifetime for %ld philosopher!\n", self->id);)
	while (!(*self->born))
		;
	if (set_time(&start_time))
		return (THREAD_ERROR);
	usleep(self->stats->time_to_die * ms_to_us);
	while (self->eat_time)
	{
		next_sleep_time = self->eat_time - start_time; //TODO: eat_time < start_time?
		start_time = self->eat_time;
		self->eat_time = 0;
		usleep(next_sleep_time * ms_to_us);
	}
	if (!*self->someone_died)
	{
		*self->someone_died = 1;
		D(printf("[+] The %ld philosopher died!\n", self->id);)
		pthread_join(self->say(self, SAY_DIE), NULL);
	}
	return (THREAD_SUCCESS);
}
