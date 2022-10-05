/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/04 18:39:48 by jakoh            ###   ########.fr       */
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
 * pipes '|' , redirection '< > >>' and here_doc '<<'
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