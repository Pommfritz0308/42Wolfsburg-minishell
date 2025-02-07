/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:58:03 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/27 13:04:58 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd_helper(t_env *env, char *arg, char *pwd)
{
	arg = retr_env_value(env, "OLDPWD");
	if (!arg)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (EXIT_FAILURE);
	}
	if (!chdir_(arg))
	{
		printf("%s\n", arg);
		go_back(env, arg, pwd);
	}
	free(arg);
	return (EXIT_SUCCESS);
}

int	ft_export_cd(t_env *env, char *str, char *update)
{
	int		i;

	i = -1;
	env->flag = 0;
	while (env->env[++i])
	{
		if (!ft_strncmp(env->env[i],
				str, ft_find_pos(env->env[i], '=')))
		{
			env->flag = 1;
			break ;
		}
	}
	ch_env(env, i, update);
	return (EXIT_SUCCESS);
}

int	to_home(t_env *env, char *arg)
{
	char	*home;
	char	*update;

	home = retr_env_value(env, "HOME=");
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (EXIT_FAILURE);
	}
	if (!home[0])
		return (EXIT_SUCCESS);
	if (chdir_(home))
	{
		free(home);
		return (EXIT_FAILURE);
	}
	update = ft_strjoin("OLDPWD=", arg);
	ft_export_cd(env, "OLDPWD", update);
	free(update);
	update = ft_strjoin("PWD=", home);
	ft_export_cd(env, "PWD", update);
	free(home);
	free(update);
	return (EXIT_SUCCESS);
}
