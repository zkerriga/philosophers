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

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <errno.h>

# define THREAD_SUCCESS 0

# define DEBUG 0
# if DEBUG == 1
#  include <stdio.h>
#  define D(x) {printf("\033[35m"); x ; printf("\033[0m");}
# else
#  define D(x) {}
# endif

typedef struct	s_args
{
	ssize_t		n_of_philosophers;
	ssize_t		time_to_die;
	ssize_t		time_to_eat;
	ssize_t		time_to_sleep;
	ssize_t		n_of_times;
}				t_args;

void			put_error(const char *error_str);
int				argparse(t_args *args, int ac, char **av);
char			*ft_say_join(const char *time, const char *nbr,
								const char *message);
void			set_time_usec(time_t *dest);
time_t			get_time_usec(void);
void			ft_usleep(time_t time_usec);

int				ft_isspace(int c);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
char			*ft_itoa(size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

#endif
