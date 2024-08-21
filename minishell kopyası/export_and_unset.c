/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_and_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:06:54 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:06:55 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	declare_export(void *data, t_shell *m_shell)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = m_shell->parse;
	new = (t_env *)data;
	write(str->outfile, "declare -x ", 11);
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	if (new->value && *(new->value) && new->key[0] > 31)
		write(str->outfile, "=", 1);
	i = 0;
	while (new->value && new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

int	export_print(char *text, t_shell *m_shell)
{
	char	*key;
	char	*value;

	if (!export_key_control(text))
	{
		write(2, "minishell: export: `", 20);
		write(2, text, ft_strlen(text));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	export_utils(&m_shell, &key, &value, text);
	edit_env(m_shell->env, key, value, m_shell);
	return (0);
}

int	exec_export(t_parse *data, t_shell *m_shell)
{
	int	i;

	i = 0;
	if (data->text == NULL)
		ft_newlstiter(m_shell->env, declare_export, m_shell);
	else
	{
		while (data->text[i])
		{
			if (export_print(data->text[i], m_shell))
			{
				m_shell->exec_status = 1;
				return (1);
			}
			i++;
		}
	}
	m_shell->exec_status = 0;
	return (0);
}

int	unset_edit(t_list **node, t_list **prev_node, t_shell *m_shell)
{
	t_env	*tmp;

	tmp = (*node)->content;
	if (*prev_node == NULL)
		m_shell->env = (*node)->next;
	else
		(*prev_node)->next = (*node)->next;
	free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free((*node)->content);
	free(*node);
	return (1);
}

void	exec_unset(t_parse *data, t_shell *m_shell, int i, int x)
{
	t_list	*prev_node;
	t_list	*node;
	t_env	*env;

	env = NULL;
	if (data->text == NULL)
		return ;
	while (data->text[i])
	{
		prev_node = NULL;
		node = m_shell->env;
		while (node != NULL)
		{
			env = (t_env *)node->content;
			if (ft_strcmp(env->key, data->text[i]) == 0)
				x = unset_edit(&node, &prev_node, m_shell);
			if (x)
				break ;
			prev_node = node;
			node = node->next;
		}
		i++;
	}
}
