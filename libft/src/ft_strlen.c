/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:36:42 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/25 12:56:43 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_c(char *str, char end)
{
	size_t	len;

	len = 0;
	while (str[len + 1] != 0 && str[len] != end)
		len++;
	return (len);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != 0)
		len++;
	return (len);
}
