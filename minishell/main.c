/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:07:46 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/21 05:54:10 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int		g_check_heredoc;

void	initialize_shell(t_shell **shell) // ÖĞRENİLDİ
{
	// SHELL STRUCT'INI OLUŞTURUR HATA DURUMLARINI KONTROL EDER
	*shell = malloc(sizeof(t_shell));
	if (!(*shell))
		malloc_error(0, shell);
	(*shell)->env = malloc(sizeof(t_env));
	if (!(*shell)->env)
		malloc_error(1, shell);
	(*shell)->parse = NULL;
	(*shell)->lex_list = NULL;
	(*shell)->exec_status = 0;
	(*shell)->heredoc = NULL;
	(*shell)->cmd = NULL;
	g_check_heredoc = 0;
}

void	get_readline(t_shell *shell) // ÖĞRENİLDİ
{	// BU FONKSİYON KULLANICININ GİRDİĞİ KOMUTLARI ALIR
	shell->cmd = readline("\e[32mminishell\e[35m$ \e[0m");
	if (shell->cmd && !is_space(shell->cmd))
	{
		free(shell->cmd);
		get_readline(shell);
	}
	if (!shell->cmd)
	{ // bu kısım kullanıcı ctrl + D yaparsa çalışır böyle olunca readline fonksiyonu NULL döner
		free_loop(0, shell);
		free_env(shell);
		if (shell->lex_list)
			free(shell->lex_list);
		free(shell);
		exit(0);
	}
	add_history(shell->cmd);
	// bu kısım kullanıcının girdiği komutları history'e ekler
	// history dediğimize kullanıcının daha önce girdiği komutları gösteren kısım
}

void	parse_exec(t_shell *shell, char **env)
{
	// bu fonksiyon shell adında bir struct alır ve env adında bir char ** alır
	// bu fonksiyonun amacı shell->cmd deki komutları parse edip exec etmektir
	// öncelikle shell->cmd deki komutları parse etmek için parser fonksiyonunu çağırır
	// parser fonksiyonu shell->cmd deki komutları parse eder ve exec etmeye hazır hale getirir
	// parser fonksiyonu başarılı bir şekilde çalıştıysa exec fonksiyonunu çağırır
	// exec fonksiyonu shell->cmd deki komutları exec eder
	// bu fonksiyonun sonunda free_loop fonksiyonu çağırılır
	// free_loop fonksiyonu shell->cmd deki komutları free eder
	// free_loop fonksiyonu shell->cmd deki komutları free ettikten sonra shell->cmd deki komutları free eder
	int	flags[3];
	int	control;
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	control = cmd_check(shell->lex_list, NULL, NULL);
	// cmd_check fonksiyonu shell->lex_list deki komutları kontrol eder
	if (!control)
	{
		// eğer cmd_check fonksiyonu 0 döndürürse
		// print_error fonksiyonunu çağırır
		free_lexes(&(shell->lex_list));
		// free_lexes fonksiyonu shell->lex_list deki contentleri free eder
		free(shell->cmd);
		// shell->cmd deki komutları free eder
		return ;
	}
	if (ft_strcmp(shell->cmd, ""))
	{
		// eğer shell->cmd boş değilse
		if (parser(shell, flags))
			// parser fonksiyonu başarılı bir şekilde çalıştıysa
			exec(env, shell);
			// exec fonksiyonunu çağırır
	}
	free_loop(control, shell);
	// free_loop fonksiyonu shell->cmd deki komutları free eder
}

void	free_lexes(t_list **node)
{
	if (!*node)
		return ;
	if ((*node)->next != NULL)
		free_lexes(&(*node)->next);
	if ((*node)->content)
		(*node)->content = (free((*node)->content), NULL);
	if ((*node))
		(*node) = (free(*node), NULL);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)av;
	if (ac != 1)
		exit(write(2, "This program cannot accept any arguments\n", 41));
	initialize_shell(&shell);
	env_get(env, &shell);
	signals_control();
	while (1)
	{
		get_readline(shell);
		if (quote_check(shell->cmd))
		{
			lexer(shell->cmd, &shell->lex_list, &shell);
			expander(shell);
			parse_exec(shell, env);
		}
		else
		{
			free(shell->cmd);
			continue ;
		}
	}
	return (0);
}
