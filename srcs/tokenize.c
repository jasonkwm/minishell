/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:42:02 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/11 17:37:09 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_quote(char *str, t_token_stuff *s, t_node **cur_node);
void	parse_arg(char *str, t_token_stuff *s, t_node **cur_node);
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

// need to accpt struct in parameters
int tokenize(char *str, t_node	**list)
{
	int	left;
	int	right;
	int	len;
	// char *temp;
	t_token_stuff s;
	t_node *cur_node;

	cur_node = *list;
	s.left = 0;
	s.right = 0;
	s.len = ft_strlen(str) + 1;
	left = 0;
	right = 0;
	len = ft_strlen(str) + 1;
	
	while (right < len && left < len)
	{
		s.left = left;
		s.right = right;
		// if its a quote ' or " 
		// loop till end of string or quote found
		if (right != 0 && str[right - 1] == '\\' && is_op(str[right]) == 1)
				++right;
		else if (is_op(str[right]) == 1)
		{
			parse_quote(str, &s, &cur_node);
			left = s.left;
			right = s.right;
		}
		// sub string remainder or any that encounters space
		// check if its command or not
		else if ((str[right] == ' ' || str[right] == '\0' || str[right] == ';')
				&& left != right)
		{
			parse_arg(str, &s, &cur_node);
			left = s.left;
			right = s.right;
		}
		// this is for redirection < or >
		else if (is_op(str[right]) == 2)
		{
			if (left != right)
				cur_node = assign_node(&cur_node, ft_substr(str, left, (right - left)), 2);
			left = right;
			if (str[right] == str[right + 1])
			{
				cur_node = assign_node(&cur_node, ft_substr(str, left, 2), 3);
				++right;
			}
			else
				cur_node = assign_node(&cur_node, ft_substr(str, left, 1), 3);
			left = ++right;
		}
		// for pipe |
		else if (is_op(str[right]) == 3)
		{
			if (left != right)
			{
				cur_node = assign_node(&cur_node, ft_substr(str, left, (right - left)), 2);
				left = right;
			}
			cur_node = assign_node(&cur_node, ft_substr(str, left, 1), 4);
			left = ++right;
		}
		else
			right++;
		// need another else if to check if check for operators, pipes and stuff
	}
	return (0);
}

void	parse_quote(char *str, t_token_stuff *s, t_node **cur_node)
{
	if (is_op(str[s->right]) == 1)
	{
		s->prev = s->right;
		while (str[++(s->right)] != str[s->prev] && str[s->right] != 0)
			;
		// if closing quote is not found
		if (str[s->right] == 0)
			*cur_node = ft_here_quotes(ft_substr(str, s->left, (s->right - s->left + 1)),
				str[s->prev], cur_node);
		++(s->right);
	}
}

void	parse_arg(char *str, t_token_stuff *s, t_node **cur_node)
{
	char	*temp;
	temp = ft_substr(str, s->left, (s->right - s->left));
	if (is_cmd(temp) == 1)
		*cur_node = assign_node(cur_node, temp, 1);
	else
		*cur_node = assign_node(cur_node, temp, 2);
	s->left = ++(s->right);
}

// void	parse_redirect(char *str, t_token_stuff *s, t_node **cur_node)
// {
	
// }