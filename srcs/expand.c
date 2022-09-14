/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:03:29 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/14 15:06:23 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expanding arguments
// just like tokenizing
// only this time we free cur_node->val and string join the new part of the string

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
						++(s.left);
						while (is_op(node->val[s.right]) != 9 && is_op(node->val[s.right]) != 1)
							++(s.right);
						temp = ft_substr(node->val, s.left, s.right - s.left);
						str = ft_monies(m_var, str, temp);
						s.left = s.right;
						if (node->val[s.right] == '\"')
							break ;
					}
				}
				if (s.left != s.right)
				{
					temp = ft_substr(node->val, s.left, s.right - s.left);
					str = sjoin_ext(str, temp);
				}
			}
			s.left = ++(s.right);
		}
		else if (node->val[s.right] == '$')
		{
			// if question mark only do nothing
			// get errno number
			if (s.left != s.right)
			{
				temp = ft_substr(node->val, s.left, s.right - s.left);
				str = sjoin_ext(str, temp);
			}
			s.left = s.right;
			s.left++;
			while (is_op(node->val[s.right]) != 9 && is_op(node->val[s.right]) != 1)
				++(s.right);
			temp = ft_substr(node->val, s.left, s.right - s.left);
			str = ft_monies(m_var, str, temp);
			s.left = s.right;
		}
		else
			++(s.right);
	}
	temp = ft_substr(node->val, s.left, s.right - s.left);
	str = sjoin_ext(str, temp);
	free(node->val);
	node->val = str;
	if (is_cmd(node->val) == 1)
		node->type = 1;
}

// if theres nothing to join then just return either s1 or s2
// accepted input for parameter must be a malloc char *
// function will call string join and free both s1 & s2
// and return the joined string.
char	*sjoin_ext(char *s1, char *s2)
{
	char	*temp;
	
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (temp);
}

char	*get_ev(t_main *m_var, char *var);
// parsing dollar sign $ string but without the $
char	*ft_monies(t_main *m_var,char *s1, char *s2)
{
	char	*str;
	char	*temp;

	temp = get_ev(m_var, s2);
	if (temp == NULL)
		str = ft_strdup("");
	else
		str = ft_strdup(temp + ft_strlen(s2) + 1);
	str = sjoin_ext(s1, str);
	free(s2);
	return (str);
}

// get specific enviroment variable
char	*get_ev(t_main *m_var, char *var)
{
	t_envp	*temp;

	temp = m_var->envp;
	while (temp != NULL)
	{
		if (ft_strnstr(temp->val, var, ft_strlen(var)) != 0)
			break;
		temp = temp->next;
	}
	if (temp == NULL)
		return NULL;
	return (temp->val);
}

// add to end envp linked list in m_var
void	add_env(t_main *m_var, char *str)
{
	t_envp	*temp;

	temp = m_var->envp;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = ft_calloc(1, sizeof(t_envp));
	temp->next->val = ft_strdup(str);
	temp->next->next = NULL;
}

/*
char	*ft_monies(t_main *m_var,char *s1, char *s2)
{
	char	*str;
	int		i;
	t_envp	*temp;

	i = -1;
	temp = m_var->envp;
	while (temp != NULL)
	{
		if (ft_strnstr(temp->val, s2, ft_strlen(s2)) != 0)
			break;
		temp = temp->next;
	}
	if (temp == NULL)
		str = ft_strdup("");
	else
		str = ft_strdup(temp->val + ft_strlen(s2) + 1);
	str = sjoin_ext(s1, str);
	free(s2);
	return (str);
}
*/