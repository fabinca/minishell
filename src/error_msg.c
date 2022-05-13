/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:08:34 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/13 16:51:23 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str1, char *str2, char *str3, char *str4)
{
	char	*err_message;

	err_message = (char *)ft_calloc(100, sizeof(char));
	ft_strlcat(err_message, str1, 99);
	if (str2)
		ft_strlcat(err_message, str2, 99);
	if (str3)
		ft_strlcat(err_message, str3, 99);
	if (str4)
		ft_strlcat(err_message, str4, 99);
	write(2, err_message, ft_strlen(err_message));
	free(err_message);
}
