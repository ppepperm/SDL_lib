/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:41:39 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:40:44 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dst;

	i = 0;
	while (*src)
	{
		src++;
		i++;
	}
	src -= i;
	dst = (char*)malloc(sizeof(*src) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = *src;
	return (dst - i);
}
