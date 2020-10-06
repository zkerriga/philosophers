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
	pthread_mutex_destroy(&self->eat_mutex);
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
		self->eat_counter = (args->n_of_times < 0) ? 1 : args->n_of_times;
		if (pthread_mutex_init(&self->eat_mutex, NULL) ||
pthread_create(&self->actions, NULL, (void *(*)(void *))philosopher_action, self) ||
pthread_create(&self->lifetime, NULL, (void *(*)(void *))philosopher_lifetime, self))
		{
			return (NULL);
		}
		self->say = philosopher_say;
		self->del = philosopher_del;
	}
	return (self);
}
