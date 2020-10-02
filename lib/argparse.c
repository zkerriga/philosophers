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

/*
** The function fills in the argument structure by pointer.
** Returns 0 if successful, otherwise 1.
*/

int		argparse(t_args *args, int ac, char **av)
{
	const int	success_code = 0;
	const int	error_code = 1;

	if (ac < 4 || ac > 5)
	{
		put_error("Arguments error!\nThe program accepts 4 numeric values (and\
1 more optional) in the following order:\n  1. Number of philosophers\n  2. Ti\
me to die\n  3. Time to eat\n  4. Time to sleep\n  5. Number of times each phi\
losopher must eat\n");
		return (error_code);
	}
	else
	{

	}
	return (success_code);
}
