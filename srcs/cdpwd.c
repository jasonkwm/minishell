/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:51:49 by edlim             #+#    #+#             */
/*   Updated: 2022/10/28 15:58:11 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cdpwd(t_cmds **cmd_groups)
{
	char	cwd[PATH_MAX];

	if (ft_strcmp((*cmd_groups)->args[0], "cd") == 0)
	{
		// If pipe should do nothing
		if ((*cmd_groups)->args[1] != NULL)
		{
			if (ft_strcmp((*cmd_groups)->args[1], "~") == 0)
				chdir(getenv("HOME"));
			else if (chdir((*cmd_groups)->args[1]) == -1)
				printf("cd: no such file or directory: %s\n",
					(*cmd_groups)->args[1]);
		}
		else
			chdir(getenv("HOME"));
	}
	else if (ft_strcmp((*cmd_groups)->args[0], "pwd") == 0)
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
