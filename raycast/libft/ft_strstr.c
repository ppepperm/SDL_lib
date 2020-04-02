/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:43:26 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:38:19 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	const char *s;
	const char *t;

	if (*to_find == '\0')
		return ((char*)str);
	while (*str != '\0')
	{
		s = str;
		t = to_find;
		while (*s == *t)
		{
			if (*(t + 1) == '\0')
				return ((char*)str);
			s++;
			t++;
		}
		str++;
	}
	return (NULL);
}
