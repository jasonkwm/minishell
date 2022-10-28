/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:59:14 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/28 16:24:12 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief sets input and output for processes \
 * @brief for execution
 * 
 * @param cur current command group
 * @param check to dup or not to dup
 * if check == 1 dup current input and output
 * else just close fd in cur intput and output
 */
void	handle_io(t_cmds **cur, int check)
{
	if (check == 1)
	{
		dup2((*cur)->input, 0);
		dup2((*cur)->output, 1);
	}
	if ((*cur)->input != 0)
		close((*cur)->input);
	if ((*cur)->output != 1)
		close((*cur)->output);
}

/**
 * @brief close all pipes in 'direct' this includes pipes fd and heredoc fd
 *
 * @param direct N/A
 */
void	ft_close_pipes(t_direct **direct)
{
	t_direct	*temp;
	int			i;

	i = -1;
	temp = *direct;
	if (temp->fd_pipes != NULL)
	{
		while (temp->fd_pipes[++i] != NULL)
		{
			close(temp->fd_pipes[i][0]);
			close(temp->fd_pipes[i][1]);
			free(temp->fd_pipes[i]);
		}
		free(temp->fd_pipes);
	}
	i = -1;
	if (temp->fd_heredoc != NULL)
	{
		while (temp->fd_heredoc[++i] != NULL)
		{
			close(temp->fd_heredoc[i][0]);
			free(temp->fd_heredoc[i]);
		}
		free(temp->fd_heredoc);
	}
}

char	**search_path(t_cmds **cmds)
{
	int	i;

	i = -1;
	while ((*cmds)->envp[++i] != NULL)
	{
		if (ft_strnstr((*cmds)->envp[i], "PATH", 4) != 0)
			return (ft_split((*cmds)->envp[i] + 5, ':'));
	}
	return (NULL);
}

/**
 * @brief returns a 2d array of all possible PATH for executable
 * 
 * @param cmds current command group
 * @return type: char **, 2d array of possible executable PATH 
 */
char	**find_path(t_cmds **cmds)
{
	char	**all;
	char	*temp;
	int		i;

	if ((*cmds)->args[0] == NULL)
		return (NULL);
	all = search_path(cmds);
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

/**
 * @brief Check if current path is executable 
 * if none of the paths is executable, command not found is printed 
 * and exit(127) is called;
 * @param cmds current command group
 * @return type: char *, executable path
 */
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
		if (access(paths[i], X_OK) != -1 && temp == NULL)
			temp = ft_strdup(paths[i]);
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
