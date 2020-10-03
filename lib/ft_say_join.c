/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_say_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:04:33 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/03 18:04:34 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_say_join(const char *time, const char *nbr, const char *message)
{
	size_t	len_time;
	size_t	len_nbr;
	size_t	len_mes;
	char	*new_str;

	len_time = ft_strlen(time);
	len_nbr = ft_strlen(nbr);
	len_mes = ft_strlen(message);
	new_str = (char *)malloc(sizeof(char) * (len_mes + len_time + len_nbr + 4));
	if (new_str)
	{
		ft_strlcpy(new_str, time, len_time + 1);
		new_str[len_time] = ' ';
		ft_strlcpy(&new_str[len_time + 1], nbr, len_nbr + 1);
		new_str[len_time + 1 + len_nbr] = ' ';
		ft_strlcpy(&new_str[len_time + len_nbr + 2], message, len_mes + 1);
		new_str[len_time + len_nbr + len_mes + 2] = '\n';
		new_str[len_time + len_nbr + len_mes + 3] = '\0';
	}
	return (new_str);
}
