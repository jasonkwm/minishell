/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:51:49 by edlim             #+#    #+#             */
/*   Updated: 2022/10/11 20:51:50 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cdpwd(t_main *m_var, t_cmds **cmd_groups)
{
	char	cwd[PATH_MAX];

	while ((*cmd_groups) != NULL)
	{
		if (ft_strcmp((*cmd_groups)->args[0], "cd") == 0)
		{
			// If pipe should do nothing
			if ((*cmd_groups)->args[1] != NULL)
			{
				if (chdir((*cmd_groups)->args[1]) == -1)
					printf("cd: no such file or directory: %s\n",
						(*cmd_groups)->args[1]);
			}
		}
		else if (ft_strcmp((*cmd_groups)->args[0], "pwd") == 0)
		{
			printf("%s\n", getcwd(cwd, sizeof(cwd)));
		}
		(*cmd_groups) = (*cmd_groups)->next;
	}
	(void)m_var;
}

// Do I even need m_var here