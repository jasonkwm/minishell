/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/03 13:25:51 by jakoh            ###   ########.fr       */
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
		if (temp->type == PIPE)
			(*total)->tol_pipes += 1;
		else if (ft_strcmp(temp->val, "<<") == 0)
		{
			if (temp->next == NULL)
			{
				(*total)->error = parse_error("\\n");
				break ;
			}
			else if (temp->next->type == PIPE || temp->next->type == REDIRECT)
			{
				(*total)->error = parse_error(temp->next->val);
				break ;
			}
			++((*total)->tol_heredoc);
		}
		temp = temp->next;
	}
}


/**
 * @brief 
 * get delimiter for each heredoc 
 * and store in malloc (*total)->delim 2d array
 * 
 * @param lists 
 * link list of tokenized input string.
 * @param total 
 * total contains info for pipes and here_doc
 */
void	get_delim(t_node **lists, t_total **total)
{
	t_node	*cur_node;
	t_total	*cur_tol;
	int		i;

	i = 0;
	cur_node = *lists;
	cur_tol = *total;
	
	while (cur_node != NULL && i < cur_tol->tol_heredoc)
	{
		if (ft_strcmp(cur_node->val, "<<") == 0)
		{
			if (cur_node->next == NULL)
				break ;
			else if (cur_node->next->type == PIPE || cur_node->next->type == REDIRECT)
				break ;
			cur_node = cur_node->next;
			cur_tol->delim[i] = ft_strdup(cur_node->val);
			i++;
		}
		cur_node = cur_node->next;
	}
}
