/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:12:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/25 14:40:31 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(t_cmds **cmds)
{
	char	**temp;
	int		i;

	i = -1;
	temp = NULL;
	while ((*cmds)->envp[++i] != NULL)
	{
		if (ft_strnstr((*cmds)->envp[i], "PATH", 4) != 0)
		{
			temp = ft_split((*cmds)->envp[i] + 5, ':');
			break ;
		}
	}
	i = -1;
	while (temp[++i] != NULL)
		printf("temp: %s\n", temp[i]);
}

// char	**get_path(t_cmds **cmds)
// {

// }

// void	excevator(t_cmds **cmds)
// {
// 	char    **path;

// }

// void	function(t_main *m_var, t_direct **direct, t_cmds **cmds)
// {
// 	t_cmds	*temp;
// 	int		id;
// 	int		i;

// 	temp = *cmds;
// 	i = 0;
// 	while (temp != NULL)
// 	{
// 		id = fork();
// 		if (id < 0)
// 			return ;
// 		if (id == 0)
// 		{
// 			handle_io(direct, temp);
// 			ft_close_pipes(direct);
// 			excevator(cmds);
// 			// run executor
// 			// do child thing
// 		}
// 		++i;
// 		temp = temp->next;
// 	}
// 	ft_close_pipes(direct);
// }

// void	handle_io(t_direct **direct, t_cmds **cur)
// {
// 	if ((*cur)->input != STDIN_FILENO)
// 		dup2((*cur)->input, STDIN_FILENO);
// 	if ((*cur)->output != STDOUT_FILENO)
// 		dup2((*cur)->output, STDOUT_FILENO);
// }
