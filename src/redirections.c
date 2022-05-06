/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:26:56 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/06 09:27:06 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	redirect(int old_file, int new_file)
{
	if (dup2(old_file, new_file) < 0)
		return (1);
	close(old_file);
	close(new_file);
	return (0);
}
