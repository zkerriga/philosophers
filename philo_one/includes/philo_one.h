/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:15:38 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/02 18:15:39 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "lib.h"

#define DEBUG 1 //TODO: delete this
#if DEBUG == 1
#include <stdio.h>
#define D(x) {x}
#else
#define D(x) {}
#endif

#endif
