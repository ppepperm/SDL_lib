/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 10:13:11 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/15 12:15:07 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_kost(int mult)
{
	if (mult < 0)
		return (0);
	return (-1);
}

int			ft_atoi(const char *str)
{
	long long mult;
	long long nb;

	mult = 1;
	nb = 0;
	while ((*str == ' ') || (*str == '\t') || (*str == '\v') || (*str == '\f')\
			|| (*str == '\r') || (*str == '\n'))
		str++;
	if (*str == '-')
	{
		str++;
		mult = -1;
	}
	else if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if ((*str < '0') || (*str > '9'))
			return (nb * mult);
		if (nb > nb * 10 + (*str - '0') && nb != 214748364)
			return (ft_kost(mult));
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return ((int)(nb * mult));
}
