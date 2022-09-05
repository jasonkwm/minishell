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
	int	prev;
	t_node *temp;

	temp = *list;
	left = 0;
	right = 0;
	len = ft_strlen(str) + 1;
	
	while (right < len && left < len)
	{
		// if its either single '' or double "" quotes
		// and nothing before it
		if (is_operator(str[right]) == 1 && left == right)
		{
			left = right;
			while (str[++right] != str[left] && str[right] != 0)
				;
			if (str[right] == 0)
			{
				// if closing quote is not found
				// call readline();
			}
			else
			{
				// ft_substring that shit with closing quote
				temp->val = ft_substr(str, left, (++right - left) + 1);
				temp->type = 2;
			}
			temp->next = ft_node(temp->id + 1, NULL, 0, &temp);
			temp = temp->next;
			left = right;
		}
		else if (is_operator(str[right]) == 1 && left != right)
		{
			prev = right;
			while (str[++right] != str[prev] && str[right] != 0)
				;
			if (str[right] == 0)
			{
				// if closing quote is not found
				// call readline();
			}
			else if (str[right] == str[prev])
				right++;
		}
		else if ((str[right] == ' ' || str[right] == '\0') && left != right)
		{
			temp->val = ft_substr(str, left, (right - left));
			// int	is_command(char *str) check if temp->val 
			// is a command if its a command then set temp->type
			if (is_command(temp->val) == 1)
				temp->type = 1;
			else
				temp->type = 2;
			temp->next = ft_node(temp->id + 1, NULL, 0, &temp);
			temp = temp->next;
			left = ++right;
		}
		else
			right++;
	}
	return (0);
}
