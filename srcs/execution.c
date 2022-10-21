/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:12:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/21 12:57:17 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// ft_close_pipes(t_direct **direct);

// void    function(t_main *m_var, t_direct **direct, t_cmds **cmds)
// {
// 	t_cmds *temp;
// 	int     id;
	
// 	temp = *cmds;
// 	while (temp != NULL)
// 	{
// 		id = fork();
// 		if (id < 0)
// 			return ;
// 		if (id == 0)
// 		{
// 			// 
// 			// dup2 input and output
// 			// run executor
// 			// do child thing
// 		}
// 	}
// }

// ft_close_pipes(t_direct **direct)
// {
// 	t_direct	*temp;
// 	int			i;

// 	i = -1;
// 	temp = *direct;
// 	while (++i < temp->tol_pipes)
// 	{
// 		close(temp->fd_pipes[i][0]);
// 		close(temp->fd_pipes[i][1]);
// 		free(temp->fd_pipes[i]);
// 	}
// 	free(temp->fd_pipes);
// }