/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:07:24 by arbutnar          #+#    #+#             */
/*   Updated: 2022/02/06 18:07:26 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst1;
	t_list	*tmp;

	if (*lst)
	{
		lst1 = *lst;
		while (lst1)
		{
			tmp = lst1;
			(del)(lst1->content);
			lst1 = lst1->next;
			free(tmp);
		}
	}
	*lst = NULL;
}
