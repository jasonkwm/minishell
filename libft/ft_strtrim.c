/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:28:45 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/06 09:10:49 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_first(char const *s1, char const *set);
int	get_last(char const *s1, char const *set);

// Trim/Remove spaces and tabs from the start and end of string.
char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	first = get_first(s1, set);
	last = get_last(s1, set);
	return (ft_substr(s1, first, (last - first + 1)));
}

int	get_first(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	have;

	i = -1;
	while (s1[++i] != 0)
	{
		j = -1;
		have = 0;
		while (set[++j] != 0)
			if (s1[i] == set[j])
				have++;
		if (have == 0)
			return (i);
	}
	return (i);
}

int	get_last(char const *s1, char const *set)
{
	int	j;
	int	len;
	int	have;

	len = ft_strlen(s1);
	while (--len != 0)
	{
		j = -1;
		have = 0;
		while (set[++j] != 0)
			if (s1[len] == set[j])
				have++;
		if (have == 0)
			return (len);
	}
	return (len);
}
