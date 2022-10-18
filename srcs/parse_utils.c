/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:13:13 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/18 19:07:20 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check permission and open fd if able
 * 
 * @param path file path
 * @param type 
 * 0 = READ <
 * 1 = WRITE >
 * 2 = APPEND >>
 * @param cur current command group
 * @return int 
 * -1 if fail
 * 0 if success
 */
int check_access(char *path, int type, t_cmds **cur)
{
	if (type == 0)
	{
		if (access(path, R_OK) == -1)
		{
			printf("%s: %d, str: %s\n", path, errno, strerror(errno));
			return (-1);
		}
		(*cur)->input =open(path, O_RDONLY);
	}
	else if (type == 1 || type == 2)
	{
		if (type == 1)
			(*cur)->output = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			(*cur)->output = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*cur)->output == -1 && access(path, W_OK) == -1)
		{
			printf("%s: %d, str: %s\n", path, errno, strerror(errno));
			return (-1);
		}
	}
	return (2);
}

// need a extension function for grouping
int function(t_node *list, t_cmds **cur_group, int *i, int *hd)
{
	int	check;

	check = 0;
	if (list->type == PIPE)
	{
		*i = -1;
		(*cur_group)->next = init_cur_group(list->next, hd);
		(*cur_group) = (*cur_group)->next;
		check = 1;
	}
	else if (list->type == REDIRECT)
	{
		if (ft_strcmp(list->val, "<") == 0)
			check = check_access(list->next->val, 0, cur_group);
		else if (ft_strcmp(list->val, "<<") == 0)
				(*cur_group)->input = -2;
		else if (ft_strcmp(list->val, ">") == 0)
			check = check_access(list->next->val, 1, cur_group);
		else if (ft_strcmp(list->val, ">>") == 0)
			check = check_access(list->next->val, 1, cur_group);
	}
	return (check);
}