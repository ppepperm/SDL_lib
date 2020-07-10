/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:58:37 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/13 17:59:18 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_kostil(void)
{
	char *tmp;

	tmp = (char*)malloc(sizeof(char));
	*tmp = 0;
	return (tmp);
}

static char	get_ij(size_t *i, size_t *j, char const *s)
{
	if (!ft_strlen(s))
		return (0);
	*j = ft_strlen(s) - 1;
	while (s[*i] == ' ' || s[*i] == '\n' || s[*i] == '\t')
		(*i)++;
	if (*i >= *j)
		return (0);
	while (s[*j] == ' ' || s[*j] == '\n' || s[*j] == '\t')
		(*j)--;
	return ('a');
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	*ret;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!get_ij(&i, &j, s))
		return (ft_kostil());
	tmp = (char*)malloc(sizeof(char) * (j - i + 2));
	if (!(ret = tmp))
		return (NULL);
	while (i <= j)
	{
		*tmp = s[i++];
		tmp++;
	}
	*tmp = '\0';
	return (ret);
}
