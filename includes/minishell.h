/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:18 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/04 18:39:26 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

enum type
{
	NO_TYPE,
	CMD,
	ARG,
	REDIRECT,
	PIPE,
};

// type 0 = no type, 1 = command,
// 2 = arguments, 3 = redirections,
// 4 = pipe, 5 = here_doc file
typedef struct s_node
{
	int				id;
	char			*val;
	int				type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

// linked-list like data struct 
// to store enviroment variable
typedef struct s_envp
{
	char			*val;
	struct s_envp	*next;
}	t_envp;

// struct to store main parameters
typedef struct s_main
{
	int		ac;
	char	**av;
	t_envp	*envp;
}	t_main;

// tokenizing/parsing struct
// use to shorten code.
typedef struct s_toke_var
{
	int		left;
	int		right;
	int		len;
	char	*str;
}	t_toke_var;

/**
 * @brief stores
 * parsing error, total heredoc, total pipes,
 * delimiter in 2d char *,
 * heredocs as string in 2d  char *
 * fd for pipes in 2d int array,
 */
typedef struct s_total
{
	int	error;
	int	tol_heredoc;
	int	tol_pipes;
	char	**delim;
	int		**fd_pipes;
	char	**heredoc;
}	t_total;

typedef struct s_cmds
{
	int		input_fd;
	int		output_fd;
	int		heredoc_no;
	char	*args;
	struct s_cmds	*next;
}	t_cmds;

// checker.c
int		ft_strcmp(char *a, char *b);
int		is_built_in(char *str);
int		is_op(char c);
int		is_token(char	*str);

// inits.c
void	ft_init_main_var(t_main *main, int ac, char **av, char **envp);
void	init_toke_var(t_toke_var *s, int len, char *temp);
void	init_total(t_total **total);

// env.c
char	*get_ev(t_main *m_var, char *var);
void	add_env(t_main *m_var, char *str);

// node_utils.c
t_node	*ft_node(int  id, char *val, int type,  t_node **prev);
t_node	*assign_node(t_node **cur_node, char *val, int type);

// tokenize.c
void	tokenize(t_main *m_var, char *str, t_node	**tree);
void	to_lower(char *src, char **dest);

// expand.c
void	expand_env(t_main *m_var, t_node **cur_node);
void	expand_env_ext(t_main *m_var, t_node **cur_node, t_toke_var *s);
void	expand_env_ext_quote(t_main *m_var, t_node **cur_node, t_toke_var *s);

// expand_utils.c
char	*sjoin_ext(char *s1, char *s2);
char	*dollar_join(t_main *m_var, char *s1, char *s2);
void	cut_and_paste(t_toke_var *s, t_node **cur_node, int i);
void	found_cash(t_main *m_var, t_node **cur_node, t_toke_var	*s);

// error.c
int	ft_err_handle(char *path, int perm, int type);
int	syntax_error(char *msg);

//parse.c
void	malloc_size(t_total **total);
void    write_to_heredoc(t_total **total);
void	get_total(t_node **lists, t_total **total);
void	get_delim(t_node **lists, t_total **total);
void	get_tol_condition(t_total **total, t_node *cur_node);
// parse_utils.c
void	malloc_pipes(t_total **total);
void	malloc_heredoc(t_total **total);

// here_doc.c
t_node	*here_quote(char *str, char quote, t_node **list);
char	*here_doc(char *delim);

// free.c
void	free_lists(t_node **lists);
void	free_total(t_total **total);
void	free_envp(t_envp **envp);
#endif
