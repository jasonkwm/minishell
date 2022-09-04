/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:18 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/04 16:19:17 by jakoh            ###   ########.fr       */
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
	char			*type;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*prev;
}   t_tree;

typedef struct s_node
{
	int				id;
	char			*val;
	int				type;
	struct s_node	*next;
}	t_node;

// checker.c
int	ft_strcmp(char *a, char *b);
int	is_command(char *str);
int	is_operator(char c);

// temp.c
int	tokenize(char *str, t_tree	**tree);

// node_utils.c
t_tree	*ft_treenode(int  id, char *val, char *type, t_tree **prev);
t_node	*ft_node(int  id, char *val, int type, t_node **prev);

#endif
