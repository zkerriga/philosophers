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

void	*philosopher_action(t_philosopher *self)
{
	D(printf("[+] Start actions for %ld philosopher!\n", self->id);)
	while (!(*self->born))
		;
	usleep(50 * 1000ul);
	self->say(self, SAY_FORK);
	usleep(50 * 1000ul);
	self->say(self, SAY_FORK);
	usleep(50 * 1000ul);
	self->say(self, SAY_EAT);
	usleep(50 * 1000ul);
	self->say(self, SAY_SLEEP);
	usleep(50 * 1000ul);
	self->say(self, SAY_THINK);
	return (THREAD_SUCCESS);
}
