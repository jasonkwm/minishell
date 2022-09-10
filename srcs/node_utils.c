/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:04:33 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/10 17:51:43 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// not sure if need to store previous notes or not but yeah.
// id is position. 
// type 0 = no type, 1 = command, 2 = arguments,
// 3 = redirections, 4 = pipe 5 = here_doc file
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

// tot of using binary tree but life happens.
t_tree	*ft_treenode(int  id, char *val, int type, t_tree **prev)
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
