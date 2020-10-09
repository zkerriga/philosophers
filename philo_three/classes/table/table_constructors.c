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

	i = 0;
	while (i < self->quantity)
	{
		sem_post(self->philosophers_array[i]->eat_sem);
		self->philosophers_array[i]->del(self->philosophers_array[i]);
		++i;
	}
	sem_close(self->forks);
	sem_close(self->waiter);
	sem_close(self->output);
	sem_close(self->simulation);
	free(self);
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
			philo_array[i] = philosopher_new(self, i + 1);
			if (!philo_array[i])
			{
				while (i--)
					philo_array[i]->del(philo_array[i]);
				return (NULL);
			}
			++i;
		}
	}
	return (philo_array);
}

static t_table			*pre_init(t_table *self, const t_args *args)
{
	const char	*sem_output = "sem_output";
	const char	*sem_simulation = "sem_simulation";

	self->stats = args;
	self->quantity = args->n_of_philosophers;
	self->start_simulation = table_start_simulation;
	self->del = table_del;
	sem_unlink(sem_output);
	if ((self->output = sem_open(sem_output, O_CREAT | O_RDWR,
													S_IRWXU, 1)) == SEM_FAILED)
	{
		return (NULL);
	}
	sem_unlink(sem_simulation);
	if ((self->simulation = sem_open(sem_simulation, O_CREAT | O_RDWR,
													S_IRWXU, 1)) == SEM_FAILED)
	{
		return (NULL);
	}
	return (self);
}

t_table					*table_new(const t_args *args)
{
	const char	*sem_forks = "sem_forks";
	const char	*sem_waiter = "sem_waiter";
	t_table		*self;

	if ((self = (t_table *)malloc(sizeof(t_table))))
	{
		if (!(pre_init(self, args)))
			return (NULL);
		sem_unlink(sem_forks);
		if ((self->forks = sem_open(sem_forks, O_CREAT | O_RDWR,
										S_IRWXU, self->quantity)) == SEM_FAILED)
		{
			return (NULL);
		}
		sem_unlink(sem_waiter);
		if ((self->waiter = sem_open(sem_waiter, O_CREAT | O_RDWR,
		S_IRWXU, (self->quantity > 1) ? self->quantity / 2 : 1)) == SEM_FAILED)
		{
			return (NULL);
		}
		if (!(self->philosophers_array = create_philo_array(self, args)))
			return (NULL);
	}
	return (self);
}
