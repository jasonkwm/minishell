/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:59:14 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/24 15:52:00 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_close_pipes(t_direct **direct)
{
	t_direct	*temp;
	int			i;

	i = -1;
	temp = *direct;
	if (temp->fd_pipes != NULL)
	{
		while (temp->fd_pipes[++i] != NULL)
		{
			close(temp->fd_pipes[i][0]);
			close(temp->fd_pipes[i][1]);
			free(temp->fd_pipes[i]);
		}
		free(temp->fd_pipes);
	}
	i = -1;
	if (temp->fd_heredoc != NULL)
	{
		while (temp->fd_heredoc[++i] != NULL)
		{
			close(temp->fd_heredoc[i][0]);
			free(temp->fd_heredoc[i]);
		}
		free(temp->fd_heredoc);
	}
}
