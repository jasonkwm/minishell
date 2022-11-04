/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:48:23 by edlim             #+#    #+#             */
/*   Updated: 2022/11/04 13:36:57 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_cmds **cmd_groups)
{
	int		i;
	char	*isn;

	i = 1;
	isn = (*cmd_groups)->args[i];
	if (isn == NULL)
	{
		printf("\n");
		return ;
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

void	unset(t_main *m_var, t_cmds **cmd_groups)
{
	t_envp	*temp;
	t_envp	*tofree;

	temp = m_var->envp;
	if ((*cmd_groups)->args[1] == NULL)
		return ;
	while (temp->next != NULL)
	{
		if (ft_strcmp(temp->next->key, (*cmd_groups)->args[1]) == 0)
		{
			free(temp->next->key);
			free(temp->next->val);
			tofree = temp->next;
			if (temp->next->next != NULL)
				temp->next = temp->next->next;
			else
				temp->next = NULL;
			free(tofree);
			return ;
		}
		temp = temp->next;
	}
}

void	exitbuiltin(t_main *m_var, t_cmds **cmd_groups)
{
	int	i;

	i = 0;
	tcsetattr(0, 0, &m_var->ogterm);
	printf("exit\n");
	if ((*cmd_groups)->args[1] != NULL)
	{
		while ((*cmd_groups)->args[1][i] != '\0')
		{
			if ((*cmd_groups)->args[1][i] < '0'
				|| (*cmd_groups)->args[1][i] > '9')
			{
				printf("minishell: exit: %s: numeric argument required\n",
					(*cmd_groups)->args[1]);
				exit(255);
			}
			i++;
		}
		exit(ft_atoi((*cmd_groups)->args[1]));
	}
	system("leaks minishell");
	exit(0);
}

void	builtins(t_main *m_var, t_cmds **cmd_groups)
{
	if (ft_strcmp((*cmd_groups)->args[0], "cd") == 0
		|| ft_strcmp((*cmd_groups)->args[0], "pwd") == 0)
		cdpwd(cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "echo") == 0)
		echo(cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "export") == 0)
		export(m_var, cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "env") == 0)
		env(m_var);
	else if (ft_strcmp((*cmd_groups)->args[0], "unset") == 0)
		unset(m_var, cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "exit") == 0)
		exitbuiltin(m_var, cmd_groups);
	(void)m_var;
}
