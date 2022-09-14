/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:18 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/14 14:43:26 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "libft.h"

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_tree
{
	int				id;
	char			*val;
	int				type;;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*prev;
}   t_tree;

// type 0 = no type, 1 = command, 2 = arguments, 3 = redirections,
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
	int	left;
	int	right;
	int	len;
}	t_toke_var;

// checker.c
int		ft_strcmp(char *a, char *b);
int		is_cmd(char *str);
int		is_op(char c);

// tokenize.c
void	tokenize(t_main *m_var, char *str, t_node	**tree);
void	to_lower(char *src, char **dest);

// node_utils.c
t_tree	*ft_treenode(int  id, char *val, int type, t_tree **prev);
t_node	*ft_node(int  id, char *val, int type,  t_node **prev);
t_node	*assign_node(t_node **cur_node, char *val, int type);

// here_doc.c
t_node	*here_quote(char *str, char quote, t_node **list);

//expand.c
void	exspender(t_main *m_var, t_node **cur_node);
// void	spender(t_main *m_var, t_node **lists);
// int	convert_dollar(t_main *m_var, t_node **lists);
#endif
