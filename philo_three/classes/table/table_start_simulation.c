/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_start_simulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 16:08:38 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 16:08:39 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

int		init_fork(t_table *self, size_t index)
{
	pid_t		pid;
	const int	success_code = 0;

	pid = fork();
	if (pid < 0)
	{
		put_error("Fork error! Exit.");
		return (errno);
	}
	else if (pid == 0)
	{
		philosopher_action(self->philosophers_array[index]);
		sem_post(self->simulation);
		while (!usleep(1000))
			;
	}
	else
	{
		self->philosophers_array[index]->pid = pid;
	}
	return (success_code);
}

void	*wait_eat_counter_thread(t_table *self)
{
	size_t	i;

	i = 0;
	while (i < self->quantity)
		sem_wait(self->philosophers_array[i++]->eat_sem);
	sem_post(self->simulation);
	return (THREAD_SUCCESS);
}

void	table_start_simulation(t_table *self)
{
	size_t		i;
	int			ret;
	pthread_t	wait_eat_counter;

	sem_wait(self->simulation);
	i = 0;
	while (i < self->quantity)
	{
		if ((ret = init_fork(self, i)))
		{
			while (i--)
				kill(self->philosophers_array[i]->pid, SIGKILL);
			exit(ret);
		}
		++i;
	}
	if (pthread_create(&wait_eat_counter, NULL,
						(void *(*)(void *))wait_eat_counter_thread, self))
	{
		put_error("Thread error! Exit.");
		exit(errno);
	}
	sem_wait(self->simulation);
}
