/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:43:34 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/24 17:24:51 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_var(char *str)
{
	if (ft_strcmp(str, "PATH") == 0)
		return (1) && printf("%s\n", getenv("PATH"));
	else if (ft_strcmp(str, "HOME") == 0)
        return (1) && printf("%s\n", getenv("HOME"));
	else if (ft_strcmp(str, "ROOT") == 0)
		return (1) && printf("%s\n", getenv("ROOT"));
	else if (ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "PWD") == 0)
		return (1) && printf("%s\n", getenv("PWD"));
	return (0);
}

// check if both string is similar
int ft_strcmp(char *a, char *b)
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

int	is_command(char *str)
{
	char *lower;
	int	i;

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

int	is_operator(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (2);
	if ( c == '/' || c == '.')
		return (3);
	if (c == '(' || c == '[' || c == '{')
		return (4);
	if ( c == ')' || c == ']' || c == '}')
		return (5);
	if (c == '\\')
		return (6);
	if (c == '$')
		return (7);
	return (0);
}

// need to accpt struct in parameters
int tokenize(char *str)
{
	int	left;
	int	right;
	int	len;
	
	left = 0;
	right = 0;
	len = ft_strlen(str);
	while (right < len && left < len)
	{
		if (is_operator(str[right]) && left == right)
		{
			if (is_operator(str[right + 1]) == 2)
			{
				right++;
			}
			right++;
			left = right;
		}
	}
	return (0);
}

// create new sub string and store in struct