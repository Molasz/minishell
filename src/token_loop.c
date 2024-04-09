/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/09 16:11:34 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	cmd_count(t_token *token)
{
	int	count;
	int	j;

	count = 1;
	j = 0;
	while (token[j].token && ft_strncmp(token[j].token, "||", 3)
			&& ft_strncmp(token[j].token, "&&", 3))
	{
		if (!ft_strncmp(token[j].token, "|", 2))
			count++;
		j++;
	}
	return (count);
}

static int	cmd_len(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].token && ft_strncmp(token[i].token, "|", 2))
		i++;
	return (i);
}

static int	cmd_loop(t_data *data, t_token *token, int *count)
{
	int	cmd_l;
	int	j;
	int	k;
	int	l;

	cmd_l = cmd_count(token);
	data->coms = malloc((cmd_l + 1) * sizeof (t_com));
	if (!data->coms)
		return (1);
	j = -1;
	while (++j < cmd_l)
	{
		k = cmd_len(data->tokens + *count);
		data->coms[j].com = malloc((k + 1) * sizeof (char *));
		if (!data->coms[j].com)
			return (free_coms(data), 1);
		data->coms[j].com[k] = NULL;
		l = -1;
		while (++l < k)
			data->coms[j].com[l] = data->tokens[*count + l].token;
		*count += l;
		if (j + 1 < cmd_l)
			*count += 1;
	}
	return (0);
}

int	token_loop(t_data *data)
{
	int	cmd_c;
	int	i;
	int	count;

	cmd_c = 1;
	while (data->tokens[cmd_c].token && (!ft_strncmp(data->tokens[cmd_c].token, "||", 3)
			|| !ft_strncmp(data->tokens[cmd_c].token, "&&", 3)))
		cmd_c++;
	i = 0;
	count = 0;
	while (i < cmd_c)
	{
		cmd_loop(data, data->tokens + count, &count);
		run_cmds(data);
		i++;
	}
	return (0);
}
