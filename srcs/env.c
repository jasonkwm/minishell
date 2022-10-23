/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:35:54 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/20 15:48:21 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get specific enviroment variable from linked list envp
char	*get_ev(t_main *m_var, char *var)
{
	t_envp	*temp;

	temp = m_var->envp;
	while (temp != NULL)
	{
		if (ft_strnstr(temp->val, var, ft_strlen(var)) != 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (NULL);
	return (temp->val);
}

// add to end of envp linked list in m_var
void	add_env(t_main *m_var, char *str)
{
	t_envp	*temp;

	temp = m_var->envp;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = ft_calloc(1, sizeof(t_envp));
	temp->next->val = ft_strdup(str);
	temp->next->next = NULL;
}

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
