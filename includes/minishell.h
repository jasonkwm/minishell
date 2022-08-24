/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:18 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/24 15:13:23 by jakoh            ###   ########.fr       */
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

typedef struct s_node
{
    int             id;
    char            *val;
    char            *type;
    struct s_node   *left;
    struct s_node   *right;
    struct s_node   *prev;
}   t_node;

// temp.c
int ft_strcmp(char *a, char *b);
int	get_env_var(char *str);
int tokenize(char *str);

#endif
