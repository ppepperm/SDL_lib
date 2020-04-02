/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:00:32 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:36:37 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*tmp;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(tmp = (char*)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	ret = tmp;
	while (len1--)
	{
		*tmp = *s1++;
		tmp++;
	}
	while (len2--)
	{
		*tmp = *s2++;
		tmp++;
	}
	*tmp = 0;
	return (ret);
}
