/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:52:25 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/11 14:10:43 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_prompt(void)
{
	char	*user;
	char	*dir;
	char	pwd[100];

	user = getenv("USER");
	dir = ft_strrchr(getcwd(pwd, 100), '/');
	printf("%s%s:%s~%s$%s  ", GRN, user, BLU, dir, NRM);
}

void	sighandler(int num)
{
	if (num == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		display_prompt();
		printf("\033[1;36m\033[1mMinishell\033[0m$    ");
		rl_redisplay();
	}
}

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

void	lex_parse_execute(char *line, t_envvar *env_list)
{
	t_list		*lexer_tokens;
	t_command	*cmd_struct;
	t_command	*cmd_start;
	t_pipedata	p_data;

	if (is_only_whitespaces(line))
		return ;
	p_data.ct = 0;
	p_data.envlist = env_list;
	lexer_tokens = lexer(line);
	if (!lexer_tokens)
		return ;
	cmd_struct = parser(lexer_tokens, env_list);
	cmd_start = cmd_struct;
	if (!cmd_struct || !cmd_struct->cmd || !cmd_struct->cmd[0]) //do we need this? 
		return ;
	if (!cmd_struct->next && is_builtin(cmd_struct->cmd))
		parse_builtin(cmd_struct, env_list);
	else
	{
		p_data.paths = find_paths(env_list);
		
		pipe (p_data.oldpipe);
		pipex(p_data, env_list, cmd_struct, 1);
	}
	//unlink(".tmpheredoc");
	while (cmd_start)
	{
		cmd_struct = cmd_start->next;
		free_cmd_struct(cmd_start);
		cmd_start = cmd_struct;
	}
	//free_tokens(lexer_tokens);
	//free_my_paths(p_data.paths);
}

int	main(int argc, char **argv, char **envp)
{
	char 		*line;
	t_envvar	*env_list;

	g_last_exit = 0;
	if (argc != 1 || argv[1])
	{
		printf("Run program with ./minishell (no arguments\n");
		return (0);
	}
	add_history("");
	signal(SIGINT, sighandler); //ctrl c
	signal(SIGQUIT, SIG_IGN); // ctrl backslash
	//signal(EOF, sighandler);
	env_list = init_envp_list(envp);
	while (1)
	{
		display_prompt();
		line = readline("\033[1;36m\033[1mMinishell\033[0m$ ");
		if (!line)
			break ;
		add_history(line);
		lex_parse_execute(line, env_list);
		free(line);
	}
	free_var_list(env_list);
	printf("\n");
	return (0);
}

//test for heredoc
/* int	main(void)
{
	exe_heredoc("three");
	unlink(".tmpheredoc");
	return (0);
} */
