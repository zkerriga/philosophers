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

static int	simple_atoi(char *str)
{

}

static int	set_arguments(t_args *args, int ac, char **av)
{
	const int	success_code = 0;
	const int	error_code = 1;


	return (success_code);
}

/*
** The function fills in the argument structure by pointer.
** Returns 0 if successful, otherwise 1.
*/

int			argparse(t_args *args, int ac, char **av)
{
	const int	error_code = 1;
	const char	*error_message = "Arguments error!\nThe program accepts 4 nume\
ric values (and 1 more optional) in the following order:\n  1. Number of philo\
sophers\n  2. Time to die\n  3. Time to eat\n  4. Time to sleep\n  5. Number o\
f times each philosopher must eat\n";
	int			i;

	if (ac < 4 || ac > 5)
	{
		put_error(error_message);
		return (error_code);
	}
	i = ac;
	while (--i > 0)
	{
		if (!is_valid_argument(av[0]))
		{
			put_error(error_message);
			return (error_code);
		}
	}
	return (set_arguments(args, ac, av));
}
