/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:07:18 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/02 18:07:21 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t	g_time; //TODO: delete this

int		main(int ac, char **av)
{
	t_args	args;
	t_table	*table;

	if (argparse(&args, ac, av))
		return (1);
	if (!(table = table_new(&args)))
		return (ENOMEM);
	table->start_simulation(table);
	table->del(table);
	return (0);
}
