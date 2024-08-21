/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:08:31 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/21 04:55:33 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	parse_cmd(t_shell **shell, t_parse *parse, char *str)
{
	// parse_cmd fonksiyonu shell adında bir t_shell ** ve parse adında bir t_parse struct'ı ve str adında bir char * alır
	// bu fonksiyon parse struct'ının cmd elemanına str'in kopyasını atar
	// eğer parse struct'ının cmd elemanına str'in kopyasını atamak başarısız olursa malloc_error fonksiyonunu çağırır
	parse->cmd = ft_strdup(str);
	if (!parse->cmd)
		malloc_error(5, shell);
}

void	parse_text_specifier(t_parse *parse, char *str, int *j, int *flag)
{
	// parse_text_specifier fonksiyonu parse adında bir t_parse struct'ı ve str adında bir char * ve j adında bir int * ve flag adında bir int * alır
	// bu fonksiyon parse struct'ının text elemanına str'in kopyasını atar
	// eğer parse struct'ının text elemanına str'in kopyasını atamak başarısız olursa malloc_error fonksiyonunu çağırır
	// j'nin değerini 1 artırır
	// parse struct'ının text elemanına NULL ekler
	// flag'i 1 yapar
	// bu sayede parse struct'ının text elemanına str'in kopyasını atar ve flag'i 1 yapar
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
	// parse_type_specifier fonksiyonu parse adında bir t_parse ** ve str adında bir const char * alır
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
	// initialize_parse fonksiyonu len adında bir size_t alır ve shell adında bir t_shell ** alır
	// bu fonksiyon t_parse struct'ı oluşturur ve döndürür
	// bu fonksiyonun içinde parse adında bir t_parse struct'ı oluşturulur
	// parse struct'ının next elemanı NULL olarak atanır
	// parse struct'ının cmd elemanı NULL olarak atanır
	// parse struct'ının text elemanı len + 1 boyutunda bir char ** oluşturulur ve NULL olarak atanır
	// parse struct'ının type elemanı 0 olarak atanır
	// parse struct'ının infile elemanı STDINN olarak atanır
	// parse struct'ının outfile elemanı STDOUT olarak atanır
	// parse struct'ının fd elemanı 1 olarak atanır
	// parse struct'ının pid elemanı 0 olarak atanır
	// parse struct'ının control elemanı 0 olarak atanır
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
