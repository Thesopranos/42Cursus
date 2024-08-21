/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:07:34 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/20 15:53:21 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	ignore_quote(char const *cmd, int i)
{
	if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"')
			i++;
	}
	else if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'')
			i++;
	}
	return (i);
}

static int	len_for_separate(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (0);
	if (cmd[i] == '<' && cmd[i + 1] == '<')
		return (2);
	if (cmd[i] == '>' && cmd[i + 1] == '>')
		return (2);
	if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
		return (1);
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '>' && cmd[i] != '<'
		&& cmd[i] != '|')
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i = ignore_quote(cmd, i) + 1;
		}
		else
			i++;
	}
	return (i);
}

void	lexer(char *cmd, t_list **lex_list, t_shell **shell) // ÖĞRENİLDİ
{ 	// BU FONKSİYON KULLANICININ GİRDİĞİ KOMUTLARI PARÇALARA AYIRIR
	// ÖRNEK: ls -l | grep "mert" > file.txt
	// BU KOMUTU AYIRDIĞIMIZDA
	// ls
	// -l
	// |
	// grep
	// "mert"
	// >
	// file.txt
	// OLARAK AYIRIR
	int		len;
	char	*content;
	char	*trimmed_content;

	if (!cmd || !*cmd) // "" veya NULL ise
		return ;
	cmd = ft_strtrim(cmd, " ");
	if (!cmd)
		malloc_error(4, shell);
	len = len_for_separate(cmd);
	content = ft_substr(cmd, 0, len);
	if (!content)
		malloc_error(4, shell);
	trimmed_content = ft_strtrim(content, " ");
	if (!trimmed_content)
		malloc_error(4, shell);
	free(content);
	ft_lstadd_back(lex_list, ft_lstnew(trimmed_content));
	lexer(cmd + len, lex_list, shell);
	free(cmd);
}
