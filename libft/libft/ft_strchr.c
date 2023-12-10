/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:13:41 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/10 03:00:43 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	counter;

	counter = 0;
	while (s[counter])
	{
		if (s[counter] == c)
			return ((char *)s + counter);
		counter++;
	}
	if (s[counter] == c)
		return ((char *)s + counter);
	return (0);
}
