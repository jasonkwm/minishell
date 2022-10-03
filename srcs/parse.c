/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/03 17:36:36 by jakoh            ###   ########.fr       */
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
		if (is_token(temp->val) == 0)
		{
			if (temp->next == NULL)
				(*total)->error = syntax_error("newline");
			else if (is_token(temp->next->val) == 0)
				(*total)->error = syntax_error(temp->next->val);
			if ((*total)->error == 1)
				break ;
			if (ft_strcmp(temp->val, "<<") == 0)
				++((*total)->tol_heredoc);
			else if (temp->type == PIPE)
				++((*total)->tol_pipes);
		}
		temp = temp->next;
	}
}

