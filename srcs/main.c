/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/12 15:44:09 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

t_cmds	*grouping(t_main *m_var, t_node **lists, t_total **total);

void	mini_main(t_main *m_var, t_node **lists, t_total **total)
{
	t_total	*tol;

	tol = *total;
	if ((*lists)->type == PIPE)
	{
		(*total)->error = syntax_error((*lists)->val);
		return ;
	}
	get_total(lists, total);
	if (tol->tol_heredoc != 0)
	{
		malloc_heredoc(total);
		get_delim(lists, total);
		write_to_heredoc(total);
	}
	if (tol->error == 1)
		return ;
	if (tol->tol_pipes != 0)
		malloc_pipes(total);

	(void)m_var;
}

// THING TO DO :
// SIMPLIFIED GROUPING IN parse.c
// STORES EVERYTHING CORRECTLY
// COMBINE functions that does t_total & t_cmds together
// returns t_cmds groups for execution
int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_node  *lists;
	t_node  *temp;
	t_main  m_var;
	t_total	*total;
	t_cmds	*groups;

	ft_init_main_var(&m_var, ac, av, envp);
	lists = ft_node(0, NULL, 0, NULL);
	while (1)
	{
		str = readline("minishell> ");
		if (str && *str)
			add_history(str);
		if (ft_strcmp(str, "exit") == 0)
		{
			free(str);
			free_lists(&lists);
			// system("leaks minishell");
			printf("Exit\n");
			return (0);
		}
		if (ft_strcmp(str, "show") == 0)
		{
			temp = lists;
			while (temp != NULL)
			{
				printf("content: %s, type: %i\n", temp->val, temp->type);
				temp = temp->next;
			}
		}
		else
		{
			free_lists(&lists);
			lists = ft_node(0, NULL, 0, NULL);
			tokenize(&m_var, str, &lists);
			free(str);
		}
		init_total(&total);
		mini_main(&m_var, &lists, &total);
		if (total->error != 1)
			groups = grouping(&m_var, &lists, &total);
		ft_see_group(&groups);
		// ft_see(&lists);
		free_total(&total);
	}
	return (0);
}

/*
Operator -
Single Quotes   : ' (print string as string)
Double Quotes   : " (print string as string but expand $PATH)
Redirect Input  : <
Redirect Output : >
here_doc        : <<
Append Output   : >>
Pipe Operator   : |
Enviroment Var	: $PATH
Exit Status		: $?
Dollar Symbol	: $ (Only need to expland for enviroment variable)
*/

/*
Interactive -
ctrl + C	: New prompt on a newline
ctrl + D	: Exit Shell
ctrl + \	: Do Nothing
*/

/*
Commands -
echo	: with option '-n'
cd		: with only relative or absolute path
pwd		: no options
export	: no options
unset	: no options
env		: no options or args
exit	: no options
*/
