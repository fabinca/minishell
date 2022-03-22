/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:54:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/22 17:01:41 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//strcmp is not in the libft


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


char	**ft_split(char const *s, char c);


int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	if (*s1 && !*s2)
		return (*(unsigned char *)s1);
	if (*s2 && !*s1)
		return (*(unsigned char *)s2 * -1);
	return (0);
}


char	*builtin_pwd(void)
{
	char s[100];
	
	return (getcwd(s, 100));
}

char	*ft_strcpy_path_up()
{
	int		len;
	char	*new_path;
	int		i;

	i = 0;
	if (ft_strcmp(ft_strrchr(builtin_pwd(), '/'), ft_strchr(builtin_pwd(), '/')) == 0)
		len = 1;
	else
		len = ft_strlen(builtin_pwd()) - ft_strlen(ft_strrchr(builtin_pwd(), '/'));
	new_path = malloc(sizeof(char) * (len + 1));
	if (!new_path)
	return (0);
	while (i < len)
	{
		new_path[i] = builtin_pwd()[i];
		i++;
	}
	new_path[i] = '\0';
	return (new_path);
}


void	builtin_env(char **cmd, char **envp)
{
	int	i;

	if (cmd[1])
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return ;
	}
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}


void	builtin_echo(char **token)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (token[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(token[i], "-n") == 0)
	{
		j++; //start the echo at the token after "-n"
		if (token[i + 1] == NULL)
			return ;
	}
	while (token[i + j] != NULL)
	{
		if (i != 1)
			printf(" ");
		printf("%s", token[i + j]);
		i++;
	}
	if (j == 0)
		printf("\n");
}

void	builtin_exit(char **cmd, int *exit_status)
{
	if (cmd[1])
		printf("exit: '%s': No such file or directory\n", cmd[1]); //!!!couldn't read so fast to get the actual error msg!!!
	//how can I clear the screen or close the terminal screen?
	(*exit_status)++;
}

char	*build_path(char *cmd)
{
	char	*old_path;
	char	*temp;
	char	*new_path;

	old_path = builtin_pwd();
	printf("old path = %s, length %ld\n", old_path, ft_strlen(old_path));
	if (ft_strlen(old_path) != 1)
		temp = ft_strjoin(old_path, "/");
	else
	{
		temp = malloc(sizeof(char) * 2);
		temp = "/";
	}
	printf("temp = %s\n", temp);
	new_path = ft_strjoin(temp, cmd);
	free (temp);
	return (new_path);
}

void	builtin_cd(char **cmd)
{
	char	*path;
	int		len;
	int		i;

	if (!cmd[1])
		return ;
	if (cmd[2])
	{
		printf("bash: cd: too many arguments\n");
		return ;
	}
	if (ft_strcmp(cmd[1], "..") == 0)
	{
		path = ft_strcpy_path_up();
		if (chdir(path))
		{
			printf("error cd path up\n");
			free(path);
			return ;
		}
		free(path);
		return ;
	}
	if (cmd[1][0] != '/')
	{
		path = build_path(cmd[1]);
		printf("path = %s\n", path);
		if (chdir(path))
		{
			printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
			free (path);
			return ;
		}
		free (path);
		return ;
	}

	
	
}

void	parse_builtin(char *line, char **envp, int *exit_status)
{
	char **cmd;

	cmd = ft_split(line, ' ');
	if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		printf("%s\n", builtin_pwd());
	else if (ft_strcmp(cmd[0], "env") == 0)
		builtin_env(cmd, envp);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		builtin_exit(cmd, exit_status);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		builtin_cd(cmd);
	else
		printf("%s: command not found\n", cmd[0]);
}

/* int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	parse_builtin(line);
	return (0);
} */