/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_envvars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:06:08 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/04 19:09:21 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_exit_status(char *buf, size_t *i, size_t *j)
{
	char	*exit_status;

	*i += 1;
	exit_status = ft_itoa(g_last_exit);
	ft_strlcat(buf, exit_status, MAX_TOKEN_LEN);
	*j += ft_strlen(exit_status);
	free(exit_status);
}

static void	expand_envvar(char *string, char *buf, size_t *i, size_t *j)
{
	size_t	end;
	char	*envvar;
	char	*str;

	end = 0;
	if (string[1] == '?')
	{
		expand_exit_status(buf, i, j);
		return ;
	}
	while (string[++end] != 0)
	{
		if (string[end] != 39 && string[end] == '"')
			continue ;
		end--;
		break ;
	}
	*i += end;
	str = ft_substr(string, 1, end);
	envvar = getenv(str);
	free(str);
	if (!envvar)
		return ;
	ft_strlcat(buf, envvar, MAX_TOKEN_LEN);
	*j += ft_strlen(envvar);
}

static int	handle_quote(char c, bool quote[2])
{
	if (c == '"' && !quote[1])
	{
		quote[0] = !quote[0];
		return (1);
	}
	if (c == 39 && !quote[0])
	{
		quote[1] = !quote[1];
		return (1);
	}
	return (0);
}

static char	*update(char *string, char *buf)
{
	free(string);
	string = ft_calloc(ft_strlen(buf) + 1, sizeof(char));
	ft_strlcpy(string, buf, ft_strlen(buf) + 1);
	free(buf);
	return (string);
}

char	*quotes_and_envvars(char *string, size_t len)
{
	size_t	i;
	size_t	j;
	char	*buf;
	bool	quote[2];

	i = -1;
	j = 0;
	quote[0] = 0;
	quote[1] = 0;
	buf = (char *)ft_calloc(MAX_TOKEN_LEN, sizeof(char));
	while (++i < len)
	{
		if (handle_quote(string[i], quote))
			continue ;
		if (!quote[1] && string[i] == '$' && \
		string[i + 1] != ' ' && string[i + 1] != 0)
			expand_envvar((string + i), buf, &i, &j);
		else
			buf[j++] = string[i];
	}
	buf[j] = 0;
	string = update(string, buf);
	return (string);
}
