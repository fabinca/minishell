/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:15:16 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/18 13:36:24 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_strlen_c(char *str, char end)
{
	size_t	len;

	len = 0;
	while (str[len] != 0 && str[len] != end)
		len++;
	return (len);
}

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
		//printf("%ld\n", token.len);
		token.string = ft_substr_strip_space(line, token.start, token.len);
		// -> replace $[...] if not ' '
		token.start = token.start + token.len;
		printf("%s\n", token.string);
		ft_lstadd_back(&lexer_start, ft_lstnew(token.string));
	}
	return (lexer_start);
}

int	main(int argc, char **argv)
{
	char	*line;
	t_list	*start;

	if (argc > 1)
		line = argv[1];
	start = lexer(line);
	if (start)
		return (0);
	return (1);
}
