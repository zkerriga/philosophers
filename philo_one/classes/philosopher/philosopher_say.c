/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_say.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 16:47:20 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 16:47:21 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	put_and_free_full_str(t_say *say, char *full_str)
{
	size_t			len;
	pthread_mutex_t	*output;

	len = ft_strlen(full_str);
	output = say->output;
	pthread_mutex_lock(output);
	write(1, full_str, len);
	if (!say->is_die)
		pthread_mutex_unlock(output);
	free(full_str);
}

static void	*create_and_put_str(t_say *say)
{
	char	*time_str;
	char	*nbr_str;
	char	*full_str;

	time_str = ft_itoa(say->time_usec / 1000);
	nbr_str = ft_itoa(say->id);
	if (!time_str || !nbr_str ||
		!(full_str = ft_say_join(time_str, nbr_str, say->message)))
	{
		if (time_str)
			free(time_str);
		if (nbr_str)
			free(nbr_str);
		free(say);
		put_error("An ENOMEM error during the speech. Skipped!");
		return ((void *)ENOMEM);
	}
	free(time_str);
	free(nbr_str);
	put_and_free_full_str(say, full_str);
	free(say);
	return (THREAD_SUCCESS);
}

pthread_t	philosopher_say(t_philosopher *self, const char *message, int die)
{
	t_say		*say;
	pthread_t	say_thread;

	if (!(say = malloc(sizeof(t_say))))
	{
		put_error("An ENOMEM error during the speech. Skipped!");
		return (NULL);
	}
	set_time_usec(&say->time_usec);
	say->id = self->id;
	say->message = message;
	say->is_die = die;
	say->output = self->output;
	if (pthread_create(&say_thread, NULL, (void *(*)(void *))create_and_put_str,
						say))
	{
		free(say);
		put_error("A thread error during the speech. Skipped!");
	}
	return (say_thread);
}
