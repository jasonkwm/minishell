/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/05 11:46:59 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	run_execve(t_main *m_var, char **args);
void	grouping(t_main *m_var, t_node **lists, t_total **total);

void	mini_main(t_main *m_var, t_node **lists, t_total **total)
{
	t_total	*tol;

	tol = *total;
	if ((*lists)->type == PIPE)
	{
		syntax_error((*lists)->val);
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
	grouping(m_var, lists, total);
	(void)m_var;
}

void	grouping(t_main *m_var, t_node **lists, t_total **total)
{
	// t_cmds	*groups;
	// int		i;
	// init_groups(&groups);
	t_node	*temp;

	temp = *lists;
	(void)m_var;
	(void)total;
	while (temp != NULL)
	{
		printf("lists id: %i, val: %s, type: %i\n", temp->id, temp->val, temp->type);
		temp = temp->next;
		// if 
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_node  *lists;
	t_node  *temp;
	t_main  m_var;
	t_total	*total;

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
			system("leaks minishell");
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

// echo if echo met < or > do as the operator expects. 
// if echo met quotes ' or " then continue finding that quote until the end of time
// if cant find quote then read line again and again until quote is found. 

void	run_execve(t_main *m_var, char **args)
{
	t_envp	*env;
	char	**split;
	char	*temp;
	char	*exec;
	int		i;
	env = m_var->envp;
	while (env != NULL)
	{
		if (ft_strnstr(env->val, "PATH", ft_strlen("PATH")) != 0)
			break ;
		env = env->next;
	}
	if (env == NULL)
	{
		printf("PATH NOT FOUND IN ENVIROMENT\n");
		system("leaks minishell");
		exit(2);
	}
	split = ft_split(env->val + ft_strlen("PATH="), ':');
	i = -1;
	while (split[++i] != NULL)
	{
		// if (access(args[0], X_OK) == 0)
		// 	break ;
		temp = ft_strjoin(split[i], "/");
		free(split[i]);
		split[i] = ft_strjoin(temp, args[0]);
		free(temp);
		if (access(split[i], X_OK) == 0)
		{
			exec = ft_strdup(split[i]);
			break;
		}
	}
	if (split[i] == NULL)
		exec = NULL;
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
	execve(exec, args, NULL);
	ft_err_handle(*args, 0, 1);
}