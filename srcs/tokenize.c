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
		// if its a quote ' or " 
		// loop till end of string or quote found
		if (is_operator(str[right]) == 1)
		{
			prev = right;
			while (str[++right] != str[prev] && str[right] != 0)
				;
			if (str[right] == 0)
			{
				// if closing quote is not found
				temp = ft_here_quotes(ft_substr(str, left, (++right - left)),
					str[prev], &temp);
			}
			else if (str[right] == str[prev])
				right++;
		}
		// sub string remainder or any that encounters space
		// check if its command or not
		else if ((str[right] == ' ' || str[right] == '\0') && left != right)
		{
			temp->val = ft_substr(str, left, (right - left));
			if (is_command(temp->val) == 1)
				temp->type = 1;
			else
				temp->type = 2;
			temp->next = ft_node(temp->id + 1, NULL, 0, &temp);
			temp = temp->next;
			left = ++right;
		}
		// this is for redirection
		else if (is_operator(str[right]) == 2)
		{
			if (left != right)
			{
				temp->val = ft_substr(str, left, (right - left));
				temp->type = 2;
				temp->next = ft_node(temp->id + 1, NULL, 0, &temp);
				temp = temp->next;
				left = right;
			}
			if (left == right)
			{
				if (str[right] == str[right + 1])
				{
					temp->val = ft_substr(str, left, 2);
					++right;
				}
				else
					temp->val = ft_substr(str, left, 1);
				temp->type = 3;
				temp->next = ft_node(temp->id + 1, NULL, 0, &temp);
				temp = temp->next;
				left = ++right;
			}
		}
		else if (is_operator(str[right]) == 3)
		{
			if (left != right)
			{
				temp->val = ft_substr(str, left, (right - left));
				temp->type = 2;
				temp->next = ft_node(temp->id + 1, NULL, 0, &temp);
				temp = temp->next;
				left = right;
			}
			temp->val = ft_substr(str, left, 1);
			temp->type = 4;
			temp->next = ft_node(temp->id + 1, NULL, 0, &temp);
			temp = temp->next;
			left = ++right;
		}
		// need to check for foward slash '\'
		else
			right++;
		// need another else if to check if check for operators, pipes and stuff
	}
	return (0);
}
