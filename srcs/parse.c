/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/17 14:33:01 by jakoh            ###   ########.fr       */
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
void	get_num_args(t_node **lists, int *num_args, int *hd)
{
	t_node	*temp;

	temp = *lists;
	while (temp != NULL)
	{
		if (temp->type == PIPE)
			break ;
		else if (temp->type == REDIRECT)
		{
			if (ft_strcmp(temp->val, "<<") == 0)
				++(*hd);
			temp = temp->next;
		}
		else
			++(*num_args);
		temp = temp->next;
	}
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
t_cmds	*grouping(t_node **lists)
{
	t_node	*temp;
	t_cmds	*cmd_groups;
	t_cmds	*cur_group;
	int	num_args;
	int	hd;
	int i = -1;
	
	temp = *lists;
	hd = 0;
	num_args = 0;
	get_num_args(&temp, &num_args, &hd);
	cmd_groups = cmd_groups_init(0, 1, num_args, hd);
	cur_group = cmd_groups;
	while (temp != NULL && temp->val != NULL)
	{
		if (temp->type == PIPE)
		{
			num_args = 0;
			i = -1;
			get_num_args(&(temp->next), &num_args, &hd);
			cur_group->next = cmd_groups_init(0, 1, num_args, hd);
			cur_group = cur_group->next;
		}
		else if (temp->type == REDIRECT)
		{
			if (ft_strcmp(temp->val, "<") == 0)
			{
				if (access(temp->next->val, R_OK) == -1)
				{
					printf("errno: %d, str: %s\n", errno, strerror(errno));
					break ;
				}
				cur_group->input = open(temp->next->val, O_RDONLY);
			}
			else if (ft_strcmp(temp->val, "<<") == 0)
				cur_group->input = -2;
			else if (ft_strcmp(temp->val, ">") == 0)
			{
				cur_group->output = open(temp->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (cur_group->output == -1)
				{
					if (access(temp->next->val, W_OK) == -1)
					{
						printf("errno: %d, str: %s\n", errno, strerror(errno));
						break ;
					}
				}
			}
			else if (ft_strcmp(temp->val, ">>") == 0)
			{
				cur_group->output = open(temp->next->val, O_CREAT | O_RDWR | O_APPEND, 0644);
				if (cur_group->output == -1)
				{
					if (access(temp->next->val, W_OK) == -1)
					{
						printf("errno: %d, str: %s\n", errno, strerror(errno));
						break ;
					}
				}
			}
			temp = temp->next;
		}
		else
			cur_group->args[++i] = ft_strdup(temp->val);
		temp = temp->next;
	}
	return (cmd_groups);
}
