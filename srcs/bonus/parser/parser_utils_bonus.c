/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:21:45 by challeau          #+#    #+#             */
/*   Updated: 2021/06/05 20:21:45 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

/*
** returns 1 if the strings are identical,
** 0 if one str is contained in the other,
** -1 if they are strictly different.
*/
int	ft_compare_strs(const char *str1, const char *str2)
{
	size_t	i;
	size_t	j;
	char	*s1;
	char	*s2;

	i = 0;
	j = 0;
	s1 = (char *)str1;
	s2 = (char *)str2;
	if (ft_strlen(str1) < ft_strlen(str2))
		swap_strs(&s1, &s2);
	while (s1[i])
	{
		while (s1[i + j] == s2[j])
		{
			if (s2[j] == '\0' && i == 0 && s1[i + j] == '\0')
				return (1);
			else if (s2[j] == '\0')
				return (0);
			j++;
		}
		i++;
	}
	return (-1);
}

/*
** checks the color value given in the source file is correct.
*/

bool	get_elem_color(const char *attribute, t_rgb *color)
{
	int		rgb[3];
	uint8_t	i;

	i = 0;
	while (i <= 2)
	{
		rgb[i] = ft_atoi(attribute);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (false);
		if (i++ != 2)
			attribute += ft_strchr(attribute, ',') + 1;
	}
	color->x = rgb[0];
	color->y = rgb[1];
	color->z = rgb[2];
	return (true);
}

/*
** checks the orientation value given in the source file is correct.
*/

bool	get_elem_orientation(const char *attribute, t_vec3f *ori)
{
	float	o[3];
	uint8_t	i;

	i = 0;
	while (i <= 2)
	{
		o[i] = ft_atof(attribute);
		if (o[i] < -1. || o[i] > 1.)
			return (false);
		if (i++ != 2)
			attribute += ft_strchr(attribute, ',') + 1;
	}
	ori->x = o[0];
	ori->y = o[1];
	ori->z = o[2];
	return (true);
}

/*
** checks the position value given in the source file is correct.
*/

bool	get_elem_position(const char *attribute, t_vec3f *pos)
{
	pos->x = ft_atof(attribute);
	attribute += ft_strchr(attribute, ',') + 1;
	pos->y = ft_atof(attribute);
	attribute += ft_strchr(attribute, ',') + 1;
	pos->z = ft_atof(attribute);
	return (true);
}
