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
	sem_close(self->eat_mutex);
	sem_post(self->forks);
	sem_post(self->forks);
	free(self);
}

static void		*table_pre_init(t_philosopher *self, t_table *table)
{
	self->born = &table->born;
	self->stats = table->stats;
	self->forks = table->forks;
	self->output = table->output;
	self->waiter = table->waiter;
	self->someone_died = &table->someone_died;
	self->all_eat_counter = &table->all_eat_counter;
	self->say = philosopher_say;
	self->del = philosopher_del;
	if (pthread_create(&self->actions, NULL,
						(void *(*)(void *))philosopher_action, self) ||
		pthread_create(&self->lifetime, NULL,
						(void *(*)(void *))philosopher_lifetime, self))
	{
		return (NULL);
	}
	return (self);
}

static char		*get_sem_name(const char *default_name, size_t id)
{
	char	*sem_name;
	char	*nbr_str;
	size_t	len_default;
	size_t	len_nbr;

	if (!(nbr_str = ft_itoa(id)))
		return (NULL);
	len_nbr = ft_strlen(nbr_str);
	len_default = ft_strlen(default_name);
	if ((sem_name = malloc(sizeof(char) * (len_default + len_nbr + 1))))
	{
		ft_strlcpy(sem_name, default_name, len_default + 1);
		ft_strlcpy(&(sem_name[len_default]), nbr_str, len_nbr + 1);
	}
	free(nbr_str);
	return (sem_name);
}

t_philosopher	*philosopher_new(void *table, size_t id)
{
	t_philosopher	*self;
	ssize_t			n_of_times;
	char			*sem_name;

	if ((self = (t_philosopher *)malloc(sizeof(t_philosopher))))
	{
		self->id = id;
		if (!(table_pre_init(self, table)))
			return (NULL);
		self->eat_time = 0;
		if (!(sem_name = get_sem_name("sem_eat_mutex", id)))
			return (NULL);
		sem_unlink(sem_name);
		if ((self->eat_mutex = sem_open(sem_name, O_CREAT | O_RDWR,
													S_IRWXU, 1)) == SEM_FAILED)
		{
			return (NULL);
		}
		free(sem_name);
		sem_wait(self->eat_mutex);
		n_of_times = self->stats->n_of_times;
		self->eat_counter = (n_of_times < 0) ? 1 : n_of_times;
	}
	return (self);
}
