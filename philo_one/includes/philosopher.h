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

#include "lib.h"

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
	void			(*del)(struct s_philosopher *);
}					t_philosopher;

t_philosopher		*philosopher_new(const t_args *args, const int *born, size_t id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);

void				*philosopher_action(t_philosopher *self);
void				*philosopher_lifetime(t_philosopher *self);

#endif
