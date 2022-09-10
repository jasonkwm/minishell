/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:28:26 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/10 17:17:09 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create temp file called "rl_quote"
// After readling line from stdin with readline
// it will first write to temp file "rl_quote"
// before checking whether quote is in line
t_node	*ft_here_quotes(char *str, char quote, t_node **list)
{
    char	*rl;
	int		temp_fd;
    t_node  *temp;

    temp = *list;
	temp_fd = open("rl_quote", O_CREAT | O_RDWR | O_APPEND, 0644);
	rl = NULL;
	write(temp_fd, str, ft_strlen(str));
	write(temp_fd, "\n", 1);
	free(str);
    while (1)
    {
        rl = readline("> ");
        write(temp_fd, rl, ft_strlen(rl));
        if (ft_strchr(rl, quote) != 0)
            break;
		write(temp_fd, "\n", 1);
        free(rl);
    }
    if (rl)
        free(rl);
    temp->val = "rl_quote";
    temp->type = 5;
    temp->next = ft_node(temp->id + 1, NULL, 0, &temp);
	return (temp->next);
}