/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:37:16 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/17 14:21:23 by jakoh            ###   ########.fr       */
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

t_direct	 *init_direct(void)
{
	t_direct	*tol;

	tol = ft_calloc(1, sizeof(t_direct));
	tol->error = 0;
	tol->tol_heredoc = 0;
	tol->tol_pipes = 0;
	tol->delim = NULL;
	tol->heredoc = NULL;
	tol->fd_pipes = NULL;
	return (tol);
}

t_cmds	*cmd_groups_init(int ipt, int opt, int num_args, int hd)
{
	t_cmds	*temp;

	temp = ft_calloc(1, sizeof(t_cmds));
	temp->input = ipt;
	temp->output = opt;
	temp->envp = NULL;
	temp->args = ft_calloc(num_args + 1, sizeof(char *));
	temp->args[num_args] = NULL;
	temp->heredoc_no = hd;
	temp->next = NULL;
	return (temp);
}
