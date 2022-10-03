/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:18:39 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/03 13:40:03 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief malloc space for heredoc delimiter & heredoc,
 * heredoc is stored in string format.
 * 
 * @param total 
 * total is struct to store pipes & heredoc stuff
 */
void	malloc_heredoc(t_total **total)
{
	t_total	*temp;

	temp = *total;
	if (temp->tol_heredoc != 0)
	{
		temp->delim = ft_calloc(temp->tol_heredoc + 1, sizeof(char *));
		temp->delim[temp->tol_heredoc] = NULL;
		temp->heredoc = ft_calloc(temp->tol_heredoc + 1, sizeof(char *));
		temp->heredoc[temp->tol_heredoc] = NULL;
	}
}

void	malloc_pipes(t_total **total)
{
	t_total	*temp;
	int		i;
    
    temp = *total;
	if (temp->tol_pipes != 0)
	{
		temp->fd_pipes = ft_calloc(temp->tol_pipes + 1, sizeof(int *));
		temp->fd_pipes[temp->tol_pipes] = NULL;
		i = -1;
		while (++i < temp->tol_pipes)
		{
			temp->fd_pipes[i] = ft_calloc(2, sizeof(int));
			pipe(temp->fd_pipes[i]);
		}
	}
}
