/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:12:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/27 14:36:30 by jakoh            ###   ########.fr       */
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
		free(paths[i]);
	}
	free(paths);
	if (temp == NULL && (*cmds)->args[0] != NULL)
	{
		printf("minishell: %s: command not found\n", (*cmds)->args[0]);
		exit(127);
	}
	return (temp);
}

void	excevator(t_cmds **cmds)
{
	char    *path;
	int		i;

	i = -1;
	if ((*cmds)->args[0] == NULL)
		return ;
	path = get_path(cmds);
	execve(path, (*cmds)->args, (*cmds)->envp);
}

void	handle_io(t_cmds **cur)
{
	if ((*cur)->input != 0)
	{
		dup2((*cur)->input, 0);
		close((*cur)->input);
	}
	if ((*cur)->output != 1)
	{
		dup2((*cur)->output, 1);
		close((*cur)->input);
	}
}

int	function(t_main *m_var, t_direct **direct, t_cmds **cmds)
{
	t_cmds	*temp;
	pid_t	id;
	int		status;

	(void)m_var;
	temp = *cmds;
	while (temp != NULL)
	{
		id = fork();
		if (id < 0)
			return (-1);
		if (id == 0)
		{
			handle_io(&temp);
			ft_close_pipes(direct);
			excevator(&temp);
			exit(127);
		}
		temp = temp->next;	
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		m_var->exit_code = WEXITSTATUS(status);
	ft_close_pipes(direct);
	return (0);
}
