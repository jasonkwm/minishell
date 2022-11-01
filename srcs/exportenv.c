#include "minishell.h"

int gotequal(char *val)
{
	int	i;

	i = 0;
	while (val[i] != '\0')
	{
		if (val[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void    export(t_main *m_var, t_cmds **cmd_groups)
{
	char	**split;
	char	*val;
	t_envp	*temp;
	int		i;

	if ((*cmd_groups)->args[1] == NULL)
	{
		while (temp != NULL)
		{
			printf("delcare -x ");
			if (temp->val == NULL)
				printf("%s", temp->key);
			else
				printf("%s=", temp->key);
			if (temp->val != NULL)
				printf("\"%s\"", temp->val);
			printf("\n");
			temp = temp->next;
		}
		return ;
	}
	temp = m_var->envp;
	if (gotequal((*cmd_groups)->args[1]) == 0)
	{
		while (temp != NULL)
		{
			if (strcmp(temp->key, (*cmd_groups)->args[1]) == 0)
				return ;
			if (temp->next == NULL)
				break ;
			temp = temp->next;
		}
		temp->next = malloc(sizeof(t_envp));
		temp->next->key = ft_strdup((*cmd_groups)->args[1]);
		temp->next->val = NULL;
		temp->next->next = NULL;
		return ;
	}
	split = ft_split((*cmd_groups)->args[1],'=');
	while (temp != NULL)
	{
		if (strcmp(temp->key, split[0]) == 0)
		{
			i = -1;
			while (split[++i] != NULL)
				free(split[i]);
			free(split);
			val = ft_strchr((*cmd_groups)->args[1], '=');
			val++;
			if (temp->val != NULL)
				free(temp->val);
			temp->val = ft_strdup(val);
			return ;
		}
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	val = ft_strchr((*cmd_groups)->args[1], '=');
	val++;
	temp->next = malloc(sizeof(t_envp));
	temp->next->key = ft_strdup(split[0]);
	temp->next->val = ft_strdup(val);
	temp->next->next = NULL;
	
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

void    env(t_main *m_var)
{
	t_envp *temp;

	temp = m_var->envp;
	while (temp != NULL)
	{
		if (temp->val != NULL)
		{
			printf("%s=", temp->key);
			printf("%s\n", temp->val);
		}
		temp = temp->next;
	}
}

// Test cases
// export e
// export c=d
// any other command
// Will leak

// Test cases
// export e
// export c=d
// Won't leak