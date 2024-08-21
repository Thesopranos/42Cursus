/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:09:06 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:09:07 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_relative_path(char **pwd, t_parse *current_parse)
{
	char	*str;
	char	*temp;
	t_parse	*m_next;

	str = getcwd(NULL, 0);
	m_next = current_parse->next;
	*pwd = ft_strjoin(str, "/");
	free(str);
	temp = ft_strjoin(*pwd, m_next->text[0]);
	free(*pwd);
	*pwd = temp;
}

void	wait_all(t_shell *m_shell)
{
	t_parse	*data;

	data = m_shell->parse;
	while (data)
	{
		if (!data->next)
			waitpid(data->pid, &m_shell->exec_status, 0);
		else
			waitpid(data->pid, 0, 0);
		data = data->next;
	}
	m_shell->exec_status = WEXITSTATUS(m_shell->exec_status);
}

void	clear_pipe(int *fd)
{
	int	index;

	if (fd)
	{
		index = -1;
		while (++index < 2)
		{
			if (fd[index])
				close(fd[index]);
		}
	}
}

void	ft_newlstiter(t_list *lst, void (*f)(void *, t_shell *), t_shell *shell)
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content, shell);
		lst = lst->next;
	}
}

char	*ft_mini_strdup2(size_t len, char *s, int i, const char *str)
{
	int	j;

	j = 0;
	while (i < (int)len)
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				s[j++] = str[i++];
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				s[j++] = str[i++];
			i++;
		}
		else
			s[j++] = str[i++];
	}
	s[j] = '\0';
	return (s);
}
