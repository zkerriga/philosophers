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

void	table_start_simulation(t_table *self)
{
	size_t	i;

	i = self->quantity;
	self->born = 1;
	while (i--)
	{
		pthread_join(self->philosophers_array[i]->lifetime, NULL);
	}
}
