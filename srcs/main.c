/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/27 14:31:07 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

/**
 * @brief read user input and tokenize input into linked list
 * 
 * @param m_var main variable which contains "ac, av, envp"
 * @return t_node* 
 * return a tokenize linked list
 */
t_node	*token_reader(t_main *m_var)
{
	char	*str;
	t_node	*lists;

	str = readline("minishell> ");
	if (str && *str)
		add_history(str);
	if (ft_strcmp(str, "exit") == 0)
	{
		free(str);
		system("leaks minishell");
		printf("Exit\n");
		exit(0);
	}
	else
	{
		lists = ft_node(0, NULL, 0, NULL);
		tokenize(m_var, str, &lists);
		free(str);
	}
	return (lists);
}

/**
 * @brief for now it get info on redirection \
 * @brief and create command groups for execution
 * 
 * @param m_var contains main variable "ac, av, envp"
 * @param lists tokenize linked list of 
 */
int	mini_main(t_main *m_var, t_node **lists)
{
	t_direct	*direct;
	t_cmds		*cmds;

	direct = director(lists);
	if (direct->error == 258)
		m_var->exit_code = direct->error;
	if (direct->error != 258)
	{
		cmds = grouping(m_var, *lists);
		set_direction(&direct, &cmds);
		if (function(m_var, &direct, &cmds) == 1)
		{
			printf("here\n");
			return (1);
		}
		free_cmds(&cmds);
	}
	free_direct(&direct);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_node	*lists;
	t_main	m_var;

	ft_init_main_var(&m_var, ac, av, envp);
	while (1)
	{
		lists = token_reader(&m_var);
		if (lists->val != NULL)
			if (mini_main(&m_var, &lists) == 1)
				return (1);
		free_lists(&lists);
		// printf("exit status: %i\n", m_var.exit_code);
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
