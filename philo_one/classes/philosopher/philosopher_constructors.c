/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_constructors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 09:20:20 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 09:20:22 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void		philosopher_del(t_philosopher *self)
{
	free(self);
}

t_philosopher	*philosopher_new(int *someone_died, pthread_mutex_t *output, const t_args *args, const int *born, size_t id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	t_philosopher	*self;

	if ((self = (t_philosopher *)malloc(sizeof(t_philosopher))))
	{
		self->id = id;
		self->born = born;
		self->stats = args;
		self->forks.left = left_fork;
		self->forks.right = right_fork;
		self->output = output;
		self->eat_time = 0;
		self->someone_died = someone_died;
		self->eat_counter = (args->number_of_times_each_philosopher_must_eat < 0) ? 1 : args->number_of_times_each_philosopher_must_eat;
		pthread_create(&self->actions, NULL, (void *(*)(void *))philosopher_action, self); //TODO: check error
		pthread_create(&self->lifetime, NULL, (void *(*)(void *))philosopher_lifetime, self); //TODO: check error
		self->say = philosopher_say;
		self->del = philosopher_del;
	}
	return (self);
}
