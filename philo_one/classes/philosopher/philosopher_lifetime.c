/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_lifetime.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:17:50 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 14:17:51 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher_lifetime(t_philosopher *self)
{
	D(printf("[+] Start lifetime for %ld philosopher!\n", self->id);)
	while (!(*self->born))
		;
	D(printf("[+] [lifetime] Philosopher %ld was BORN!\n", self->id);)
	return (THREAD_SUCCESS);
}
