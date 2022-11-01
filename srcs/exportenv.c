#include "minishell.h"

void    export(t_main *m_var, t_cmds **cmd_groups)
{
	t_envp	*temp;
	int		i;

	temp = m_var->envp;
	if ((*cmd_groups)->args[1] == NULL)
	{
		while (temp != NULL)
		{
			if (temp->val != NULL)
			{
				printf("delcare -x ");
				printf("%s\n", temp->val);
			}
			temp = temp->next;
		}
		return ;
	}
	//Still need to export with argument, jason said just push into envp and check if string don't show in env
	while (temp->next != NULL)
	{
		i = 0;
		if (temp->val == (*cmd_groups)->args[1])
			return ;
		temp = temp->next;
	}
	temp->next = malloc(sizeof(t_envp));
	// while((*cmd_groups)->args[1][i] != '=' && (*cmd_groups)->args[1][i] != '\0')
	// 	++i;
	// if ((*cmd_groups)->args[1][i] == '=')
	// {
	// 	if (*cmd_groups)->args[1][i + 1] == '\0')
	// }	
	temp->next->val = ft_strdup((*cmd_groups)->args[1]);
	char *val = ft_strchr((*cmd_groups)->args[1], '=');
	val++;
	printf("%s\n", val);
	temp->next->next = NULL;
}

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

void    env(t_main *m_var)
{
	t_envp *temp;

	temp = m_var->envp;
	while (temp != NULL)
	{
		if (temp->val != NULL)
		{
			if (gotequal(temp->val) == 1)
				printf("%s\n", temp->val);
		}
		temp = temp->next;
	}
}