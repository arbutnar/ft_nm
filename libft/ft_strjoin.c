/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:58:32 by arbutnar          #+#    #+#             */
/*   Updated: 2022/02/08 11:58:34 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = (ft_strlen(s1) + ft_strlen(s2));
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (0);
	while (*s1)
	{
			*res = *s1;
			res++;
			s1++;
	}
	while (*s2)
	{
			*res = *s2;
			res++;
			s2++;
	}
	*res = '\0';
	res = res - i;
	return (res);
}
