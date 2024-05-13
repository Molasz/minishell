/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirs_handler_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:41:03 by akozin            #+#    #+#             */
/*   Updated: 2024/05/13 13:41:25 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	fifo_closure(int *fio)
{
	if (fio[0] != -42)
		close(fio[0]);
	if (fio[1] != -42)
		close(fio[1]);
}

