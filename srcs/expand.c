/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:03:29 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/12 17:29:57 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expanding arguments
// just like tokenizing
// only this time we free cur_node->val and string join the new part of the string

void	exspender(t_main *m_var, t_node **cur_node);
void	spender(t_main *m_var, t_node **lists)
{
	t_node	*cur_node;

	cur_node = *lists;
	while (cur_node->val != NULL)
	{
		exspender(m_var, &cur_node);
		cur_node = cur_node->next;
	}
}

char	*sjoin_ext(char *s1, char *s2);
void	exspender(t_main *m_var, t_node **cur_node)
{
	t_node		*node;
	t_toke_var	s;
	char		*str;
	char		*temp;
	char		*temp2;

	node = *cur_node;
	if (node->type != 2 || node->val == NULL)
		return ;
	s.left = 0;
	s.right = 0;
	s.len = ft_strlen(node->val);
	while (s.right < s.len && s.left < s.len)
	{
		if (is_op(node->val[s.right]) == 1)
		{
			if (s.left != s.right)
			{
				temp = ft_substr(node->val, s.left, s.right - s.left);
				str = sjoin_ext(str, temp);
			}
			s.left = s.right;
			++(s.left);
			if (node->val[s.left] == '\'')
			{
				while (node->val[++(s.right)] != '\'')
					;
				temp = ft_substr(node->val, s.left, s.right - s.left);
				str = sjoin_ext(str, temp);
			}
			else if (node->val[s.left] == '\"')
			{
				while (node->val[++(s.right)] != '\"')
				{
					if (node->val[s.right] == '$')
					{
						if (s.left != s.right)
						{
							temp = ft_substr(node->val, s.left, s.right - s.left);
							str = sjoin_ext(str, temp);
						}
						s.left = s.right;
						s.left++;
						while (is_op(node->val[++s.right]) != 9 && node->val[s.right] != '\"')
							;
						temp = ft_substr(node->val, s.left, s.right - s.left);
						// str = 
					}
				}
				
				temp = ft_substr(node->val, s.left, s.right - s.left);
				str = sjoin_ext(str, temp);
			}
			s.left = ++s.right;
		}
		else
			++(s.right);
	}
}

char	*sjoin_ext(char *s1, char *s2)
{
	char	*temp;
	
	if (s1 == NULL)
		return (s2);
	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (temp);
}

// char	*ft_monies(t_main *m_var,char *s1, char *s2);
// {
// 	char	*temp;
// }