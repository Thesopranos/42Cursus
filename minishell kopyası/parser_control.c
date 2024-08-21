/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:08:31 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:08:32 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	parse_cmd(t_shell **shell, t_parse *parse, char *str)
{
	parse->cmd = ft_strdup(str);
	if (!parse->cmd)
		malloc_error(5, shell);
}

void	parse_text_specifier(t_parse *parse, char *str, int *j, int *flag)
{
	parse->text[*j] = ft_strdup(str);
	*j += 1;
	parse->text[*j] = NULL;
	*flag = 1;
}

void	free_option_check(t_parse *parse, int flag)
{
	if (flag == 0)
	{
		free_parse_text(parse->text);
		parse->text = NULL;
	}
}

void	parse_type_specifier(t_parse **parse, const char *str)
{
	if (str[0] == '|')
		(*parse)->type = PIPE;
	else if (str[0] == '>' && str[1] == '>')
		(*parse)->type = GREATER;
	else if (str[0] == '<' && str[1] == '<')
	{
		(*parse)->type = HEREDOC;
		g_check_heredoc = 1;
	}
	else if (str[0] == '>')
		(*parse)->type = GREAT;
	else if (str[0] == '<')
		(*parse)->type = LESS;
}

t_parse	*initialize_parse(size_t len, t_shell **shell)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		malloc_error(5, shell);
	(parse)->next = NULL;
	(parse)->cmd = NULL;
	(parse)->text = ft_calloc(sizeof(char *), len + 1);
	if (!(parse)->text)
		malloc_error(5, shell);
	(parse)->type = 0;
	(parse)->infile = STDINN;
	(parse)->outfile = STDOUT;
	(parse)->fd = 1;
	(parse)->pid = 0;
	(parse)->control = 0;
	return (parse);
}
