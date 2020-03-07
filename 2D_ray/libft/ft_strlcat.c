/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:17:47 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:36:45 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t len;

	i = 0;
	while (dst[i] != 0 && i < size)
		i++;
	len = i;
	while (src[i - len] != 0 && (i + 1) < size)
	{
		dst[i] = src[i - len];
		i++;
	}
	if (len < size)
		dst[i] = 0;
	return (len + ft_strlen(src));
}
