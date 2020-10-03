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

static int	simulation(t_table *table)
{
	usleep(500000lu);
	table->start_simulation(table);
	D(puts("-> SLEEP 5 <-");)
	usleep(5000000lu);

}

int		main(int ac, char **av)
{
	t_args	args;
	t_table	*table;

	if (argparse(&args, ac, av))
		return (1);
	D(printf("Args:\n1 -> %ld\n2 -> %ld\n3 -> %ld\n4 -> %ld\n5 -> %ld\n", args.number_of_philosophers, args.time_to_die, args.time_to_eat, args.time_to_sleep, args.number_of_times_each_philosopher_must_eat))
	if (!(table = table_new(&args)))
		return (ENOMEM);
	simulation(table);
	table->del(table);
	return (0);
}
