/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:11:55 by arbutnar          #+#    #+#             */
/*   Updated: 2022/02/06 18:11:57 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const t_byte	*str;

	str = s;
	while (n)
	{
		if (*str == (t_byte)c)
			return ((t_byte *)str);
		str++;
		n--;
	}
	return (0);
}
