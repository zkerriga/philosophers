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

extern size_t	g_time;

void	philosopher_say(t_philosopher *self, const char *message, int is_die)
{
	char	*time_str;
	char	*nbr_str;
	char	*full_str;
	size_t	len;

	time_str = ft_itoa((get_time_usec() - g_time) / 1000);
	nbr_str = ft_itoa(self->id);
	if (!time_str || !nbr_str ||
		!(full_str = ft_say_join(time_str, nbr_str, message)))
	{
		free(time_str);
		free(nbr_str);
		put_error("An ENOMEM error during the speech. Skipped!");
		return ;
	}
	free(time_str);
	free(nbr_str);
	len = ft_strlen(full_str);
	pthread_mutex_lock(self->output);
	write(1, full_str, len);
	if (!is_die)
		pthread_mutex_unlock(self->output);
	free(full_str);
}
