/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/03 18:47:27 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	run_execve(t_main *m_var, char **args);
void	free_total(t_total **total);

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
void	mini_main(t_main *m_var, t_node **lists)
{
	t_total	*total;

	(void)m_var;
	init_total(&total);
	get_total(lists, &total);
	if (total->tol_heredoc != 0)
	{
		malloc_heredoc(&total);
		get_delim(lists, &total);
		write_to_heredoc(&total);
	}
	if (total->error == 1)
	{
		free_total(&total);
		return ;
	}
	if (total->tol_pipes != 0)
		malloc_pipes(&total);
}

void	free_total(t_total **total)
{
	t_total	*temp;
	int		i;

	i = -1;
	temp = *total;
	if (temp->tol_heredoc != 0)
	{
		while (++i < temp->tol_heredoc)
		{
			free(temp->delim[i]);
			free(temp->heredoc[i]);
		}
		free(temp->delim);
		free(temp->heredoc);
	}

}

void	free_envp(t_envp **envp)
{
	t_envp *temp;
	t_envp *temp2;
	temp = *envp;
	temp2 = temp->next;
	while (temp != NULL)
	{
		free(temp->val);
		free(temp);
		temp = temp2;
		if (temp != NULL)
			temp2 = temp2->next;
	}
}
void	free_lists(t_node **lists);
int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_node  *lists;
	t_node  *temp;
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
		mini_main(&m_var, &lists);
	}
	return (0);
}

void	free_lists(t_node **lists)
{
	t_node	*temp;
	t_node	*temp2;
	
	temp = *lists;
	temp2 = temp->next;
	while (temp != NULL)
	{
		free(temp->val);
		free(temp);
		temp = temp2;
		if (temp != NULL)
			temp2 = temp2->next;
	}
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

/*
//convert linked list into array for execve
	tol_pipes = 0;
	i = 0;
	while (temp != NULL)
	{
		// if encounter < or > try to change to output or input 
		if (temp->type == PIPE)
		{
			tol_pipes++;
			break ;
		}
		else if (temp->type == REDIRECT)
		{
			if (temp->next == NULL)
			{
				printf("UNAVAILABLE TO REDIRECT\n");
				break ;
			}
			temp = temp->next->next;
		}
		else
		{
			++i;
			temp = temp->next;
		}
	}
	chain = ft_calloc(i + 1, sizeof(char *));
	int j = -1;
	temp = *lists;
	// int	file;
	while (temp != NULL)
	{
		if (temp->type == PIPE)
			break ;
		else if (temp->type == REDIRECT)
		{
			// redirector()
			temp = temp->next->next;
		}
		if (temp != NULL)
		{
			chain[++j] = ft_strdup(temp->val);
			temp = temp->next;
		}
	}
	chain[j + 1] = NULL;
*/


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