/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:09:14 by edlim             #+#    #+#             */
/*   Updated: 2022/11/03 14:11:39 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export4(t_cmds **cmd_groups, t_envp *temp, char **split)
{
	char	*val;
	int		i;

	val = ft_strchr((*cmd_groups)->args[1], '=');
	val++;
	temp->next = malloc(sizeof(t_envp));
	temp->next->key = ft_strdup(split[0]);
	temp->next->val = ft_strdup(val);
	temp->next->next = NULL;
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

void	exportutil(t_cmds **cmd_groups, t_envp *temp, char **split)
{
	char	*val;
	int		i;

	while (temp != NULL)
	{
		if (strcmp(temp->key, split[0]) == 0)
		{
			i = -1;
			while (split[++i] != NULL)
				free(split[i]);
			free(split);
			val = ft_strchr((*cmd_groups)->args[1], '=');
			val++;
			if (temp->val != NULL)
				free(temp->val);
			temp->val = ft_strdup(val);
			return ;
		}
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	export4(cmd_groups, temp, split);
}
