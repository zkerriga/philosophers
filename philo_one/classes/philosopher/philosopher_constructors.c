/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_constructors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 09:20:20 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 09:20:22 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void		philosopher_del(t_philosopher *self)
{
	free(self);
	D(puts("[+] A philosopher was deleted successfully!"))
}

t_philosopher	*philosopher_new(const t_args *args, const int *born, size_t id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	t_philosopher	*self;

	if ((self = (t_philosopher *)malloc(sizeof(t_philosopher))))
	{
		self->id = id;
		self->born = born;
		self->stats = args;
		self->forks.left = left_fork;
		self->forks.right = right_fork;
		pthread_create(&self->actions, NULL, philosopher_action, self); //TODO: check error
		pthread_create(&self->lifetime, NULL, philosopher_lifetime, self); //TODO: check error
		self->del = philosopher_del;
		D(puts("[+] A philosopher was created successfully!"))
	}
	return (self);
}
