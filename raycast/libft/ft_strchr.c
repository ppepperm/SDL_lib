/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:53:00 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:35:05 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char *ret;

	ret = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			ret = s;
			return ((char*)ret);
		}
		s++;
	}
	if (*s == (char)c)
		return ((char*)s);
	return ((char*)ret);
}
