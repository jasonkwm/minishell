/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:12:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/26 18:36:38 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_path(t_cmds **cmds)
{
	char	**all;
	char	*temp;
	int		i;

	i = -1;
	all = NULL;
	if ((*cmds)->args[0] == NULL)
		return (NULL);
	while ((*cmds)->envp[++i] != NULL)
	{
		if (ft_strnstr((*cmds)->envp[i], "PATH", 4) != 0)
		{
			all = ft_split((*cmds)->envp[i] + 5, ':');
			break ;
		}
	}
	i = -1;
	while (all[++i] != NULL)
	{
		temp = all[i];
		all[i] = ft_strjoin(temp, "/");
		free(temp);
		temp = all[i];
		all[i] = ft_strjoin(temp, (*cmds)->args[0]);
		free(temp);
	}
	return (all);
}

char	*get_path(t_cmds **cmds)
{
	char	**paths;
	char	*temp;
	int		i;

	i = -1;
	temp = NULL;
	paths = find_path(cmds);
	while (paths[++i] != NULL)
	{
		if (access(paths[i], X_OK) != -1)
		{
			temp = ft_strdup(paths[i]);
			break;
		}
		if (access(paths[i], X_OK) == -1)
			printf("errno in loop: %i\n", errno);
		free(paths[i]);
	}
	free(paths);
	if (temp == NULL)
	{
		printf("errno: %i\n", errno);
		exit(errno);
	}
	return (temp);
}

void	excevator(t_cmds **cmds)
{
	char    **path;
	int		i;

	i = -1;
	if ((*cmds)->args[0] == NULL)
		exit(errno);
	path = find_path(cmds);
	while (path[++i] != NULL)
		execve(path[i], (*cmds)->args, (*cmds)->envp);
	exit(127);
}

void	handle_io(t_cmds **cur)
{
	if ((*cur)->input != STDIN_FILENO)
		dup2((*cur)->input, STDIN_FILENO);
	if ((*cur)->output != STDOUT_FILENO)
		dup2((*cur)->output, STDOUT_FILENO);
}

void	function(t_main *m_var, t_direct **direct, t_cmds **cmds)
{
	t_cmds	*temp;
	pid_t	id;
	int		i;
	int		status;

	(void)m_var;
	temp = *cmds;
	i = 0;
	while (temp != NULL)
	{
		id = fork();
		if (id < 0)
			return ;
		if (id == 0)
		{
			handle_io(&temp);
			ft_close_pipes(direct);
			excevator(&temp);
			return ;
		}
		else
		{
			if (waitpid(id, &status, WCONTINUED) == -1)
				perror("waitpid failed");
			if (WIFEXITED(status))
				m_var->exit_code = WEXITSTATUS(status);
		}
		++i;
		temp = temp->next;
	}
	ft_close_pipes(direct);
}
