/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:15:16 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/18 16:46:39 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	token_length(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] == ' ')
		len++;
	if (str[len] == '|' || (str[len] == '<' && str[len + 1] != '<') || \
	(str[len] == '>' && str[len + 1] != '>'))
		return (len + 1);
	if ((str[len] == '<' && str[len + 1] == '<') || \
	(str[len] == '>' && str[len + 1] == '>'))
		return (len + 2);
	while (str[len] != 0 && str[len] != ' ' && \
	str[len] != '|' && str[len] != '<' && str[len] != '>')
	{
		if (str[len] == 39 || str[len] == '"')
			len += ft_strlen_c((str + len + 1), str[len]) + 1;
		len++;
	}
	return (len);
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

static void	expand_envvar(char *string, char *buf, size_t *i, size_t *j)
{
	size_t	end;
	char	*envvar;

	end = 0;
	while (string[++end] != 0)
	{
		if (string[1] == '?')
			break ;
		if (string[end] == 39 || string[end] == '"')
		{
			end--;
			break ;
		}
	}
	(*i) += end;
	if (string[1] != '?')
		envvar = getenv(ft_substr(string, 1, end));
	//else
	//	envvar = last exit status
	if (!envvar)
		return ;
	ft_strlcat(buf, envvar, MAX_TOKEN_LEN);
	*j += ft_strlen(envvar);
}

static void	quotes_and_envvars(char *string, size_t len)
{
	size_t	i;
	size_t	j;
	char	buf[MAX_TOKEN_LEN];
	bool	quote[2];

	i = -1;
	j = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (++i <= len)
	{
		if (handle_quote(string[i], quote))
			continue ;
		if (!quote[1] && string[i] == '$' && \
		string[i + 1] != ' ' && string[i + 1] != 0)
			expand_envvar((string + i), buf, &i, &j);
		else
		{
			buf[j] = string[i];
			j++;
		}
	}
	free(string);
	string = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(string, buf, j);
}

t_list	*lexer(char *line)
{
	t_list			*lexer_start;
	const size_t	len = ft_strlen(line);
	t_tok			token;

	token.start = 0;
	lexer_start = ft_lstnew("START");
	while (token.start < len)
	{
		token.len = token_length((line + token.start));
		token.string = ft_substr_strip_space(line, token.start, token.len);
		quotes_and_envvars(token.string, token.len);
		token.start = token.start + token.len;
		ft_lstadd_back(&lexer_start, ft_lstnew(token.string));
	}
	return (lexer_start);
}
/*
int	main(void)
{
	char	line[100] = "1$'HOME' 2'$HOME' 3$HOME''a 4$!bla 5$?bla";
	t_list	*start;

	start = lexer(line);
	printf("%s\n", line);
	while (start->next)
	{
		start = start->next;
		printf("%s\n", (char *)start->content);
	}
	return (1);
}
*/
