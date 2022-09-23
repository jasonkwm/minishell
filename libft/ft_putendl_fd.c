/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:06:08 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/06 09:18:39 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Write '\n' to specific file descriptor
void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
		write(fd, "\n", 1);
	}
}
