/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:02:23 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/26 17:22:58 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if u wannt to check path with access() use type 1
// if u want to output "command not found error message" use type 0
// after printing out error message it will run exit();
int	ft_err_handle(char *path, int perm, int type)
{
	char	*s;

	if (type == 0)
	{
		if (access(path, perm) == -1)
		{
			s = strerror(errno);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd("\n", 2);
			exit(0);
		}
	}
	else if (type == 1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
	return (0);
}

// returns 1 to shorten code
int	syntax_error(char *msg)
{
	ft_putstr_fd("ms: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (258);
}
