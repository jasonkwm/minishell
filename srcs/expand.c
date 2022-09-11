/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:03:29 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/11 18:53:58 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// just testing unusable kinda
char	*convert_dollar(t_main *m_var, t_node **lists)
{
	t_node	*temp;
	char	*chr;
	int		i;

	(void)m_var;
	chr = 0;
	temp = *lists;
	while (temp->val != NULL)
	{
		chr = ft_strchr(temp->val, '$');
		if (chr != 0)
		{
			++chr;
			i = -1;
			while (chr[++i] != 0 && ft_strchr(" \"", chr[i]) == 0)
				;
			chr[i] = 0;
			i = -1;
			while (m_var->envp[++i] != NULL)
			{
				if (ft_strnstr(m_var->envp[i], chr, ft_strlen(chr)) != 0)
				{
					chr = ft_strchr(m_var->envp[i], '=');
					chr++;
					// chr now has the value of env;
					printf("env value: %s\n", chr);
				}
			}
		}
		temp = temp->next;
	}
	return chr;
}