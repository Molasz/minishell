/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:23:31 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/30 15:13:02 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*read_env(t_data *data, char *key, int envi)
{
	int		i;

	i = 0;
	while (data->env[envi][i].key)
	{
		if (!ft_strncmp(key, data->env[envi][i].key, ft_strlen(key)))
			break ;
		i++;
	}
	if (data->env[envi][i].key)
		return (data->env[envi][i].value);
	return (NULL);
}

void	benv(t_data *data, int envi)
{
	int	i;

	i = 0;
	while (data->env[envi][i].value)
	{
		if (data->env[envi][i].exp)
			printf("%s=%s\n", data->env[envi][i].key,
				data->env[envi][i].value);
		i++;
	}
}

char	**format_env(t_env *env)
{
	char	**new_env;
	int		len;
	int		i;

	len = 0;
	while (env[len].value)
		len++;
	new_env = malloc((len + 1) * sizeof (char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i].value)
		new_env[i] = env[i].value;
	new_env[i] = NULL;
	return (new_env);
}
