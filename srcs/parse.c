/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/27 21:04:19 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gets total number of pipes need
// number of heredoc pipes needed
// check if theres token error
// get heredoc delimiter
void	get_total(t_node **lists, t_total **total)
{
	t_node	*temp;

	temp = *lists;
	while (temp != NULL)
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

// malloc & pipe for pipe fd & here_doc fd
// also malloc for heredoc_Delim
void	malloc_size(t_node **lists, t_total **total)
{
	t_total	*temp;
	int		i;

	temp = *total;
	temp->heredoc_delim = ft_calloc(temp->tol_heredoc + 1, sizeof(char *));
	temp->fd_heredoc = ft_calloc(temp->tol_heredoc + 1, sizeof(int *));
	temp->fd_pipes = ft_calloc(temp->tol_pipes + 1, sizeof(int *));
	temp->fd_heredoc[temp->tol_heredoc] = NULL;
	temp->fd_pipes[temp->tol_pipes] = NULL;
	i = -1;
	while (++i < temp->tol_heredoc)
	{
		temp->fd_heredoc[i] = ft_calloc(2, sizeof(int));
		pipe(temp->fd_heredoc[i]);
	}
	i = -1;
	while (++i < temp->tol_pipes)
	{
		temp->fd_pipes[i] = ft_calloc(2, sizeof(int));
		pipe(temp->fd_pipes[i]);
	}
	temp->heredoc_delim = ft_calloc(temp->tol_heredoc + 1, sizeof(char *));
	temp->heredoc_delim[temp->tol_heredoc] == NULL;
}

// string dup here_doc delimiter to total->heredoc_delim
void	get_delim(t_node **lists, t_total **total)
{
	t_node	*cur_node;
	t_total	*cur_tol;
	int		i;

	i = -1;
	cur_node = *lists;
	cur_tol = *total;
	malloc_size(lists, total);
	while (cur_node != NULL)
	{
		if (ft_strcmp(cur_node->val, "<<") == 0)
		{
			if (cur_node->next == NULL)
				break ;
			else if (cur_node->next->type == PIPE || cur_node->next->type == REDIRECT)
				break ;
			cur_node = cur_node->next;
			cur_tol->heredoc_delim[++i] = ft_strdup(cur_node->val);
		}
		cur_node = cur_node->next;
	}
}

void    