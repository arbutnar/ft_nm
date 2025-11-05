/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:59:32 by arbutnar          #+#    #+#             */
/*   Updated: 2022/02/08 11:59:33 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	if ((ft_strlen(src) + 1) <= dstsize)
		ft_memcpy(dst, src, (ft_strlen(src) + 1));
	else if (dstsize)
	{
		ft_memcpy(dst, src, (dstsize - 1));
		dst[dstsize - 1] = '\0';
	}
	return (ft_strlen(src));
}
