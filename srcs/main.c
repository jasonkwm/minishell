/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/10 17:24:33 by jakoh            ###   ########.fr       */
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
	// grouping(m_var, lists, total);

	(void)m_var;
}

t_node	*get_num_args(t_node **lists, int *num_args, int *hd)
{
	t_node	*temp;

	temp = *lists;
	while (temp != NULL)
	{
		if (temp->type == PIPE)
			break ;
		else if (temp->type == REDIRECT)
		{
			if (ft_strcmp(temp->val, "<<") == 0)
				++(*hd);
			temp = temp->next;
		}
		else
			++(*num_args);
		temp = temp->next;
	}
	return (temp);
}

t_cmds	*cmd_groups_init(int ipt, int opt, char	**args, int hd)
{
	t_cmds	*temp;

	temp = ft_calloc(1, sizeof(t_cmds));
	temp->input = ipt;
	temp->output = opt;
	temp->envp = NULL;
	temp->args = args;
	temp->heredoc_no = hd;
	temp->next = NULL;
	return (temp);
}

/**
 * @brief 
 * create command group link list
 * set each groups input, output and arguments
 * 
 * @param m_var 
 * @param lists 
 * @param total 
 */
void	grouping(t_main *m_var, t_node **lists, t_total **total)
{
	// t_cmds	*groups;
	// int		i;
	// init_groups(&groups);
	t_node	*temp;
	t_node	*temp2;
	t_cmds	*cmd_groups;
	t_cmds	*cur_group;
	temp = *lists;
	
	int	num_args;
	int	hd;
	int i = -1;
	hd = 0;
	num_args = 0;
	temp2 = get_num_args(&temp, &num_args, &hd);
	cmd_groups = cmd_groups_init(0, 1, ft_calloc(num_args + 1, sizeof(char *)), hd);
	cur_group = cmd_groups;
	cur_group->args[num_args] = NULL;
	while (temp != NULL)
	{
		if (temp->type == PIPE)
		{
			num_args = 0;
			i = -1;
			temp2 = get_num_args(&(temp->next), &num_args, &hd);
			cur_group->next = cmd_groups_init(0, 1, ft_calloc(num_args + 1, sizeof(char *)), hd);
			cur_group = cur_group->next;
			cur_group->args[num_args] = NULL;
			printf("args: %d, hd: %d\n", num_args, hd);
		}
		else if (temp->type == REDIRECT)
		{
			if (ft_strcmp(temp->val, "<") == 0)
			{
				if (access(temp->next->val, R_OK) == -1)
				{
					printf("errno: %d, str: %s\n", errno, strerror(errno));
					break ;
				}
				cur_group->input = open(temp->next->val, O_RDONLY);
			}
			else if (ft_strcmp(temp->val, "<<") == 0)
				cur_group->input = -2;
			else if (ft_strcmp(temp->val, ">") == 0)
			{
				cur_group->output = open(temp->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (cur_group->output == -1)
				{
					if (access(temp->next->val, W_OK) == -1)
					{
						printf("errno: %d, str: %s\n", errno, strerror(errno));
						break ;
					}
				}
			}
			else if (ft_strcmp(temp->val, ">>") == 0)
			{
				cur_group->output = open(temp->next->val, O_CREAT | O_RDWR | O_APPEND, 0644);
				if (cur_group->output == -1)
				{
					if (access(temp->next->val, W_OK) == -1)
					{
						printf("errno: %d, str: %s\n", errno, strerror(errno));
						break ;
					}
				}
			}
			temp = temp->next;
		}
		else if (temp->type == CMD)
		{
			if (ft_strcmp(temp->val, "cd") == 0)
			{
				if (temp->next != NULL)
				{
					// If pipe should do nothing
					if (chdir(temp->next->val) == -1)
						printf("cd: no such file or directory: %s\n", temp->next->val);
				}
			}
			if (ft_strcmp(temp->val, "pwd") == 0)
			{
				char cwd[PATH_MAX];
				printf("%s\n", getcwd(cwd, sizeof(cwd)));
			}
		}
		else
			cur_group->args[++i] = ft_strdup(temp->val);
		temp = temp->next;
	}
	// ft_see_group(&cmd_groups);
	(void)m_var;
	(void)total;
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
			grouping(&m_var, &lists, &total);
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
