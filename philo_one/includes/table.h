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
	pthread_mutex_t	*forks_array;
	t_philosopher	**philosophers_array;
	void			(*del)(struct s_table *);
}					t_table;

t_table				*table_new(const t_args *args);

#endif
