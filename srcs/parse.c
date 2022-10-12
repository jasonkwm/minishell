/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/12 15:42:27 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Gets total number of pipes,
 * number of heredoc,
 * check if theres token error,
 * if error found then output error message.
 * 
 * @param lists 
 * link list of tokenized input string.
 * @param total 
 * total contains info for pipes and here_doc
 */
void	get_total(t_node **lists, t_total **total)
{
	t_node	*temp;

	temp = *lists;
	while (temp != NULL && temp->val != NULL)
	{
		get_tol_condition(total, temp);
		if ((*total)->error == 1)
			return ;
		temp = temp->next;
	}
}

/**
 * @brief extention of get_total function,
 * checks and print token error. And count number of 
 * pipes '|' and redirection '< > >> <<'
 * @param total 
 * total contains info for pipes and here_doc
 * @param cur_node 
 * current node in loop
 */
void	get_tol_condition(t_total **total, t_node *cur_node)
{
	if (cur_node->type == PIPE)
	{
		if (cur_node->next == NULL || cur_node->next->type == PIPE)
			(*total)->error = syntax_error(cur_node->val);
	}
	else if (cur_node->type == REDIRECT)
	{
		if (cur_node->next == NULL)
			(*total)->error = syntax_error("newline");
		else if (is_token(cur_node->next->val) == 0)
			(*total)->error = syntax_error(cur_node->next->val);
	}
	if ((*total)->error == 1)
		return ;
	if (ft_strcmp(cur_node->val, "<<") == 0)
		++((*total)->tol_heredoc);
	else if (cur_node->type == PIPE)
		++((*total)->tol_pipes);
}

/**
 * @brief Get the num arguments for each command group
 * 
 * @param lists tokenize list
 * @param num_args destination for num_args
 * @param hd destination for here doc
 * @return t_node* idk why i do this but apparently we dont need this
 */
t_node	*get_num_args(t_node **lists, int *num_args, int *hd)
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
	return (temp);
}

/**
 * @brief Create command group link list \
 * @brief set each groups input, output and arguments
 * 
 * @param m_var main variable for ac, av & envp
 * @param lists tokenize lists
 * @param total contains info about heredoc and pipes 
 * 
 */
t_cmds	*grouping(t_main *m_var, t_node **lists, t_total **total)
{
	t_node	*temp;
	t_node	*temp2;
	t_cmds	*cmd_groups;
	t_cmds	*cur_group;
	int	num_args;
	int	hd;
	int i = -1;
	
	temp = *lists;
	hd = 0;
	num_args = 0;
	temp2 = get_num_args(&temp, &num_args, &hd);
	cmd_groups = cmd_groups_init(0, 1, ft_calloc(num_args + 1, sizeof(char *)), hd);
	cur_group = cmd_groups;
	cur_group->args[num_args] = NULL;
	while (temp != NULL && temp->val != NULL)
	{
		if (temp->type == PIPE)
		{
			num_args = 0;
			i = -1;
			temp2 = get_num_args(&(temp->next), &num_args, &hd);
			cur_group->next = cmd_groups_init(0, 1, ft_calloc(num_args + 1, sizeof(char *)), hd);
			cur_group = cur_group->next;
			cur_group->args[num_args] = NULL;
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
	(void)m_var;
	(void)total;
}
