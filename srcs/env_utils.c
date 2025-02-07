/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:11 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:29:12 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_cpy(t_env *data, char **envp)
{
	int			i;

	i = -1;
	data->env_size = 0;
	while (envp && envp[data->env_size])
		data->env_size++;
	data->env = ft_calloc(data->env_size + 1, sizeof(char *));
	if (!data->env)
		return (EXIT_FAILURE);
	while (++i < data->env_size)
		data->env[i] = ft_strdup(envp[i]);
	return (EXIT_SUCCESS);
}

char	**realloc_env(t_env *data, int size)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = ft_calloc(size + 1, sizeof(char *));
	while (data->env[++i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
	}
	free(data->env);
	return (new_env);
}

int	check_shlvl(int i)
{
	if (i < 0)
		return (0);
	else if (i > 1000)
	{
		ft_perror(0, HIGH_SHLVL, 0);
		return (1);
	}
	return (i);
}

int	update_shlvl(t_env *env)
{
	char	*shlvl;
	char	*temp;
	int		i;

	i = 1;
	shlvl = NULL;
	temp = NULL;
	shlvl = retr_env_value(env, "SHLVL=");
	if (!shlvl)
		ft_export_cd(env, "SHLVL", "SHLVL=1");
	else
	{
		i += ft_atoi(shlvl);
		free(shlvl);
		i = check_shlvl(i);
		shlvl = ft_itoa(i);
		temp = ft_strjoin("SHLVL=", shlvl);
		ft_export_cd(env, "SHLVL", temp);
		free(shlvl);
		free(temp);
	}
	return (EXIT_SUCCESS);
}
