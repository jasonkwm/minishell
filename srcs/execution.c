/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:12:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/28 15:34:20 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief execute non builtin functions
 * 
 * @param cmds current command group
 */
void	executor(t_cmds **cmds)
{
	char    *path;
	int		i;

	i = -1;
	if ((*cmds)->args[0] == NULL)
		return ;
	path = get_path(cmds);
	execve(path, (*cmds)->args, (*cmds)->envp);
	exit(127);
}

/**
 * @brief function to execute command group\
 * @brief this is where we fork processes to execute commands
 * 
 * @param m_var main variable contains envp and error code
 * @param direct contains all fd needed to handle input and output
 * @param cmds commands groups in linked list
 */
void	function(t_main *m_var, t_direct **direct, t_cmds **cmds)
{
	t_cmds	*temp;
	int		status;

	temp = *cmds;
	while (temp != NULL)
	{
		forker(&temp, direct);
		handle_io(&temp, 0);
		temp = temp->next;	
	}
	ft_close_pipes(direct);
	while (waitpid(-1, &status, WUNTRACED) > 0);
	m_var->exit_code = WEXITSTATUS(status);
	return ;
}

/**
 * @brief forking is done here
 * 
 * @param cur_cmd current command group
 * @param direct contains fd to close after dupping
 * @return pid_t 
 */
pid_t	forker(t_cmds **cur_cmd, t_direct **direct)
{
	pid_t	id;

	id = fork();
	if (id < 0)
		return (-1);
	if (id == 0)
	{
		handle_io(cur_cmd, 1);
		ft_close_pipes(direct);
		executor(cur_cmd);
		return (id);
	}
	return (id);
}