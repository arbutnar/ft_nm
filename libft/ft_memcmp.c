/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:52:51 by arbutnar          #+#    #+#             */
/*   Updated: 2022/02/08 11:52:53 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const t_byte	*str1;
	const t_byte	*str2;

	str1 = s1;
	str2 = s2;
	if (n)
	{
		while (n--)
		{
			if (*str1 != *str2)
				return (*str1 - *str2);
			str1++;
			str2++;
		}
	}
	return (0);
}
