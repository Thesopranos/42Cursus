/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:03:13 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/20 15:38:33 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	is_valid_other(char *a, char *b)
{
	if ((a[0] == '<' && !a[1]) && !b)
		// eğer a'nın ilk karakteri '<' ve a'nın ikinci karakteri yoksa ve b yoksa
		// bu sayede ls < gibi bir komutu kontrol eder.
		return (0);
	else if ((a[0] == '>' && !a[1]) && (!ft_strcmp(a, b)))
		// eğer a'nın ilk karakteri '>' ve a'nın ikinci karakteri yoksa ve a ve b aynıysa
		// bu sayede ls > gibi bir komutu kontrol eder.
		return (0);
	else if (((a[0] == '<' && !a[1])) && (!ft_strcmp(a, b)))
		// eğer a'nın ilk karakteri '<' ve a'nın ikinci karakteri yoksa ve a ve b aynıysa
		// bu sayede ls < gibi bir komutu kontrol eder.
		return (0);
	else if (((a[0] == '<' && a[1] == '<')) && (!ft_strcmp(a, b)))
		// eğer a'nın ilk karakteri '<' ve a'nın ikinci karakteri '<' ve a ve b aynıysa
		// bu sayede ls << gibi bir komutu kontrol eder.
		return (0);
	else if (((a[0] == '>' && a[1] == '>')) && (!ft_strcmp(a, b)))
		// eğer a'nın ilk karakteri '>' ve a'nın ikinci karakteri '>' ve a ve b aynıysa
		// bu sayede ls >> gibi bir komutu kontrol eder.
		return (0);
	else if (((a[0] == '<' && a[1] != '<')) && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		// eğer a'nın ilk karakteri '<' ve a'nın ikinci karakteri '<' değilse ve b'nin ilk karakteri '<' veya '>' veya '|' ise
		// bu sayede ls < | gibi bir komutu kontrol eder.
		return (0);
	else if ((a[0] == '>' && a[1] != '>') && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		// eğer a'nın ilk karakteri '>' ve a'nın ikinci karakteri '>' değilse ve b'nin ilk karakteri '<' veya '>' veya '|' ise
		// bu sayede ls > | gibi bir komutu kontrol eder.
		return (0);
	else if (((a[0] == '<' && a[1] == '<')) && (b[0] == '>' || b[0] == '|'))
		// eğer a'nın ilk karakteri '<' ve a'nın ikinci karakteri '<' ve b'nin ilk karakteri '>' veya '|' ise
		// bu sayede ls << > gibi bir komutu kontrol eder.
		return (0);
	else if ((a[0] == '>' && a[1] == '>') && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		// eğer a'nın ilk karakteri '>' ve a'nın ikinci karakteri '>' ve b'nin ilk karakteri '<' veya '>' veya '|' ise
		// bu sayede ls >> | gibi bir komutu kontrol eder.
		return (0);
	else if ((a[0] == '|' && !a[1] && b[0] == '|' && !b[1]))
		// eğer a'nın ilk karakteri '|' ve a'nın ikinci karakteri yoksa ve b'nin ilk karakteri '|' ve b'nin ikinci karakteri yoksa
		// bu sayede | | gibi bir komutu kontrol eder.
		return (0);
	return (1);
}

int	cmd_check(t_list *lex_list, char *a, char *b)
{
	// bu fonksiyonun amacı, lex_list'in içindeki contentlerin uygun olup olmadığını kontrol etmek.
	// örnek lex_list içeriği: ls | wc -l > file.txt
	// eğer uygun değilse print_error fonksiyonunu çağırıyor.
	// eğer uygunsa 1 döndürüyor.
	// a ve b değişkenleri, lex_list'in contentlerini tutar.
	// örnek a ve b değişkenleri: a = ls, b = wc
	// tmp değişkeni, lex_list'in başlangıcını tutar.
	// i değişkeni, lex_list'in kaçıncı elemanında olduğumuzu tutar.
	// i = 0 ise ve a'nın ilk karakteri '<' veya '>' ise print_error fonksiyonunu çağırır.
	// a'nın ilk karakteri '|' ve a'nın ikinci karakteri yoksa print_error fonksiyonunu çağırır.
	// a'nın ilk karakteri '>' ve a'nın ikinci karakteri yoksa ve b yoksa print_error fonksiyonunu çağırır.
	// is_valid_other fonksiyonunu çağırır.
	// eğer is_valid_other fonksiyonu 0 döndürürse print_error fonksiyonunu çağırır.
	// eğer hiçbir koşul sağlanmazsa 1 döndürür.
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lex_list;
	while (tmp)
	{
		a = tmp->content;
		// a değişkenine tmp'nin contentini atar.
		if (tmp->next)
		// eğer tmp'nin next'i varsa
			b = tmp->next->content;
			// b değişkenine tmp'nin next'inin contentini atar.
		if (i == 0 && !b && ((a[0] == '<') || (a[0] == '>')))
			// eğer i = 0 ve b yoksa ve a'nın ilk karakteri '<' veya '>' ise
			// bu sayede ls < file.txt gibi bir komutu kontrol eder.
			// ls . > file.txt && ls < file.txt
			return (print_error());
		if ((a[0] == '|' && !a[1]) && i == 0)
			// eğer a'nın ilk karakteri '|' ve a'nın ikinci karakteri yoksa ve i = 0 ise
			// bu sayede | ls gibi bir komutu kontrol eder.
			return (print_error());
		else if ((a[0] == '>' && !a[1]) && !b)
			// eğer a'nın ilk karakteri '>' ve a'nın ikinci karakteri yoksa ve b yoksa
			// bu sayede ls > gibi bir komutu kontrol eder.
			return (print_error());
		else if (!is_valid_other(a, b))
			// eğer is_valid_other fonksiyonu 0 döndürürse
			// bu sayede ls > > gibi bir komutu kontrol eder.
			return (print_error());
		tmp = tmp->next;
		// tmp'yi bir sonraki elemana atar.
		i++;
		// i'yi bir arttırır.
	}
	// eğer hiçbir koşul sağlanmazsa 1 döndürür.
	// bu sayede herhangi bir hata yoksa 1 döndürür.
	return (1);
}

int	quote_len1(char *data)
{
	int	j;
	int	i;
	int	a;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '\"' || data[i] == '\'')
		{
			j++;
			a = data[i++];
			while (data[i] && data[i] != a)
			{
				i++;
			}
			if (!data[i])
				break ;
			j++;
		}
		i++;
	}
	return (j);
}

int	quote_check(char *data)
{
	int	x;

	x = 0;
	x = quote_len1(data);
	if (x % 2 != 0)
	{
		printf("minishell: quote error\n");
		return (0);
	}
	return (1);
}
