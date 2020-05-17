/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:04:50 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:37:59 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	lenn;

	lenn = ft_strlen(to_find);
	while (len >= lenn && *str)
	{
		len--;
		if (!ft_memcmp(str, to_find, lenn))
			return ((char*)str);
		str++;
	}
	return (NULL);
}
