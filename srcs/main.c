/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/17 14:37:02 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	mini_main(t_main *m_var, t_node **lists)
{
	t_direct	*direct;
	t_cmds		*cmds;

	direct = director(lists);
	if (direct->error != 1)
		cmds = grouping(lists);
	free_direct(&direct);
	(void)m_var;
}

// THING TO DO :
// SIMPLIFIED GROUPING IN parse.c
// STORES EVERYTHING CORRECTLY
// COMBINE functions that does t_direct & t_cmds together
// returns t_cmds groups for execution
int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_node  *lists;
	t_main  m_var;

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
		else
		{
			free_lists(&lists);
			lists = ft_node(0, NULL, 0, NULL);
			tokenize(&m_var, str, &lists);
			free(str);
		}
		mini_main(&m_var, &lists);
		// ft_see(&lists);
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
