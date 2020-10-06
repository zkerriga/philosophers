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

/*
** This method is a stream that keeps track of the philosopher's lifetime.
** As soon as the philosopher dies, the table object receives information
** about this via the `someone_died` field, after which it begins waiting
** for the death message to finish printing.
*/

void		*philosopher_lifetime(t_philosopher *self)
{
	size_t		start_time_usec;
	size_t		next_sleep_time_usec;

	while (!(*self->born))
		;
	set_time_usec(&start_time_usec);
	ft_usleep(self->stats->time_to_die);
	while (self->eat_time)
	{
		next_sleep_time_usec = self->eat_time - start_time_usec; //TODO: eat_time < start_time?
		start_time_usec = self->eat_time;
		self->eat_time = 0; //TODO: переработать на разные переменные
		ft_usleep(next_sleep_time_usec);
	}
	if (!*self->someone_died && self->eat_counter != 0)
	{
		*self->someone_died = 1;
		pthread_join(self->say(self, SAY_DIE, 1), NULL);
	}
	D(puts("[-] STOP LIFETIME");)
	return (THREAD_SUCCESS);
}
