/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:06:31 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:06:39 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	expand_dollar_variable(t_shell *shell, t_list *lex, char **temp,
		char *before)
{
	char	*new_value;

	if (ft_isdigit((*temp)[1]))
	{
		new_value = ft_strdup(*temp + 2);
		free_utils3(&shell, before, new_value, lex);
		*temp = ft_strchr(lex->content + ft_strlen(before), '$');
	}
	else if (!ft_isdigit((*temp)[1]))
	{
		new_value = get_env(shell->env, *temp + 1);
		free(lex->content);
		lex->content = ft_strjoin(before, new_value);
		if (!(char *)lex->content)
		{
			lex->content = ft_strdup(before);
			free_utils4(&shell, before, new_value, lex);
		}
		free(new_value);
		*temp = ft_strchr(lex->content + ft_strlen(before), '$');
	}
}

void	expand_question_mark(t_shell *shell, t_list *lex, char **temp,
		char *before)
{
	char	*after;
	char	*back;
	char	*new_value;

	new_value = NULL;
	after = ft_strdup(*temp + 2);
	free(lex->content);
	new_value = ft_itoa((shell)->exec_status);
	if (!new_value)
	{
		free(after);
		free(before);
		malloc_error(4, &shell);
	}
	back = ft_strjoin(new_value, after);
	free(new_value);
	free_utils(&shell, back, after, before);
	lex->content = ft_strjoin(before, back);
	free_utils2(&shell, back, lex, before);
	free(back);
	*temp = ft_strchr(lex->content + ft_strlen(before), '$');
}

static void	expand_tilde(t_shell *shell, t_list *lex)
{
	char	*tmp;
	char	*home;

	tmp = NULL;
	home = get_env(shell->env, "HOME");
	if (!home)
		malloc_error(4, &shell);
	if (((char *)lex->content)[0] == '~' && ((char *)lex->content)[1] == '/')
		tilde_utils(tmp, home, lex, shell);
	else if (((char *)lex->content)[0] == '~'
		&& ((char *)lex->content)[1] == '\0')
	{
		free(lex->content);
		lex->content = home;
	}
	else
		free(home);
}

void	expand_dollar(t_shell *shell, t_list *lex, char **temp, char *before)
{
	if ((*temp)[1] == '?')
		expand_question_mark(shell, lex, temp, before);
	else if ((*temp)[1] != '$' && ft_strcmp((*temp), "$") != 0)
		expand_dollar_variable(shell, lex, temp, before);
	else
		*temp = ft_strchr(*temp + 1, '$');
}

void	expander(t_shell *shell)
{
	char	*temp;
	t_list	*lex;
	char	*before;

	lex = shell->lex_list;
	while (lex)
	{
		if (((char *)lex->content)[0] == '~')
			expand_tilde(shell, lex);
		temp = ft_strchr(lex->content, '$');
		while (temp)
		{
			before = ft_substr(lex->content, 0, temp - (char *)lex->content);
			if (check_quote(before, temp))
				expand_dollar(shell, lex, &temp, before);
			else
				temp = ft_strchr(temp + 1, '$');
			free(before);
		}
		lex = lex->next;
	}
}
