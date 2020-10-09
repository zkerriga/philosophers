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

static void	put_ph(t_philosopher *self, char *full_str, size_t len, int is_die)
{
	sem_wait(self->output);
	if (self->i_am_alive)
		write(1, full_str, len);
	if (is_die)
		self->i_am_alive = 0;
	else
		sem_post(self->output);
}

void		philosopher_say(t_philosopher *self, const char *message, int die)
{
	char	*time_str;
	char	*nbr_str;
	char	*full_str;

	time_str = ft_itoa(get_time_usec() / 1000);
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
	if (self->i_am_alive)
		put_ph(self, full_str, ft_strlen(full_str), die);
	free(full_str);
}
