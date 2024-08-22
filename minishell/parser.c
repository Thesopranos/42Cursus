/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:08:43 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/18 23:08:44 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quotes_in_str(char *str)
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote_char;

	i = 0;
	j = 0;
	in_quotes = 0;
	quote_char = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (!in_quotes
				|| quote_char == str[i]))
		{
			in_quotes = !in_quotes;
			if (in_quotes)
				quote_char = str[i];
			else
				quote_char = '\0';
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

static void	remove_quotes_in_parse(t_parse *parse)
{
	char	**text_ptr;

	if (parse != NULL)
	{
		if (parse->cmd != NULL)
			remove_quotes_in_str(parse->cmd);
		if (parse->text != NULL)
		{
			text_ptr = parse->text;
			while (*text_ptr != NULL)
			{
				remove_quotes_in_str(*text_ptr);
				text_ptr++;
			}
		}
		remove_quotes_in_parse(parse->next);
	}
}

void	start_parse(t_list *lex, t_shell *shell, int flags[3], char *str)
{
	t_parse	*parse;

	parse = initialize_parse((size_t)ft_lstsize(lex), &shell);
	shell->parse = parse;
	while (lex != NULL)
	{
		str = lex->content;
		if (flags[0]++ == 0 && ft_strcmp(str, "<<"))
			parse_cmd(&shell, parse, str);
		else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		{
			if (parse_type_specifier(&parse, str), str[0] == '|')
				flags[0] = 0;
			parse->next = initialize_parse((size_t)ft_lstsize(lex), &shell);
			flags[1] = 0;
			parse = parse->next;
		}
		else if (ft_strcmp(str, ""))
			parse_text_specifier(parse, str, &flags[1], &flags[2]);
		remove_quotes_in_parse(parse);
		lex = lex->next;
	}
	free_option_check(parse, flags[2]);
}

int	parser(t_shell *shell, int flags[3])
{
	t_list	*b;
	char	*content;

	content = NULL;
	b = shell->lex_list;
	start_parse(b, shell, flags, content);
	free_lexes(&shell->lex_list);
	return (create_files(shell));
}
