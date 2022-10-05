/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:37:16 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/04 13:07:10 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// puts main arguments into t_main struct
// and converts envp into link-list
void	ft_init_main_var(t_main *main, int ac, char **av, char **envp)
{
	int	i;
	t_envp	*temp;

	main->ac = ac;
	main->av = av;
	main->envp = NULL;
	temp = NULL;
	i = -1;
	while (envp[++i] != NULL)
	{
		if (temp == NULL)
			temp = ft_calloc(1, sizeof(t_envp));
		else
		{
			temp->next = ft_calloc(1, sizeof(t_envp));
			temp = temp->next;
		}
		temp->val = envp[i];
		temp->next = NULL;
		if (main->envp == NULL)
			main->envp = temp;
	}
}

// init token variable
// takes in pointer to toke_var
// only thing that is changable during init is 
// length & string
// left and right is always 0
void	init_toke_var(t_toke_var *s, int len, char *temp)
{
	s->left = 0;
	s->right = 0;
	s->len = len;
	s->str = temp;
}

void	init_total(t_total **total)
{
	(*total) = ft_calloc(1, sizeof(t_total));
	(*total)->error = 0;
	(*total)->tol_heredoc = 0;
	(*total)->tol_pipes = 0;
	(*total)->delim = NULL;
	(*total)->heredoc = NULL;
	(*total)->fd_pipes = NULL;
}

void	init_groups(t_cmds **groups)
{
	(*groups) = ft_calloc(1, sizeof(t_cmds));
	(*groups)->args = NULL;
	(*groups)->heredoc_no = 0;
	(*groups)->input_fd = 0;
	(*groups)->output_fd = 1;
	(*groups)->next = NULL;
}