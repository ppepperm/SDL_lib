/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:24:16 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/13 18:20:24 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_puttnbr(int nb, char *dst)
{
	if (nb / 10 == 0)
	{
		*dst = nb % 10 + '0';
	}
	else
	{
		ft_puttnbr(nb / 10, dst + 1);
		*dst = nb % 10 + '0';
	}
}

static void	ft_marginalint(char *dst)
{
	char *src;

	src = "-2147483648";
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
}

char		*ft_itoa(int n)
{
	char *tmp;
	char *ret;

	tmp = (char*)malloc(sizeof(char) * 12);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, 12);
	ret = tmp;
	if (n == -2147483648)
	{
		ft_marginalint(tmp);
		return (ret);
	}
	if (n < 0)
	{
		n = n * -1;
		*tmp = '-';
		tmp++;
	}
	ft_puttnbr(n, tmp);
	ft_strrev(tmp);
	return (ret);
}
