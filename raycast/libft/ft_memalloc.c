/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:58:09 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:32:29 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *tmp;

	if (size <= 4294967296)
	{
		tmp = malloc(sizeof(char) * size);
		if (tmp)
			ft_bzero(tmp, size);
		return (tmp);
	}
	return (NULL);
}
