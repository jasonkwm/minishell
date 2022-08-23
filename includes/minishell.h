/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:18 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/23 15:06:33 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node
{
    char            *val;
    char            *type;
    struct s_node   *left;
    struct s_node   *right;
}   t_node;

#endif
