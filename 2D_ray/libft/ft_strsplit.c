/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:43:26 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:38:13 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	speclen(const char *str, char delim)
{
	int i;

	i = 0;
	while (*str != delim && *str)
	{
		i++;
		str++;
	}
	return (i);
}

static char		*ft_memcpyend(char *dst, const char *src, char delim)
{
	ft_memcpy(dst, src, speclen(src, delim));
	*(dst + speclen(src, delim)) = 0;
	return (dst);
}

static size_t	ft_count(const char *str, char delim)
{
	size_t	count;
	int		slovo;
	int		probel;

	slovo = 0;
	count = 0;
	probel = 1;
	while (*str)
	{
		if (*str != delim && probel)
		{
			probel = 0;
			slovo = 1;
			count++;
		}
		if (*str == delim && slovo)
		{
			probel = 1;
			slovo = 0;
		}
		str++;
	}
	return (count);
}

static char		**ft_free(char **src, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		free(src[i]);
		i++;
	}
	free(src);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tmp;
	size_t	i;
	int		flag;

	if (!s || !c)
		return (NULL);
	flag = 1;
	i = 0;
	if (!(tmp = (char**)malloc(sizeof(char*) * (ft_count(s, c) + 1))))
		return (NULL);
	tmp[ft_count(s, c)] = 0;
	while (*(s))
	{
		if (flag && *(s) != c)
		{
			if (!(tmp[i] = (char*)malloc(sizeof(char) * (speclen(s, c) + 1))))
				return (ft_free(tmp, i + 1));
			ft_memcpyend(tmp[i++], s, c);
		}
		flag = 0;
		if (*(s) == c)
			flag = 1;
		s++;
	}
	return (tmp);
}
