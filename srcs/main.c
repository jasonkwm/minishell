/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/08/23 15:35:47 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *a, char *b);

int main(void)
{
    char    *str;

    while (1)
    {
        str = readline("minishell> ");
        if (str && *str)
            add_history(str);
        if (ft_strcmp(str, "exit") == 0)
            return (0);
        else if (ft_strcmp(str, "PATH") == 0)
            printf("%s\n", getenv("PATH"));
        else if (ft_strcmp(str, "HOME") == 0)
            printf("%s\n", getenv("HOME"));
        else if (ft_strcmp(str, "ROOT") == 0)
            printf("%s\n", getenv("ROOT"));
        else if (ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "PWD") == 0)
            printf("%s\n", getenv("PWD"));
        else if (ft_strcmp(str, "env") == 0)
            printf("%s\n", getenv(""));
        else
            printf( "%s\n", str);
    }
    return (0);
}

int ft_strcmp(char *a, char *b)
{
    while (*a || *b)
    {
        if (*a != *b)
            return (1);
        a++;
        b++;
    }
    return (*a - *b);
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