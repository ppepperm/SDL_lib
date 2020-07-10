/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 12:53:13 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:37:35 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char *tmp;

	tmp = dest;
	while (n)
	{
		*tmp = *src;
		if (*src != 0)
			src++;
		tmp++;
		n--;
	}
	return (dest);
}
