/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:17:56 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/11 18:32:11 by jakoh            ###   ########.fr       */
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

// ****MALLOC WAS USED****
// convert string pass into src 
// to lower character
void	to_lower(char *src, char **dest)
{
	char	*temp;
	int		i;

	i = -1;
	temp = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	while (src[++i])
	{
		if (src[i] >= 'A' && src[i] <= 'Z')
			temp[i] = src[i] + 32;
		else
			temp[i] = src[i];
	}
	*dest = temp;
}

// check wether string is a command or not
int	is_cmd(char *str)
{
	char	*lower;
	int		i;

	i = 0;
	to_lower(str, &lower);
	if (!ft_strcmp(lower, "echo") || !ft_strcmp(lower, "cd")
		|| !ft_strcmp(lower, "pwd") || !ft_strcmp(lower, "export")
		|| !ft_strcmp(lower, "unset") || !ft_strcmp(lower, "env")
		|| !ft_strcmp(lower, "exit") || !ft_strcmp(lower, "cat"))
		i = 1;
	free(lower);
	return (i);
}

// compare character 
// returns a specific int if match character
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
	if (c == ' ' || c == ';' || c == '\0')
		return (9);
	return (0);
}
