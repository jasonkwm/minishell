/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student->42->fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:43:34 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/25 14:51:51 by jakoh            ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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

// ****MALLOC WAS USED HERE****
// create new sub string and store in struct
void	ft_splice(char *str, int start, int end, t_node *list)
{
	char	*temp;
	int		i;
	temp = ft_calloc(end - start + 1, sizeof(char));
	i = -1;
	while (start <= end)
	{
		temp[++i] = str[start++];
	}
	list->val = temp;
}

// need to accpt struct in parameters
int tokenize(char *str, t_node	**list)
{
	int	left;
	int	right;
	int	len;
	t_node *temp;

	temp = *list;
	left = 0;
	right = 0;
	len = ft_strlen(str);
	
	while (right < len && left < len)
	{
		printf("beginning str[right]: %c\n", str[right]);
		// Check if its one of the operator character
		// and nothing before it
		if (is_operator(str[right]) && left == right)
		{
			// if its either single '' or double "" quotes
			if (is_operator(str[right]) == 1)
			{
				// tc is temporary character
				// to compare if its single or double quotes
				char tc;
				left = right;
				if (str[right] == '\'')
					tc = '\'';
				else
					tc = '\"';
				while (str[++right] != tc && str[right] != 0)
					;
				if (str[right] == 0)
				{
					// if closing quote is not found
					// create something like here_doc that waits for tc;
				}
				else
				{
					// ft_substring that shit with closing quote
					temp->val = ft_substr(str, left, (++right - left) + 1);
				}
			}
			// check for < > | & this 4 symbol
			// and check if preceding character is similar
			else if (is_operator(str[right + 1]) == 2)
				temp->val = ft_substr(str, left, (++right - left) + 1);
			else
				temp->val = ft_substr(str, left, (right - left) + 1);
			temp->left = ft_node(temp->id + 1, NULL, NULL, &temp);
			temp = temp->left;
			left = ++right;
		}
		else if (str[right++] == ' ')
			left = right;
	}
	return (0);
}
