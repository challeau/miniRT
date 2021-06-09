/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:21:45 by challeau          #+#    #+#             */
/*   Updated: 2021/06/05 20:21:45 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

/*
** returns the value of the enum corresponding to the element_type.
*/

int	id_index(const char *id)
{
	int					i;
	static const char	*elem_id_array[__ELEM_TOTAL] = {"R", "A", "C",
		"l", "sp", "pl", "cy"};

	i = 0;
	while (elem_id_array[i])
	{
		if (ft_compare_strs(id, elem_id_array[i]) == 1)
			return (i);
		i++;
	}
	return (-1);
}

/*
** swaps the contents of two strings.
*/

void	swap_strs(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
