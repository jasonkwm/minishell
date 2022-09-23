/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:43:47 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/06 09:12:41 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sub_len(char const *s, size_t start, size_t len);

// return a substring of string s thats
// starts at index start and given length.
char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	len = sub_len(s, start, len);
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	i = -1;
	while (++i < len)
		sub[i] = s[start++];
	return (sub);
}

int	sub_len(char const *s, size_t start, size_t len)
{
	size_t	slen;

	slen = ft_strlen(s);
	if (start >= slen)
		return (0);
	if (slen < len)
		return (slen);
	return (len);
}
