/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:00:13 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/18 16:21:28 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_envp **envp)
{
	t_envp *temp;
	t_envp *temp2;
	temp = *envp;
	temp2 = temp->next;
	while (temp != NULL)
	{
		free(temp->val);
		free(temp);
		temp = temp2;
		if (temp != NULL)
			temp2 = temp2->next;
	}
}

void	free_direct(t_direct **direct)
{
	t_direct	*temp;
	int		i;

	i = -1;
	temp = *direct;
	if (temp->delim != NULL)
	{
		while (temp->delim[++i] != NULL)
		{
			free(temp->delim[i]);
			free(temp->heredoc[i]);
		}
		free(temp->delim);
		free(temp->heredoc);
	}
	i = -1;
	if (temp->fd_pipes != NULL)
	{
		while (temp->fd_pipes[++i] != NULL)
			free(temp->fd_pipes[i]);
		free(temp->fd_pipes);
	}
    if (temp != NULL)
        free(temp);
}

void	free_lists(t_node **lists)
{
	t_node	*temp;
	t_node	*temp2;
	
	temp = *lists;
	temp2 = temp->next;
	while (temp != NULL)
	{
		free(temp->val);
		free(temp);
		temp = temp2;
		if (temp != NULL)
			temp2 = temp2->next;
	}
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*temp;
	int		i;
	temp = *cmds;
	while (temp != NULL)
	{
		i = -1;
		while (temp->args[++i] != NULL)
			free(temp->args[i]);
		free(temp->args);
		// i = -1;
		// while (temp->envp[++i] != NULL)
		// 	free(temp->envp[i]);
		// free(temp->envp);
		*cmds = (*cmds)->next;
		free(temp);
		temp = *cmds;
	}
}