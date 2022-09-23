/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:45:46 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/06 09:15:32 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Duplicates a string.
char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	while (s1[i] != 0)
		++i;
	dup = ft_calloc(i + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != 0)
		dup[i] = s1[i];
	return (dup);
}
