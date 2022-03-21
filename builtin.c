/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:54:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/21 09:56:44 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//strcmp is not in the libft


#include <stdio.h>
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

void	builtin_echo(char **token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strcmp(token[i], "-n") == 0)
	{
		j++; //start the echo at the token after "-n"
		if (token[1] == NULL)
			return ;
	}
	while (token[i + j] != NULL)
	{
		if (i != 0)
			printf(" ");
		printf("%s", token[i + j]);
		i++;
	}
	if (j == 0)
		printf("\n");
}

void	parse_builtin(int argc, char **cmd)
{
	if (argc < 3)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd + 1); //cmd[0] = "echo" is not passed on to the function
	else
		printf("%s: command not found\n", cmd[0]);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	parse_builtin(argc, argv + 1); //argv[0] is not passed to the function
	return (0);
}