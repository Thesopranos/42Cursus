/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:03:47 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:03:47 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>

void	create_next_file(t_parse *parse, t_shell *m_shell)
{
	char	*pwd1;
	t_parse	*nparse;
	char	*home;

	pwd1 = NULL;
	home = NULL;
	create_files_utils2(&m_shell, &home);
	nparse = parse->next;
	if (!ft_strnstr(nparse->text[0], home, ft_strlen(home)))
		handle_relative_path(&pwd1, parse);
	else
		create_files_utils(&m_shell, home, nparse, &pwd1);
	if (nparse->type == 4)
		parse->fd = open(pwd1, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (nparse->type == 3)
		parse->fd = open(pwd1, O_CREAT | O_RDWR | O_TRUNC, 0777);
	parse->outfile = parse->fd;
	if (pwd1)
		free(pwd1);
	free(home);
}

void	create_multi_file(t_parse *current_parse, t_shell *m_shell)
{
	t_parse	*n_parse;
	int		i;
	int		j;

	n_parse = current_parse->next;
	i = 0;
	while (current_parse->text[i])
		i++;
	while (n_parse && n_parse->type != 2)
	{
		j = 1;
		while (n_parse->text[j])
		{
			current_parse->text[i] = ft_strdup(n_parse->text[j]);
			if (!current_parse->text[i])
				malloc_error(5, &m_shell);
			i++;
			j++;
		}
		n_parse = n_parse->next;
	}
	current_parse->text[i] = NULL;
	create_next_file(current_parse, m_shell);
}

void	create_out_files(t_parse *current_parse, t_parse *first_parse,
		t_shell *m_shell)
{
	char	*pwd;
	t_parse	*m_next;
	char	*home;

	pwd = NULL;
	home = NULL;
	create_files_utils2(&m_shell, &home);
	m_next = current_parse->next;
	if (m_next->type == GREAT || m_next->type == GREATER)
		return (free(home), create_multi_file(current_parse, m_shell));
	if (!ft_strnstr(m_next->text[0], home, ft_strlen(home)))
		handle_relative_path(&pwd, current_parse);
	else
		create_files_utils(&m_shell, home, m_next, &pwd);
	if (current_parse->type == GREATER)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (current_parse->type == GREAT)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (current_parse->cmd)
		current_parse->outfile = m_next->fd;
	else if (first_parse->cmd)
		first_parse->outfile = m_next->fd;
	if (pwd)
		free(pwd);
	free(home);
}

int	create_files(t_shell *m_shell)
{
	t_parse	*current_parse;
	t_parse	*first_parse;
	int		i;

	i = 1;
	current_parse = m_shell->parse;
	first_parse = m_shell->parse;
	while (current_parse)
	{
		if (current_parse->type == GREAT || current_parse->type == GREATER)
			create_out_files(current_parse, first_parse, m_shell);
		else if (current_parse->type == LESS)
			i = create_in_files_me(current_parse, m_shell);
		current_parse = current_parse->next;
	}
	return (i);
}
