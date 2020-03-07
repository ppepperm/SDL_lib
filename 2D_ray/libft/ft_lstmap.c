/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:23:13 by ppepperm          #+#    #+#             */
/*   Updated: 2019/09/12 18:32:09 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_del(void *content, size_t content_size)
{
	free(content);
	content_size = content_size - content_size;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*fres;
	t_list	*first_node;
	t_list	*node;

	if (!lst || !f)
		return (NULL);
	fres = f(lst);
	if (!(node = ft_lstnew(fres->content, fres->content_size)))
		return (NULL);
	lst = lst->next;
	first_node = node;
	while (lst)
	{
		fres = f(lst);
		node->next = ft_lstnew(fres->content, fres->content_size);
		if (!(node->next))
		{
			ft_lstdel(&first_node, ft_del);
			return (NULL);
		}
		node = node->next;
		lst = lst->next;
	}
	return (first_node);
}
