/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:35:54 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/15 13:36:23 by jakoh            ###   ########.fr       */
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
			break;
		temp = temp->next;
	}
	if (temp == NULL)
		return NULL;
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
