/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:05:36 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:05:36 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	run_command(char **env, t_parse *tmp, int *fd, t_shell *m_shell)
{
	int	control;

	control = is_builtin(tmp);
	if (control)
		execute_builtin_command(tmp, m_shell);
	else
		run_execve(tmp, env, fd, m_shell);
	free_env(m_shell);
	free_loop(1, m_shell);
	if (m_shell->lex_list)
		free(m_shell->lex_list);
	free(m_shell);
	exit(0);
}

void	run_single_command(char **env, t_parse *parse, t_shell *m_shell)
{
	int	control;

	control = 0;
	if (parse->type != HEREDOC)
		control = is_builtin(parse);
	if (control)
		execute_builtin_command(m_shell->parse, m_shell);
	else
		run_execve(m_shell->parse, env, NULL, m_shell);
}

void	multi_command(t_parse *parse, char **env, t_shell *m_shell, int *fd)
{
	t_parse	*nparse;

	while (parse)
	{
		if (parse->next)
			pipe(fd);
		nparse = get_next_cmd(&parse);
		parse->pid = fork();
		if (parse->pid == 0)
		{
			create_dup_one(parse, fd);
			run_command(env, parse, fd, m_shell);
		}
		if (nparse)
			create_dup_two(nparse, fd);
		parse = nparse;
	}
}

void	run_multi_command(char **env, t_parse *parse, t_shell *m_shell)
{
	int	fd[2];

	m_shell->parse->std_in = dup(0);
	multi_command(parse, env, m_shell, fd);
	dup2(m_shell->parse->std_in, 0);
	clear_pipe(fd);
	wait_all(m_shell);
}

void	exec(char **env, t_shell *m_shell)
{
	int	x;

	if (g_check_heredoc != 0)
		loop_heredoc(m_shell);
	if (m_shell->parse->cmd && !ft_strcmp(m_shell->parse->cmd, "exit")
		&& g_check_heredoc != -10 && get_next_cmd(&m_shell->parse) == NULL)
	{
		builtin_exit(&m_shell);
		return ;
	}
	x = single_or_multi_command(m_shell);
	if (!x && g_check_heredoc != -10)
		run_single_command(env, m_shell->parse, m_shell);
	else if (g_check_heredoc != -10)
		run_multi_command(env, m_shell->parse, m_shell);
	g_check_heredoc = 0;
}
