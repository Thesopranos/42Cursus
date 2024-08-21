/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:06:06 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/20 15:20:13 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	is_numeric(char *s)
{
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s == 43 || *s == 45)
		s++;
	while (48 <= *s && *s <= 57)
		s++;
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s != '\0')
		return (0);
	return (1);
}

void	exit_utils(char **text, int *exit_value)
{
	printf("bash: exit: %s: numeric argument required\n",
		text[0]);
	*exit_value = 255;
}

void	builtin_exit(t_shell **m_shell)
{
	char	**text;
	int		status;
	int		exit_value;

	status = -1;
	exit_value = (*m_shell)->exec_status;
	text = (*m_shell)->parse->text;
	printf("exit\n");
	if (!!text && text[0])
		status = is_numeric(text[0]);
	if (status == 0 && !!text && text[0])
		exit_utils(text, &exit_value);
	else if (status == 1 && !!text && !text[1] && text[0])
		exit_value = ft_atoi(text[0]);
	else if (status != -1)
	{
		printf("bash: exit: too many arguments\n");
		(*m_shell)->exec_status = 1;
		return ;
	}
	(free_loop(1, *m_shell), free_env(*m_shell));
	(free((*m_shell)->lex_list), free(*m_shell));
	exit(exit_value);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	env_get(char **env, t_shell **shell) // ÖĞRENİLDİ
{ // BİLGİSAYARDAKİ ENV DEĞİŞKENLERİNİ ALIP SHELL->ENV LİSTESİNE ATAR
	t_env	*new_node;
	char	**str;

	free((*shell)->env);
	(*shell)->env = NULL;
	while (*env)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			malloc_error(2, shell);
		str = ft_split(*env, '=');
		if (!str)
			malloc_error(2, shell);
		if (str && str[0] && str[1])
		{
			new_node->key = ft_strdup(str[0]);
			new_node->value = ft_strdup(str[1]);
			ft_lstadd_back(&(*shell)->env, ft_lstnew(new_node));
		}
		free_str(str);
		env++;
	}
}
