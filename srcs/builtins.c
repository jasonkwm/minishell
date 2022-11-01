/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:48:23 by edlim             #+#    #+#             */
/*   Updated: 2022/11/01 17:42:03 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo(t_cmds **cmd_groups)
{
	int i;
	char *isn;

	i = 1;
	isn = (*cmd_groups)->args[i];
	if (isn == NULL)
	{
		printf("\n");
		return;
	}
	if (ft_strcmp(isn, "-n") == 0)
		++i;
	while ((*cmd_groups)->args[i] != NULL)
	{
		printf("%s", (*cmd_groups)->args[i]);
		++i;
		if ((*cmd_groups)->args[i] != NULL)
			printf(" ");
	}
	if (ft_strcmp(isn, "-n") != 0)
		printf("\n");
}

// void	unset(t_main *m_var, t_cmds **cmd_groups)
// {
// 	t_envp *temp;

// 	temp = m_var->envp;
// 	while (temp != NULL)
// 	{
// 		if (temp->val == )
// 		temp = temp->next;
// 	}
// }

void builtins(t_main *m_var, t_cmds **cmd_groups)
{
	if (ft_strcmp((*cmd_groups)->args[0], "cd") == 0 || ft_strcmp((*cmd_groups)->args[0], "pwd") == 0)
		cdpwd(cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "echo") == 0)
		echo(cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "export") == 0)
		export(m_var, cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "env") == 0)
		env(m_var);
	// else if (ft_strcmp((*cmd_groups)->args[0], "env") == 0)
		// unset(m_var, cmd_groups);
	(void)m_var;
}
