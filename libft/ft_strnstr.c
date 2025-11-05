/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:01:50 by arbutnar          #+#    #+#             */
/*   Updated: 2022/02/08 12:01:52 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;
	size_t	y;

	x = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[x] != '\0')
	{
		y = 0;
		while (haystack[x + y] == needle[y] && (x + y) < len)
		{
			if (haystack[x + y] == '\0' && needle[y] == '\0')
				return ((char *)&haystack[x]);
			y++;
		}
		if (needle[y] == '\0')
			return ((char *)&haystack[x]);
		x++;
	}
	return (0);
}
