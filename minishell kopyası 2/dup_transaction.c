/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_transaction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:04:00 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:04:01 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	create_heredoc_dup(t_shell *m_shell)
{
	int	new_fd[2];

	pipe(new_fd);
	write(new_fd[1], m_shell->heredoc, ft_strlen(m_shell->heredoc));
	dup2(new_fd[0], 0);
	close(new_fd[1]);
	close(new_fd[0]);
}

void	create_dup(t_shell *m_shell, t_parse *parse)
{
	if (parse->type == HEREDOC)
		create_heredoc_dup(m_shell);
	if (parse->infile > STDERR)
		dup2(parse->infile, 0);
	if (parse->outfile > STDERR)
		dup2(parse->outfile, 1);
}

void	create_dup_one(t_parse *parse, int *fd)
{
	t_parse	*nparse;

	nparse = parse->next;
	close(fd[0]);
	if (parse->next && fd && nparse->cmd)
		dup2(fd[1], 1);
	else if (parse->type == HEREDOC && parse->next->next)
		dup2(fd[1], 1);
	close(fd[1]);
}

void	create_dup_two(t_parse *parse, int *fd)
{
	close(fd[1]);
	if (fd && parse->control != 1)
		dup2(fd[0], 0);
	close(fd[0]);
}
