/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:12:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/24 16:33:37 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    function(t_main *m_var, t_direct **direct, t_cmds **cmds)
// {
// 	t_cmds *temp;
// 	int     id;
// 	int		i;

// 	temp = *cmds;
// 	i = 0;
// 	while (temp != NULL)
// 	{
// 		id = fork();
// 		if (id < 0)
// 			return ;
// 		if (id == 0)
// 		{
// 			// dup2 input and output and set file for here_doc
// 			handle_io(direct, temp, i);
// 			// run executor
// 			// do child thing
// 			ft_close_pipes(direct);
// 		}
// 		++i;
// 		temp = temp->next;
// 	}
// 	ft_close_pipes(direct);
// }

// void	handle_io(t_direct **direct, t_cmds **cur, int i)
// {
// 	if (i == 0)
// 	{
// 		dup2((*direct)->fd_pipes[i][1], 1);
// 	}
// }
