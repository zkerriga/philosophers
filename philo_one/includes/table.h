/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 09:15:45 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 09:16:02 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include "lib.h"
# include "philosopher.h"

typedef struct		s_table
{
	size_t			quantity;
	int				born;
	pthread_mutex_t	output;
	pthread_mutex_t	*forks_array;
	t_philosopher	**philosophers_array;
	void			(*start_simulation)(struct s_table *);
	void			(*del)(struct s_table *);
}					t_table;

t_table				*table_new(const t_args *args);
void				table_start_simulation(t_table *self);

#endif
