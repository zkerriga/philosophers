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
	pthread_mutex_unlock(output);
	free(full_str);
}

static void	*create_and_put_str(t_say *say)
{
	size_t	time;
	char	*time_str;
	char	*nbr_str;
	char	*full_str;

	time = say->tv.tv_sec * 1000 + say->tv.tv_usec / 1000;
	time_str = ft_itoa(time);
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

void	philosopher_say(t_philosopher *self, const char *message)
{
	t_say		*say;
	pthread_t	say_thread;

	if (!(say = malloc(sizeof(t_say))))
	{
		put_error("An ENOMEM error during the speech. Skipped!");
		return ;
	}
	if (gettimeofday(&(say->tv), NULL))
	{
		free(say);
		put_error("A `gettimeofday` error during the speech. Skipped!");
		return ;
	}
	say->message = message;
	say->output = self->output;
	say->id = self->id;
	if (pthread_create(&say_thread, NULL, (void *(*)(void *))create_and_put_str, say))
	{
		free(say);
		put_error("A thread error during the speech. Skipped!");
	}
}