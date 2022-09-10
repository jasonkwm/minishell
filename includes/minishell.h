/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:18 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/10 18:59:03 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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

// type 0 = no type, 1 = command, 2 = arguments, 3 = redirections, 4 = pipe 5 = here_doc file
typedef struct s_node
{
	int				id;
	char			*val;
	int				type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_main
{
	int		ac;
	char	**av;
	char	**envp;
}	t_main;

// checker.c
int	ft_strcmp(char *a, char *b);
int	is_command(char *str);
int	is_operator(char c);

// tokenize.c
int	tokenize(char *str, t_node	**tree);
void	to_lower(char *src, char **dest);

// node_utils.c
t_tree	*ft_treenode(int  id, char *val, int type, t_tree **prev);
t_node	*ft_node(int  id, char *val, int type,  t_node **prev);

// here_doc.c
t_node	*ft_here_quotes(char *str, char quote, t_node **list);

//expand.c
int	convert_dollar(t_main *m_var, t_node **lists);
#endif
