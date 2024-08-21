/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:07:21 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:07:22 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

char	*add_character(char *str, char a)
{
	char	*tmp;
	int		i;
	int		len;

	if (str == NULL)
		len = 0;
	else
		len = ft_strlen(str);
	tmp = ft_calloc(sizeof(char) * (len + 2), 1);
	if (!tmp)
		return (NULL);
	i = 0;
	if (!a)
	{
		free(tmp);
		return (NULL);
	}
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = a;
	free(str);
	return (tmp);
}

void	get_var(int *fd, t_shell *m_shell)
{
	char	*a;

	if (m_shell->heredoc)
		m_shell->heredoc = (free(m_shell->heredoc), NULL);
	a = malloc(sizeof(char));
	if (!a)
	{
		m_shell->heredoc = NULL;
		return ;
	}
	while (read(fd[0], a, 1))
	{
		m_shell->heredoc = add_character(m_shell->heredoc, *a);
		free(a);
		a = malloc(sizeof(char));
		if (!a)
			return ;
	}
	if (a)
		free(a);
	close(fd[0]);
}

void	get_input(t_parse *parse, int *fd)
{
	char	*delimiter;
	char	*buffer;

	delimiter = parse->next->text[0];
	while (1 && g_check_heredoc != -3)
	{
		buffer = readline("> ");
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			if (buffer)
				free(buffer);
			break ;
		}
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
		if (buffer)
			free(buffer);
	}
}

void	heredoc(t_parse *parse, t_shell *m_shell)
{
	int	fd[2];
	int	id;

	pipe(fd);
	signal(SIGINT, set_heredoc);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, killer);
		close(fd[0]);
		get_input(parse, fd);
		close(fd[1]);
		free_env(m_shell);
		free_loop(1, m_shell);
		if (m_shell->lex_list)
			free(m_shell->lex_list);
		free(m_shell);
		exit(1);
	}
	waitpid(-1, NULL, 0);
	signal(SIGINT, signals);
	close(fd[1]);
	get_var(fd, m_shell);
}

void	loop_heredoc(t_shell *m_shell)
{
	t_parse	*parse;

	parse = m_shell->parse;
	while (parse)
	{
		if (parse->type == HEREDOC)
		{
			heredoc(parse, m_shell);
		}
		parse = parse->next;
	}
}
