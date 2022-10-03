/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:28:26 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/03 18:46:45 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Readline and string join '\n' if quote not found.
t_node	*here_quote(char *str, char quote, t_node **cur_node)
{
	char	*rl;
	char	*store;
	char	*temp;
	char	*schr;

	temp = ft_strjoin(str, "\n");
	free(str);
	while (1)
	{
		rl = readline("> ");
		store = ft_strjoin(temp, rl);
		free(temp);
		schr = ft_strchr(rl, quote);
		if (rl == schr || (schr != 0 && *(schr - 1) != '\\'))
			break ;
		temp = ft_strjoin(store, "\n");
		free(store);
		free(rl);
	}
	if (rl)
		free(rl);
	return (assign_node(cur_node, store, 2));
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

/**
 * @brief write/store heredoc 2d array in total
 * 
 * @param total 
 * contains info for pipes and here_doc
 */
void    write_to_heredoc(t_total **total)
{
	t_total	*temp;
	int		i;

	i = -1;
	temp = *total;
	while (++i < temp->tol_heredoc)
		temp->heredoc[i] = here_doc(temp->delim[i]);
}

/**
 * @brief keeps reading input, if input == delimiter then loop ends
 * 
 * @param delim
 * delimiter to stop readling line
 * @return char*
 * heredoc stored as string format.
 */
char	*here_doc(char *delim)
{
	char	*rl;
	char	*store;

	store = NULL;
	// printf("delim: %s\n", delim);
	while (1)
	{
		rl = readline("heredoc> ");
		if (ft_strcmp(rl, delim) == 0)
		{
			free(rl);
			break ;
		}
		if (store != NULL)
			store = sjoin_ext(store, ft_strdup("\n"));
		store = sjoin_ext(store, rl);
	}
	return (store);
}