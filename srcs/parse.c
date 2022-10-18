/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/18 19:01:42 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the num arguments for each command group
 * 
 * @param lists tokenize list
 * @param num_args destination for num_args
 * @param hd destination for here doc
 * @return t_node* idk why i do this but apparently we dont need this
 */
t_cmds	*init_cur_group(t_node *lists, int *hd)
{
	int		num_args;

	num_args = 0;
	while (lists != NULL)
	{
		if (lists->type == PIPE)
			break ;
		else if (lists->type == REDIRECT)
		{
			if (ft_strcmp(lists->val, "<<") == 0)
				++(*hd);
			lists = lists->next;
		}
		else
			++num_args;
		lists = lists->next;
	}
	return (cmd_groups_init(0, 1, num_args, *hd));
}

/**
 * @brief Create command group link list \
 * @brief set each groups input, output and arguments
 * 
 * @param m_var main variable for ac, av & envp
 * @param lists tokenize lists
 * @param direct contains info about heredoc and pipes 
 * 
 */
t_cmds	*grouping(t_node *lists)
{
	t_cmds	*cmd_groups;
	t_cmds	*cur_group;
	int	hd;
	int i;
	int	check;
	
	hd = 0;
	i = -1;
	cmd_groups = init_cur_group(lists, &hd);
	cur_group = cmd_groups;
	while (lists != NULL && lists->val != NULL)
	{
		if (lists->type == PIPE || lists->type == REDIRECT)
		{
			check = function(lists, &cur_group, &i, &hd);
			if (check == -1)
				break;
			else if (check == 2)
				lists = lists->next;
		}
		else
			cur_group->args[++i] = ft_strdup(lists->val);
		lists = lists->next;
	}
	return (cmd_groups);
}
