/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:08:43 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/21 06:13:59 by mertcaki         ###   ########.fr       */
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
	// bu fonksiyon shell->lex_list'in içindeki contentlerin uygun olup olmadığını kontrol eder
	// bu fonksiyonun içinde initialize_parse fonksiyonu çağırılır
	// initialize_parse fonksiyonu parse struct'ını initialize eder
	// bu fonksiyonun içinde parse_cmd fonksiyonu çağırılır
	// parse_cmd fonksiyonu shell->parse deki komutları parse eder
	// parse_cmd fonksiyonu başarılı bir şekilde çalıştıysa initialize_parse fonksiyonu çağırılır
	t_parse	*parse;

	parse = initialize_parse((size_t)ft_lstsize(lex), &shell);
	// parse struct'ını initialize eder

	shell->parse = parse;
	while (lex != NULL)
	{
		str = lex->content;
		// str değişkenine lex->content atanır
		// bu conten örnek olarak: ls | wc -l > file.txt
		if (flags[0]++ == 0 && ft_strcmp(str, "<<"))
			parse_cmd(&shell, parse, str);
		// eğer flags[0] 0 ise ve str "<< değilse parse_cmd fonksiyonunu çağırır
		// parse_cmd fonksiyonu shell->parse deki komutları parse eder
		else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		{
			// eğer str'ın ilk karakteri '|' veya '>' veya '<' ise
			// parse_type_specifier fonksiyonunu çağırır
			if (parse_type_specifier(&parse, str), str[0] == '|')
				flags[0] = 0;
			// eğer str'ın ilk karakteri '|' ise flags[0] 0 yapar
			// bu sayede ls | wc -l > file.txt gibi bir komutu kontrol eder
			// eğer str'ın ilk karakteri '>' veya '<' ise flags[0] 0 yapmaz
			// bu sayede ls > file.txt gibi bir komutu kontrol eder
			parse->next = initialize_parse((size_t)ft_lstsize(lex), &shell);
			// parse struct'ını initialize eder
			flags[1] = 0;
			remove_quotes_in_parse(parse);
			// remove_quotes_in_parse fonksiyonunu çağırır
			// bu fonksiyon parse struct'ındaki cmd ve text elemanlarındaki tırnakları kaldırır
			// bu sayede ls "file.txt" gibi bir komutu kontrol eder
			// bu sayede ls 'file.txt' gibi bir komutu kontrol eder
			parse = parse->next;
		}
		else if (ft_strcmp(str, ""))
			// eğer str boş değilse
			// parse_text_specifier fonksiyonunu çağırır
			// bu fonksiyon parse struct'ının text elemanına str'i atar
			// bu sayede ls file.txt gibi bir komutu kontrol eder
			parse_text_specifier(parse, str, &flags[1], &flags[2]);
		remove_quotes_in_parse(parse);
		// remove_quotes_in_parse fonksiyonunu çağırır
		// bu fonksiyon parse struct'ındaki cmd ve text elemanlarındaki tırnakları kaldırır
		// bu sayede ls "file.txt" gibi bir komutu kontrol eder
		lex = lex->next;
		// lex'in next elemanına geçer
	}
	free_option_check(parse, flags[2]);
	// free_option_check fonksiyonunu çağırır
	// bu fonksiyon parse struct'ının text elemanını free eder
}

int	parser(t_shell *shell, int flags[3])
{
	// bu fonksiyonun amacı, shell->lex_list'in içindeki contentlerin uygun olup olmadığını kontrol etmek
	// öncelikle shell->lex_list'in içindeki contentlerin uygun olup olmadığını kontrol etmek için start_parse fonksiyonunu çağırır
	// start_parse fonksiyonu shell->lex_list'in içindeki contentlerin uygun olup olmadığını kontrol eder
	// start_parse fonksiyonu başarılı bir şekilde çalıştıysa create_files fonksiyonunu çağırır
	// create_files fonksiyonu shell->parse deki komutları parse eder ve exec etmeye hazır hale getirir
	// create_files fonksiyonu başarılı bir şekilde çalıştıysa 1 döndürür
	// create_files fonksiyonu başarısız bir şekilde çalıştıysa 0 döndürür
	// bu fonksiyonun sonunda free_lexes fonksiyonu çağırılır
	// free_lexes fonksiyonu shell->lex_list deki contentleri free eder
	t_list	*b;
	char	*content;

	content = NULL;
	b = shell->lex_list;
	start_parse(b, shell, flags, content);
	free_lexes(&shell->lex_list);
	return (create_files(shell));
}
