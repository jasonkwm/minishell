/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/11 14:29:19 by jakoh            ###   ########.fr       */
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


/**
 * @brief Create command group link list \
 * @brief set each groups input, output and arguments
 * 
 * @param m_var 
 * @param lists 
 * @param total 
 * 
 */
t_cmds	*grouping(t_main *m_var, t_node **lists, t_total **total)
{
	t_node	*temp;
	t_node	*temp2;
	t_cmds	*cmd_groups;
	t_cmds	*cur_group;
	int	num_args;
	int	hd;
	int i = -1;
	
	temp = *lists;
	hd = 0;
	num_args = 0;
	temp2 = get_num_args(&temp, &num_args, &hd);
	cmd_groups = cmd_groups_init(0, 1, ft_calloc(num_args + 1, sizeof(char *)), hd);
	cur_group = cmd_groups;
	cur_group->args[num_args] = NULL;
	while (temp != NULL && temp->val != NULL)
	{
		if (temp->type == PIPE)
		{
			num_args = 0;
			i = -1;
			temp2 = get_num_args(&(temp->next), &num_args, &hd);
			cur_group->next = cmd_groups_init(0, 1, ft_calloc(num_args + 1, sizeof(char *)), hd);
			cur_group = cur_group->next;
			cur_group->args[num_args] = NULL;
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
		else
			cur_group->args[++i] = ft_strdup(temp->val);
		temp = temp->next;
	}
	return (cmd_groups);
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
