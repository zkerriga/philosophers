/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_constructors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 09:13:39 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 09:15:35 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

static void				table_del(t_table *self)
{
	size_t	i;

	pthread_mutex_destroy(&self->output);
	i = 0;
	while (i < self->quantity)
	{
		self->philosophers_array[i]->del(self->philosophers_array[i]);
		++i;
	}
	i = 0;
	while (i < self->quantity)
		pthread_mutex_destroy(&(self->forks_array[i++]));
	free(self);
}

static pthread_mutex_t	*create_forks_array(size_t quantity)
{
	pthread_mutex_t	*forks_array;
	size_t			i;

	if ((forks_array = malloc(sizeof(pthread_mutex_t) * quantity)))
	{
		i = 0;
		while (i < quantity)
		{
			if (pthread_mutex_init(&(forks_array[i]), NULL))
			{
				while (i)
					pthread_mutex_destroy(&(forks_array[--i]));
				return (NULL);
			}
			++i;
		}
	}
	return (forks_array);
}

static t_philosopher	**create_philo_array(t_table *self, const t_args *args)
{
	t_philosopher	**philo_array;
	ssize_t			i;

	philo_array = malloc(sizeof(t_philosopher *) * args->n_of_philosophers);
	if (philo_array)
	{
		i = 0;
		while (i < args->n_of_philosophers)
		{
			philo_array[i] = philosopher_new(self, i + 1,
&(self->forks_array[i]),
&(self->forks_array[(i + 1 == args->n_of_philosophers) ? 0 : i + 1]));
			if (!philo_array[i])
			{
				return (NULL);
			}
			++i;
		}
	}
	return (philo_array);
}

static t_table			*pre_init(t_table *self, const t_args *args)
{
	self->stats = args;
	self->quantity = args->n_of_philosophers;
	self->born = 0;
	self->someone_died = 0;
	self->all_eat_counter = args->n_of_philosophers;
	self->start_simulation = table_start_simulation;
	self->del = table_del;
	if (pthread_mutex_init(&self->output, NULL))
	{
		free(self);
		return (NULL);
	}
	return (self);
}

t_table					*table_new(const t_args *args)
{
	t_table	*self;

	if ((self = (t_table *)malloc(sizeof(t_table))))
	{
		if (!pre_init(self, args))
			return (NULL);
		if (!(self->forks_array = create_forks_array(self->quantity)))
		{
			pthread_mutex_destroy(&self->output);
			free(self);
			return (NULL);
		}
		if (!(self->philosophers_array = create_philo_array(self, args)))
		{
			pthread_mutex_destroy(&self->output);
			while (self->quantity)
				pthread_mutex_destroy(&(self->forks_array[--self->quantity]));
			free(self);
			return (NULL);
		}
	}
	return (self);
}
