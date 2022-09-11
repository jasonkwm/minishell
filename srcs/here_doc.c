/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:28:26 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/11 18:53:38 by jakoh            ###   ########.fr       */
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
