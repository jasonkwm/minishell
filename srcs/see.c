/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:21:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/10 17:21:54 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_see_group(t_cmds **groups)
{
	t_cmds *temp;
	
	temp = *groups;
	int i = -1;
	int	j = -1;
	while (temp != NULL)
	{
		printf("\n====GROUP %d===\n\n", ++j);
		printf("input <: %d, output >: %d, hd: %d\n", temp->input, temp->output, temp->heredoc_no);
		i = -1;
		printf("args : [ ");
		while (temp->args[++i] != NULL)
			printf("%s ", temp->args[i]);
		printf(" ]\n");
		printf("\n====END %d===\n\n", j);
		temp = temp->next;
	}
}


void	ft_see(t_node **lists)
{
	t_node	*temp;

	temp = *lists;
	while (temp != NULL)
	{
		printf("cur[%i]: %s, type: %i\n", temp->id, temp->val, temp->type);
		temp = temp->next;
	}
}