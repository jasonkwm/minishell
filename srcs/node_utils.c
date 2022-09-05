/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:04:33 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/05 16:14:54 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_node(int  id, char *val, int type, t_node **prev)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->id = id;
	node->val = val;
	node->type = type;
	node->prev = NULL;
	if (prev != NULL)
		node->prev = *prev;
	node->next = NULL;
	return (node);
}

t_tree	*ft_treenode(int  id, char *val, char *type, t_tree **prev)
{
	t_tree	*node;

	node = ft_calloc(1, sizeof(t_tree));
	node->id = id;
	node->val = val;
	node->type = type;
	if (prev == NULL)
		node->prev = NULL;
	else
		node->prev = *prev;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
