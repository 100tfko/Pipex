/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:20:21 by lcuevas-          #+#    #+#             */
/*   Updated: 2023/10/02 15:07:32 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = 0;
	while (*s != 0)
	{
		if (*s == (unsigned char)c)
			ptr = ((char *)s);
		s += 1;
	}
	if ((unsigned char)c == 0)
		return ((char *)s);
	return (ptr);
}

/*
busca c en y devuelve puntero pero desde el final hacia alante

#include <stdio.h>

int	main(void)
{
    char	*str;
    char	c;
    char	*ptr;
    
    str = "string";
    c = 0;
    ptr = ft_strrchr(str, c);
    printf("%s\n", str);
    printf("%s\n", ptr);
    
    return (0);
}
*/
