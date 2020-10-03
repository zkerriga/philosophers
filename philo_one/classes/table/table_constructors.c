/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_constructors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 09:13:39 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 09:15:35 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

static void	table_del(t_table *self)
{
	size_t	i;

	i = 0;
	while (i < self->quantity)
		pthread_mutex_destroy(&(self->forks_array[i++]));
	free(self);
	D(puts("[+] The table was deleted successfully!");)
}

static pthread_mutex_t	*create_forks_array(size_t quantity)
{
	pthread_mutex_t	*forks_array;
	size_t			i;

	if ((forks_array = malloc(sizeof(pthread_mutex_t) * quantity)))
	{
		i = 0;
		while (i < quantity)
		{
			if (pthread_mutex_init(&(forks_array[i]), NULL))
			{
				while (i)
					pthread_mutex_destroy(&(forks_array[--i]));
				return (NULL);
			}
			++i;
		}
	}
	return (forks_array);
}

t_table		*table_new(const t_args *args)
{
	t_table	*self;

	if ((self = (t_table *)malloc(sizeof(t_table))))
	{
		self->quantity = args->number_of_philosophers;
		if (!(self->forks_array = create_forks_array(self->quantity)))
		{
			free(self);
			return (NULL);
		}
		self->del = table_del;
		D(puts("[+] The table was created successfully!"))
	}
	return (self);
}