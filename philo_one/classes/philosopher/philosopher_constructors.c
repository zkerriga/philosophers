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
#include "table.h"

static void		philosopher_del(t_philosopher *self)
{
	pthread_mutex_destroy(&self->eat_mutex);
	free(self);
}

static void		table_pre_init(t_philosopher *self, t_table *table)
{
	self->born = &table->born;
	self->stats = table->stats;
	self->output = &table->output;
	self->someone_died = &table->someone_died;
}

t_philosopher	*philosopher_new(void *table, size_t id,
						pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	t_philosopher	*self;
	ssize_t			n_of_times;

	if ((self = (t_philosopher *)malloc(sizeof(t_philosopher))))
	{
		self->id = id;
		table_pre_init(self, table);
		self->forks.left = left_fork;
		self->forks.right = right_fork;
		self->eat_time = 0;
		n_of_times = self->stats->n_of_times;
		self->eat_counter = (n_of_times < 0) ? 1 : n_of_times;
		if (pthread_mutex_init(&self->eat_mutex, NULL) ||
pthread_create(&self->actions, NULL,
			(void *(*)(void *))philosopher_action, self) ||
pthread_create(&self->lifetime, NULL,
			(void *(*)(void *))philosopher_lifetime, self))
		{
			return (NULL);
		}
		self->say = philosopher_say;
		self->del = philosopher_del;
	}
	return (self);
}
