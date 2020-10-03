/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:10:31 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/02 18:10:33 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

#define DEBUG 1 //TODO: delete this
#if DEBUG == 1
#include <stdio.h>
#define D(x) {printf("\033[35m"); x ; printf("\033[0m");}
#else
#define D(x) {}
#endif

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

# define THREAD_SUCCESS 0

typedef struct	s_args
{
	ssize_t		number_of_philosophers;
	ssize_t		time_to_die;
	ssize_t		time_to_eat;
	ssize_t		time_to_sleep;
	ssize_t		number_of_times_each_philosopher_must_eat;
}				t_args;

void			put_error(const char *error_str);
int				argparse(t_args *args, int ac, char **av);

int				ft_isspace(int c);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);

#endif
