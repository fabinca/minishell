/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:15:16 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/28 11:36:52 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_last_exit;

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

int	is_redirection_symbol(char *token_string)
{
	if (strcmp(">", token_string) == 0)
		return (1);
	if (strcmp("<", token_string) == 0)
		return (1);
	if (strcmp(">>", token_string) == 0)
		return (1);
	if (strcmp("<<", token_string) == 0)
		return (1);
	return (0);
}

char	*tok_err(t_list *tokens)
{
	char	last_tok; // p for pipe, r for redirection, s for string 
	char	new_tok;

	if (strcmp("|", tokens->content) == 0)
		return (tokens->content);
	last_tok = 's';
	if (is_redirection_symbol(tokens->content))
		last_tok = 'r';
	while (tokens->next)
	{
		tokens = tokens->next;
		new_tok = 's';
		if (is_redirection_symbol(tokens->content))
			new_tok = 'r';
		else if (strcmp("|", tokens->content) == 0)
			new_tok = 'p';
		if (new_tok == 'p' && last_tok == 'p')
			return (tokens->content);
		if (last_tok == 'r' && new_tok != 's')
			return (tokens->content);
		last_tok = new_tok;
	}
	if (last_tok != 's')
		return (tokens->content);
	return (NULL);
}

t_list	*lexer(char *line)
{
	t_list			*st;
	const size_t	len = ft_strlen(line);
	t_tok			token;

	token.start = 0;
	st = NULL;
	while (token.start < len)
	{
		token.len = token_length((line + token.start));
		token.string = ft_substr_strip_space(line, token.start, token.len);
		token.start = token.start + token.len;
		if (ft_strlen(token.string) == 0)
			break ;
		if (!st)
			st = ft_lstnew(token.string);
		else
			ft_lstadd_back(&st, ft_lstnew(token.string));
	}
	if (tok_err(st))
	{
		printf("bash: syntax error near unexpected token '%s'\n", tok_err(st));
		ft_lstclear(&st);
		return (NULL);
	}
	return (st);
}

int	main(void)
{
	char	line[100] = "<a >b echo $?a | cat '$HOME b' | sort -n >d ";
	t_list	*start;
	t_command *start_c;

	g_last_exit = 0;
	start = lexer(line);
	start_c = parser(start);
	printf("%s\n", line);
	while (start_c)
	{
		printf("commands: %s %s, fd_in: %d, fd_out: %d \n", start_c->cmd[0], start_c->cmd[1], start_c->fd_in, start_c->fd_out);
		start_c = start_c->next;
	}
	return (1);
}

