/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:06:08 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/25 14:39:04 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_envvar(char *string, char *buf, size_t *i, size_t *j)
{
	size_t	end;
	char	*envvar;
	char	*str;

	end = 0;
	while (string[++end] != 0)
	{
		if (string[end] != 39 && string[end] == '"')
			continue ;
		if (string[1] == '?')
			end = 2;
		end--;
		break ;
	}
	str = ft_substr(string, 1, end);
	envvar = getenv(str);
	if (str[1] == '?')
		envvar = ft_itoa(g_last_exit);
	free(str);
	if (!envvar)
		return ;
	ft_strlcat(buf, envvar, MAX_TOKEN_LEN);
	(*i) += end;
	*j += ft_strlen(envvar);
}
