/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:09:15 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:09:26 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	malloc_error(int control, t_shell **shell)
{
	if (control > 4)
		free_parser(*shell);
	if (control > 3)
	{
		free_lexes(&((*shell)->lex_list));
		if ((*shell)->cmd)
			free((*shell)->cmd);
	}
	if (control > 2)
		free_env(*shell);
	if (control > 1 && (*shell)->env)
		free((*shell)->env);
	if (control > 0)
		free(*shell);
	printf("Memory allocation error\n");
	exit(control);
}

void	free_utils(t_shell **shell, char *back, char *after, char *before)
{
	free(after);
	if (!back)
	{
		free(before);
		malloc_error(4, shell);
	}
}

void	tilde_utils(char *tmp, char *home, t_list *lex, t_shell *shell)
{
	tmp = ft_strdup(lex->content);
	if (!tmp)
	{
		free(home);
		malloc_error(4, &shell);
	}
	free(lex->content);
	lex->content = ft_strjoin(home, tmp + 1);
	if (!lex->content)
	{
		free(home);
		free(tmp);
		malloc_error(4, &shell);
	}
	free(tmp);
	free(home);
}

void	edit_env_(t_list *node, char *key, char *value, t_shell *m_shell)
{
	t_env	*new_env;

	if (node == NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return ;
		new_env->key = key;
		new_env->value = value;
		ft_lstadd_back(&(m_shell->env), ft_lstnew(new_env));
	}
}

char	*get_home(t_shell *m_shell)
{
	t_list	*tmp;
	t_env	*env;

	tmp = m_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "HOME"))
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}
