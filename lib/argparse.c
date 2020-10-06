/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:22:01 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/02 18:22:03 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#define MAX_INTEGER 2147483647

static int	is_valid_argument(char *arg_str)
{
	char		*tmp;

	while (ft_isspace(*arg_str))
		++arg_str;
	tmp = arg_str;
	while (ft_isdigit(*arg_str))
		++arg_str;
	return ((tmp == arg_str || *arg_str) ? 0 : 1);
}

static int	simple_atoi(char *nptr)
{
	unsigned long	number;

	number = 0;
	while (ft_isdigit(*nptr))
	{
		number = number * 10 + (*nptr++ - '0');
		if (number > MAX_INTEGER)
			return (-1);
	}
	return ((int)number);
}

static int	set_arguments(t_args *args, int ac, char **av)
{
	const int	success_code = 0;
	const int	error_code = 1;

	args->n_of_times = -1;
	if ((args->n_of_philosophers = simple_atoi(av[1])) < 1)
		put_error("The number of philosophers must be a positive number!");
	else if ((args->time_to_die = simple_atoi(av[2]) * 1000) < 1)
		put_error("Time to death must be a positive number!");
	else if ((args->time_to_eat = simple_atoi(av[3]) * 1000) < 1)
		put_error("Time to eat must be a positive number!");
	else if ((args->time_to_sleep = simple_atoi(av[4]) * 1000) < 1)
		put_error("Time to sleep must be a positive number!");
	else if (ac == 6)
	{
		if ((args->n_of_times
			= simple_atoi(av[5])) < 1)
		{
			put_error("Number of meals must be a positive number!");
		}
		else
			return (success_code);
	}
	else
		return (success_code);
	return (error_code);
}

/*
** The function fills in the argument structure by pointer.
** Returns 0 if successful, otherwise 1.
*/

int			argparse(t_args *args, int ac, char **av)
{
	const int	error_code = 1;
	const char	*error_message = "Error!\nThe program accepts 4 positive nume\
ric values (and 1 more optional) in the following order:\n  1. Number of philo\
sophers\n  2. Time to die\n  3. Time to eat\n  4. Time to sleep\n  5. Number o\
f times each philosopher must eat\n";
	int			i;

	if (ac < 5 || ac > 6)
	{
		put_error(error_message);
		return (error_code);
	}
	i = ac;
	while (--i > 0)
	{
		if (!is_valid_argument(av[i]))
		{
			put_error(error_message);
			return (error_code);
		}
	}
	return (set_arguments(args, ac, av));
}
