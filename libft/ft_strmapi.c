/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:21:08 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:37:07 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tmp;
	char	*ret;
	int		i;

	if (!f || !s)
		return (NULL);
	tmp = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tmp)
		return (NULL);
	ret = tmp;
	i = 0;
	while (*s)
	{
		*tmp = f(i, *s);
		s++;
		tmp++;
		i++;
	}
	*tmp = 0;
	return (ret);
}
