/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:53:41 by arbutnar          #+#    #+#             */
/*   Updated: 2022/02/08 11:53:42 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	t_byte			*d;
	const t_byte	*s;

	d = dst;
	s = src;
	if (s < d)
	{
		while (len > 0)
		{
			*(d + len - 1) = *(s + len - 1);
			len--;
		}
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
