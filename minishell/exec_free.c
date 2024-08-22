/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:04:28 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:04:28 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

void	free_all_env(t_list *tmp2, t_shell *m_shell)
{
	t_env	*tmp;

	while (tmp2)
	{
		tmp = tmp2->content;
		if (tmp2->content)
		{
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
		tmp2 = tmp2->next;
	}
	while (m_shell->env)
	{
		tmp2 = m_shell->env;
		m_shell->env = m_shell->env->next;
		if (tmp2)
			free(tmp2);
	}
}

void	free_env(t_shell *m_shell)
{
	t_list	*tmp2;

	tmp2 = m_shell->env;
	if (tmp2 && tmp2->content)
		free_all_env(tmp2, m_shell);
	else if (m_shell->env && !m_shell->env->content)
		free(m_shell->env);
	clear_history();
}

void	free_loop(int control, t_shell *m_shell)
{
	if (m_shell->cmd)
		free(m_shell->cmd);
	if (control)
	{
		if (m_shell->parse)
			free_parser(m_shell);
	}
	if (m_shell->heredoc)
	{
		free(m_shell->heredoc);
		m_shell->heredoc = NULL;
	}
}

void	execve_child_free(char **str, t_shell *m_shell)
{
	free_env(m_shell);
	free_loop(1, m_shell);
	free_parse_text(str);
	if (m_shell->lex_list)
		free(m_shell->lex_list);
	free(m_shell);
}
