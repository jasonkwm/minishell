/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:48:23 by edlim             #+#    #+#             */
/*   Updated: 2022/10/25 16:39:01 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo(t_cmds **cmd_groups)
{
	while ((*cmd_groups) != NULL)
	{
        if (!(*cmd_groups)->args[0])
			return ;
		if (ft_strcmp((*cmd_groups)->args[0], "echo") == 0)
        {
            
        }
		(*cmd_groups) = (*cmd_groups)->next;
        printf("HI");
	}
}

void builtins(t_main *m_var, t_cmds **cmd_groups)
{
    // echo(cmd_groups);
    cdpwd(m_var, cmd_groups);
}