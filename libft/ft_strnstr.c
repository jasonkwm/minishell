/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:25:02 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/06 09:07:14 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Implementation of strnstr
// man strnstr for more info
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (*needle == 0)
		return ((char *)haystack);
	while (++i < len && haystack[i] != 0)
	{
		j = -1;
		while (haystack[i + (++j)] == needle[j] && (i + j) < len)
			if (needle[j + 1] == 0)
				return ((char *)(haystack + i));
	}
	return (0);
}
