/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:33:57 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/20 14:00:30 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief counts and converts envp in m_var into a 2d string
 * 
 * @param m_var main variable that contains ac av and (envp in linked list format)
 * 
 * @return type:char **, envp in 2D String
 */
char	**envp_converter(t_main *m_var)
{
	t_envp  *temp;
	char	**env;
	int		i;

	i = 0;
	temp = m_var->envp;
	while (temp != NULL)
	{
		temp = temp->next;
		++i;
	}
	env = ft_calloc(i + 1, sizeof(char *));
	env[i] = NULL;
	temp = m_var->envp;
	i = -1;
	while (temp != NULL)
	{
		env[++i] = ft_strdup(temp->val);
		temp = temp->next;
	}
	return (env);
}

/**
 * @brief converts envp linked list into 2d char * and store in cmd_groups->envp
 * 
 * @param m_var main variable that contains ac av and (envp in linked list format)
 * @param cmd_groups cmd_groups to be executed.
 */
void	add_envp(t_main *m_var, t_cmds **cmd_groups)
{
	t_cmds	*temp;
	char	**env;

	temp = *cmd_groups;
	env = envp_converter(m_var);
	while (temp != NULL)
	{
		temp->envp = env;
		temp = temp->next;
	}
}
