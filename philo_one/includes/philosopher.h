/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 09:20:45 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 09:20:47 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "lib.h"
# define SAY_FORK "has taken a fork"
# define SAY_EAT "is eating"
# define SAY_SLEEP "is sleeping"
# define SAY_THINK "is thinking"
# define SAY_DIE "died"

typedef struct		s_forks
{
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}					t_forks;

typedef struct		s_philosopher
{
	size_t			id;
	const int		*born;
	const t_args	*stats;
	pthread_t		lifetime;
	pthread_t		actions;
	t_forks			forks;
	pthread_mutex_t	*output;
	time_t			eat_time;
	pthread_mutex_t	eat_mutex;
	int				*someone_died;
	ssize_t			eat_counter;
	ssize_t			*all_eat_counter;
	void			(*say)(struct s_philosopher *, const char *, int);
	void			(*del)(struct s_philosopher *);
}					t_philosopher;

t_philosopher		*philosopher_new(void *table, size_t id,
					pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);
void				*philosopher_action(t_philosopher *self);
void				*philosopher_lifetime(t_philosopher *self);
void				philosopher_say(t_philosopher *self, const char *message,
									int is_die);

#endif
