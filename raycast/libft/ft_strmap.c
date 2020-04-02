/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:51:07 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:36:59 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *tmp;
	char *ret;

	if (!s || !f)
		return (NULL);
	tmp = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tmp)
		return (NULL);
	ret = tmp;
	while (*s)
	{
		*tmp = f(*s);
		s++;
		tmp++;
	}
	*tmp = 0;
	return (ret);
}
