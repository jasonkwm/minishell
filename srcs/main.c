/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/09/10 16:23:08 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int main(void)
{
    char    *str;
    t_node  *lists;
    t_node  *temp;
    
	lists = ft_node(0, NULL, 0, NULL);
    while (1)
    {
        str = readline("minishell> ");
        // printf("str: %s\n", str);
        if (str && *str)
            add_history(str);
        if (ft_strcmp(str, "exit") == 0)
            return (0) | printf( "%s\n", str);
        // typing 'show' in minishell will show you whats in the link list
        else if (ft_strcmp(str, "show") == 0)
        {
            temp = lists;
            while (temp != NULL)
            {
                printf("content: %s, type: %i\n", temp->val, temp->type);
                temp = temp->next;
            }
        }
        else
            tokenize(str, &lists);
    }
    
    return (0);
}

/*
Operator -
Single Quotes   : ' (print string as string)
Double Quotes   : " (print string as string but expand $PATH)
Redirect Input  : <
Redirect Output : >
here_doc        : <<
Append Output   : >>
Pipe Operator   : |
Enviroment Var	: $PATH
Exit Status		: $?
Dollar Symbol	: $ (Only need to expland for enviroment variable)
*/

/*
Interactive -
ctrl + C	: New prompt on a newline
ctrl + D	: Exit Shell
ctrl + \	: Do Nothing
*/

/*
Commands -
echo	: with option '-n'
cd		: with only relative or absolute path
pwd		: no options
export	: no options
unset	: no options
env		: no options or args
exit	: no options
*/

// echo if echo met < or > do as the operator expects. 
// if echo met quotes ' or " then continue finding that quote until the end of time
// if cant find quote then read line again and again until quote is found. 