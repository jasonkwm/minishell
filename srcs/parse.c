/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/27 21:46:08 by jakoh            ###   ########.fr       */
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
// also malloc for delim
void	malloc_size(t_total **total)
{
	t_total	*temp;
	int		i;

	temp = *total;
	temp->delim = ft_calloc(temp->tol_heredoc + 1, sizeof(char *));
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
	temp->delim = ft_calloc(temp->tol_heredoc + 1, sizeof(char *));
	temp->delim[temp->tol_heredoc] = NULL;
}

// string dup here_doc delimiter to total->delim
void	get_delim(t_node **lists, t_total **total)
{
	t_node	*cur_node;
	t_total	*cur_tol;
	int		i;

	i = 0;
	cur_node = *lists;
	cur_tol = *total;
	malloc_size(total);
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

// write to all the heredoc pipe
void    write_to_heredoc(t_total **total)
{
	t_total	*temp;
	char	*gnl;
	int		i;

	i = -1;
	temp = *total;
	gnl = NULL;
	while (++i < temp->tol_heredoc)
	{
		while (1)
		{
			gnl = readline("heredoc> ");
			if (ft_strlen(temp->delim[i]) == (ft_strlen(gnl))
				&& ft_strncmp(temp->delim[i], gnl, ft_strlen(temp->delim[i])) == 0)
				break;
			write(temp->fd_heredoc[i][1], gnl, ft_strlen(gnl));
			free(gnl);
		}
		close(temp->fd_heredoc[i][1]);
	}
	if (gnl)
		free(gnl);
}
