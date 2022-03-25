/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:15:16 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/25 14:06:06 by cfabian          ###   ########.fr       */
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

void	update(char *string, char *buf)
{
	free(string);
	string = ft_calloc(ft_strlen(buf) + 2, sizeof(char));
	ft_strlcpy(string, buf, ft_strlen(buf) + 1);
	free(buf);
}

static char	*quotes_and_envvars(char *string, size_t len)
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
	while (++i <= len)
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
	update(string, buf);
	return (string);
}

t_list	*lexer(char *line)
{
	t_list			*lexer_start;
	const size_t	len = ft_strlen(line);
	t_tok			token;
	t_list			*new;

	token.start = 0;
	lexer_start = NULL;
	while (token.start < len)
	{
		token.len = token_length((line + token.start));
		token.string = ft_substr_strip_space(line, token.start, token.len);
		token.string = quotes_and_envvars(token.string, token.len);
		token.start = token.start + token.len;
		new = ft_lstnew(token.string);
		if (!lexer_start)
			lexer_start = new;
		else
			ft_lstadd_back(&lexer_start, new);
	}
	return (lexer_start);
}

/* int	main(void)
{
	char	line[100] = "$HOME | '$HOME' | $bla >out";
	t_list	*start;
	t_list	*buf;

	start = lexer(line);
	buf = start;
	printf("%s\n", line);
	while (start)
	{
		printf("%s\n", (char *)start->content);
		start = start->next;
	}
	ft_lstclear(&buf);
	return (1);
} */

