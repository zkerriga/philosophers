/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:30:06 by zkerriga          #+#    #+#             */
/*   Updated: 2020/10/02 18:30:07 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	put_error(const char *error_str)
{
	const char	*set_color = "\033[33m";
	const char	*reset_color = "\033[0m";

	write(2, set_color, ft_strlen(set_color));
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
	write(2, reset_color, ft_strlen(reset_color));
}
