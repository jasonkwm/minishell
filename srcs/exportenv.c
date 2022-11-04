/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:47:03 by edlim             #+#    #+#             */
/*   Updated: 2022/11/04 13:39:10 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gotequal(char *val)
{
	int	i;

	i = 0;
	while (val[i] != '\0')
	{
		if (val[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	export2(t_cmds **cmd_groups, t_envp *temp)
{
	if (gotequal((*cmd_groups)->args[1]) == 0)
	{
		while (temp != NULL)
		{
			if (strcmp(temp->key, (*cmd_groups)->args[1]) == 0)
				return (1);
			if (temp->next == NULL)
				break ;
			temp = temp->next;
		}
		temp->next = malloc(sizeof(t_envp));
		temp->next->key = ft_strdup((*cmd_groups)->args[1]);
		temp->next->val = NULL;
		temp->next->next = NULL;
		return (1);
	}
	return (0);
}

void	export(t_main *m_var, t_cmds **cmd_groups)
{
	t_envp	*temp;
	char	**split;

	temp = m_var->envp;
	if ((*cmd_groups)->args[1] == NULL)
	{
		while (temp != NULL)
		{
			printf("declare -x ");
			if (temp->val == NULL)
				printf("%s", temp->key);
			else
				printf("%s=", temp->key);
			if (temp->val != NULL)
				printf("\"%s\"", temp->val);
			printf("\n");
			temp = temp->next;
		}
		return ;
	}
	if (export2(cmd_groups, temp) == 1)
		return ;
	split = ft_split((*cmd_groups)->args[1], '=');
	exportutil(cmd_groups, temp, split);
}

void	env(t_main *m_var)
{
	t_envp	*temp;

	temp = m_var->envp;
	while (temp != NULL)
	{
		if (temp->val != NULL)
		{
			printf("%s=", temp->key);
			printf("%s\n", temp->val);
		}
		temp = temp->next;
	}
}

// Test cases
// export e
// export c=d
// any other command
// Will leak

// Test cases
// export e
// export c=d
// Won't leak