/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:11 by akozin            #+#    #+#             */
/*   Updated: 2024/04/18 16:59:18 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dollar_exp_helper(t_token *exp_t, t_data *data, t_token *c_toks, int i)
{
	int	r;

	c_toks[i].type = determine_type(c_toks[i].token);
	if (i > 0)
		r = dollar_expander(exp_t, data, c_toks[i].token, c_toks[i - 1].type);
	else
		r = dollar_expander(exp_t, data, c_toks[i].token, TOKEN);
	return (r);
}

int	unlit_spaces_probe(t_token *f_me)
{
	int	i;

	i = 0;
	while (f_me->token[i])
	{
		if (ft_strchr(" \t\f\v", f_me->token[i]) && !f_me->literal[i])
			return (printf("ambiguous redirect\n"), 1);
		i++;
	}
	return (0);
}

t_tok_s	nt_prev(t_token *new_tokens)
{
	int		i;
	t_tok_s	ret;

	if (!new_tokens)
		return (TOKEN);
	else
	{
		i = 0;
		ret = TOKEN;
		while (new_tokens[i].token)
		{
			ret = new_tokens[i].type;
			i++;
		}
	}
	return (ret);
}
