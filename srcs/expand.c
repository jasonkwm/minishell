/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:03:29 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/12 18:31:31 by jakoh            ###   ########.fr       */
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

char	*ft_monies(t_main *m_var,char *s1, char *s2);
char	*sjoin_ext(char *s1, char *s2);
void	exspender(t_main *m_var, t_node **cur_node)
{
	t_node		*node;
	t_toke_var	s;
	char		*str;
	char		*temp;

	(void)m_var;
	str = NULL;
	temp = NULL;
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
			if (node->val[(s.left)] == '\'')
			{
				++(s.left);
				while (node->val[++(s.right)] != '\'')
					;
				temp = ft_substr(node->val, s.left, s.right - s.left);
				str = sjoin_ext(str, temp);
			}
			else if (node->val[(s.left)] == '\"')
			{
				++(s.left);
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
						str = ft_monies(m_var, str, temp);
						s.left = s.right;
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
	temp = ft_substr(node->val, s.left, s.right - s.left);
	str = sjoin_ext(str, temp);
	free(node->val);
	node->val = str;
}

char	*sjoin_ext(char *s1, char *s2)
{
	char	*temp;
	
	if (s1 == NULL)
		return (s2);
	else if (s2 == NULL)
		return (s1);
	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (temp);
}

char	*ft_monies(t_main *m_var,char *s1, char *s2)
{
	char	*temp;
	int		i;

	i = -1;
	while (m_var->envp[++i] != NULL)
		if (ft_strnstr(m_var->envp[i], s2, ft_strlen(s2)) != 0)
			break;
	if (m_var->envp[i] == NULL)
		temp = ft_strdup("");
	else
		temp = ft_strdup(m_var->envp[i] + ft_strlen(s2) + 1);
	temp = sjoin_ext(s1, temp);
	free(s2);
	return (temp);
}