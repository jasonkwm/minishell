/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:28:26 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/11 16:58:21 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Readline and string join '\n' if quote not found.
t_node	*ft_here_quotes(char *str, char quote, t_node **cur_node)
{
    char	*rl;
    char    *store;
    char    *temp;

	temp = ft_strjoin(str, "\n");
    while (1)
    {
        rl = readline("> ");
        store = ft_strjoin(temp, rl);
        free(temp);
        if (ft_strchr(rl, quote) != 0)
            break;
        temp = ft_strjoin(store, "\n");
        free(store);
        free(rl);
    }
    if (rl)
        free(rl);
	return (assign_node(cur_node, store, 2));
}

