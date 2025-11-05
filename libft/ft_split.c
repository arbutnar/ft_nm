/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbutnar <arbutnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:56:35 by arbutnar          #+#    #+#             */
/*   Updated: 2022/02/08 11:56:37 by arbutnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	s_count(char const *s, char c)
{
	size_t		i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

char const	*ft_split_support(char const *s, char c)
{
	while (*s && *s != c)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char		**matrix;
	char		*start;
	size_t		i;
	size_t		len;

	if (!s)
		return (0);
	matrix = ft_calloc(s_count(s, c) + 1, sizeof(*matrix));
	if (!matrix)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			s = ft_split_support(s, c);
			len = s - start + 1;
			matrix[i] = ft_calloc(len, sizeof(**matrix));
			ft_strlcpy(matrix[i++], start, len);
		}
		else
			s++;
	}
	return (matrix);
}
