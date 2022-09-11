/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:17:56 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/11 16:44:08 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if both string is similar
int	ft_strcmp(char *a, char *b)
{
	while (*a || *b)
		if (*(a++) != *(b++))
			return (1);
	return (*a - *b);
}

int	is_cmd(char *str)
{
	char	*lower;
	int		i;

	i = 0;
	to_lower(str, &lower);
	if (!ft_strcmp(lower, "echo") || !ft_strcmp(lower, "cd")
		|| !ft_strcmp(lower, "pwd") || !ft_strcmp(lower, "export")
		|| !ft_strcmp(lower, "unset") || !ft_strcmp(lower, "env")
		|| !ft_strcmp(lower, "exit"))
		i = 1;
	free(lower);
	return (i);
}

int	is_op(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	if (c == '<' || c == '>')
		return (2);
	if (c == '|')
		return (3);
	if (c == '/' || c == '.')
		return (4);
	if (c == '(' || c == '[' || c == '{')
		return (5);
	if (c == ')' || c == ']' || c == '}')
		return (6);
	if (c == '\\')
		return (7);
	if (c == '$')
		return (8);
	return (0);
}
