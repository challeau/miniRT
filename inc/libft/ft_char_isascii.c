/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_isascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:30:47 by challeau          #+#    #+#             */
/*   Updated: 2021/02/06 13:30:47 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_char_isascii(int c)
{
	bool	res;

	if (c >= 0 && c <= 127)
		res = true;
	else
		res = false;
	return (res);
}
