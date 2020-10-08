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
	free(self);
}

static void		table_pre_init(t_philosopher *self, t_table *table)
{
	self->born = &table->born;
	self->stats = table->stats;
	self->output = table->output;
	self->forks = table->forks;
	self->someone_died = &table->someone_died;
}

t_philosopher	*philosopher_new(void *table, size_t id)
{
	t_philosopher	*self;
	ssize_t			n_of_times;

	if ((self = (t_philosopher *)malloc(sizeof(t_philosopher))))
	{
		self->id = id;
		table_pre_init(self, table);
		self->eat_time = 0;
		sem_unlink("sem_eat_mutex");
		if ((self->eat_mutex = sem_open("sem_eat_mutex", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED)
			return (NULL);
		sem_wait(self->eat_mutex);
		n_of_times = self->stats->n_of_times;
		self->eat_counter = (n_of_times < 0) ? 1 : n_of_times;
		if (pthread_create(&self->actions, NULL,
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
