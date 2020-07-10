/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:16:27 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/15 16:08:14 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **head, t_list *node)
{
	t_list *save;

	if (!*head)
		*head = node;
	else
	{
		save = *head;
		while (save->next)
			save = save->next;
		save->next = node;
	}
}
