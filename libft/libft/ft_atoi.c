/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:31:49 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 18:34:55 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int    ft_atoi(const char *str)
{
    int     i;
    int     sign;
    int     result;

    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
            || str[i] == '\r' || str[i] == ' ')
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}