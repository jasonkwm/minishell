/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:28:26 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/30 12:25:05 by jakoh            ###   ########.fr       */
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

// write to all the heredoc pipe
void    write_to_heredoc(t_total **total)
{
	t_total	*temp;
	int		i;

	i = -1;
	temp = *total;
	while (++i < temp->tol_heredoc)
	{
		printf("temp->delim[i]: %s\n", temp->delim[i]);
		temp->heredoc[i] = here_doc(temp->delim[i]);
	}
	printf("heredoc: %s\n", temp->heredoc[i - 1]);
}


char	*here_doc(char *delim)
{
	char	*rl;
	char	*store;

	store = NULL;
	while (1)
	{
		rl = readline("heredoc> ");
		if (ft_strlen(delim) == (ft_strlen(rl))
				&& ft_strncmp(delim, rl, ft_strlen(delim) - 1) == 0)
				break;
		if (store != NULL)
			store = sjoin_ext(store, ft_strdup("\n"));
		store = sjoin_ext(store, rl);
	}
	if (rl)
		free(rl);
	return (store);
}