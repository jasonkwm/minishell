/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:02:23 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/03 09:59:05 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns 1 to shorten code
int	syntax_error(char *msg)
{
	ft_putstr_fd("ms: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (258);
}

void	call_exit(void)
{
	printf("exit\n");
	exit(0);
}
