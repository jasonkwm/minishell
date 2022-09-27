/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/27 21:03:56 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	run_execve(t_main *m_var, char **args);
void	mini_main(t_main *m_var, t_node **lists)
{
	t_total	*total;

	total = ft_calloc(1, sizeof(t_total));
	total->error = 0;
	total->tol_heredoc = 0;
	total->tol_pipes = 0;
	get_total(lists, &total);
	get_delim(lists, &total);
}

/*
typedef struct s_total
{
	int	error;
	int	tol_heredoc;
	int	tol_pipes;
	char	**heredoc_delim;
	int		*fd_pipes[2];
	int		*fd_heredoc[2];
}	t_total;
*/

t_cmds	**group_cmd(t_node **lists)
{
	t_node	*temp;
	t_cmds	**cmd_grps;
	int	tol_pipes;
	int	tol_heredoc;
	char	**heredoc_delim;
	int	hd_count;
	int	i;
	int	j;
	int	error;

	error = 0;
	tol_pipes = 0;
	tol_heredoc = 0;
	i = 0;
	j = -1;
	temp = *lists;
	// getting size of command groups
	// how many groups should there be
	// groups are seperated by pipes |
	while (temp != NULL)
	{
		if (temp->type == PIPE)
			tol_pipes++;
		else if (ft_strcmp(temp->val, "<<") == 0)
		{
			if (temp->next == NULL)
			{
				ft_putstr_fd("parse error near `\\n'\n", 2);
				error = 1;
				break ;
			}
			else if (temp->next->type == PIPE || temp->next->type == REDIRECT)
			{
				ft_putstr_fd("parse error near `", 2);
				ft_putstr_fd(temp->next->val, 2);
				ft_putstr_fd("'\n", 2);
				error = 1;
				break ;
			}
			++tol_heredoc;
		}
		temp = temp->next;
	}
	// Runs Heredoc
	// then check if there was a error before 
	// if error before 
	// then stop running program

	// malloc number of groups and stores heredoc delimiter
	// number of groups = number of pipes + 1 add 1 more to NULL terminate 2D
	// this is mostly for input and output 
	error = 0;
	cmd_grps = ft_calloc(tol_pipes + 1 + 1, sizeof(t_cmds));
	heredoc_delim = ft_calloc(tol_heredoc + 1, sizeof(char *));
	temp = *lists;
	cmd_grps[tol_pipes + 2] = NULL;
	hd_count = 0;
	cmd_grps[i]->heredoc_count = 0;
	while (temp != NULL && i < tol_pipes)
	{
		if (temp->type == PIPE)
		{
			++i;
			cmd_grps[i]->heredoc_count = 0;
			temp = temp->next;
			if (temp == NULL)
			{
				ft_putstr_fd("parse error near `\\n'\n", 2);
				error = 1;
				break ;
			}
		}
		else if (temp->type == REDIRECT)
		{
			if (temp->next == NULL)
			{
				ft_putstr_fd("parse error near `\\n'\n", 2);
				break ;
			}
			else if (temp->next->type == PIPE || temp->next->type == REDIRECT)
			{
				ft_putstr_fd("parse error near `", 2);
				ft_putstr_fd(temp->next->val, 2);
				ft_putstr_fd("'\n", 2);
				break ;
			}
			if (ft_strcmp(temp->val, "<") == 0)
			{
				if (ft_err_handle(temp->next->val, R_OK, 0) == 0)
					cmd_grps[i]->input_fd = open(temp->next->val, O_RDONLY);
			}
			else if (ft_strcmp(temp->val, ">") == 0)
			{
				cmd_grps[i]->output_fd = open(temp->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (cmd_grps[i]->output_fd == -1)
					ft_err_handle(temp->next->val, W_OK, 0);
			}
			else if (ft_strcmp(temp->val, ">>") == 0)
			{
				cmd_grps[i]->output_fd = open(temp->next->val, O_CREAT | O_RDWR | O_APPEND, 0644);
				if (cmd_grps[i]->output_fd == -1)
					ft_err_handle(temp->next->val, W_OK, 0);
			}
			else if (ft_strcmp(temp->val, "<<") == 0)
			{
				// fuck this dog shit
				++(cmd_grps[i]->heredoc_count);
				heredoc_delim[++j] = ft_strdup(temp->next->val);
			}
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	heredoc_delim[j] = NULL;
}

// int id;
// id = fork();
// if (id == 0)
// 	run_execve(m_var, chain);
// else
// 	wait(NULL);

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
			return (0) | printf("%s\n", str);
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
		}
		mini_main(&m_var, &lists);
	}
	return (0);
}

void	free_lists(t_node **lists)
{
	t_node	*cur_node;
	t_node	*temp;
	cur_node = *lists;
	while (cur_node != NULL)
	{
		temp = cur_node;
		cur_node = cur_node->next;
		free(temp->val);
		free(temp);
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