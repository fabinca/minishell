/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:52:25 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/12 12:58:20 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
void	lex_parse_execute(char *line, t_envvar *envvar, char **envp) //for testing builtins
{
	t_list		*lexer_tokens;
	t_command	*cmd_struct;
	t_command	*cmd_temp;
	t_pipedata	p_data;

	if (is_only_whitespaces(line))
		return ;
	p_data.ct = 0;
	lexer_tokens = lexer(line);
	cmd_struct = parser(lexer_tokens);
	if (!cmd_struct) //do we need this? 
		return ;
	exec_cmd(cmd_struct, envvar, envp);
	free_tokens(lexer_tokens);
} */

void	lex_parse_execute(char *line, t_envvar *env_list, t_envvar *export_list)
{
	t_list		*lexer_tokens;
	t_command	*cmd_struct;
	t_pipedata	p_data;

	if (is_only_whitespaces(line))
		return ;
	p_data.first_cmd = 1;
	p_data.envlist = env_list;
	lexer_tokens = lexer(line);
	if (!lexer_tokens)
		return ;
	cmd_struct = parser(lexer_tokens, env_list);
	if (!cmd_struct || !cmd_struct->cmd || !cmd_struct->cmd[0]) //do we need this? 
		return ;
	if (!cmd_struct->next && is_builtin(cmd_struct->cmd))
		parse_builtin(cmd_struct, env_list, export_list);
	else
	{
		p_data.paths = find_paths(env_list);
		//pipex(p_data, env_list, cmd_struct, 1);
		//cmd_start = cmd_struct;
		pipe (p_data.oldpipe);
		pipex(p_data, env_list, export_list, cmd_struct);
		free_my_paths(p_data.paths);
	}
	free_complete_struct(cmd_struct);
	free_tokens(lexer_tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_envvar	*env_list;
	t_envvar	*export_list;

	g_last_exit = 0;
	if (argc != 1 || argv[1])
	{
		printf("Run program with ./minishell (no arguments\n");
		return (0);
	}
	add_history("");
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	env_list = init_envp_list(envp);
	export_list = duplicate_list(env_list);
	while (1)
	{
		display_prompt();
		line = readline("\033[1;36m\033[1mMinishell\033[0m$ ");
		if (!line)
			break ;
		add_history(line);
		lex_parse_execute(line, env_list, export_list);
		free(line);
	}
	free_var_list(env_list);
	free_var_list(export_list);
	printf("\n");
	return (0);
}
