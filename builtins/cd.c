/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:58:31 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/25 14:25:25 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_env *env, char *arg)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_perror("minishell: cd", 0, 0);
		return (EXIT_FAILURE);
	}
	if (!arg)
	{
		to_home(env, pwd);
		return (free(pwd), EXIT_SUCCESS);
	}
	else if (!ft_strncmp(arg, "-", ft_strlen("-")))
	{
		if (ft_cd_helper(env, arg, pwd))
			return (free(pwd), EXIT_FAILURE);
		else
			return (free(pwd), EXIT_SUCCESS);
	}
	else if (chdir_(arg))
		return (free(pwd), EXIT_FAILURE);
	update_cwd(env, pwd);
	return (free(pwd), EXIT_SUCCESS);
}

int	update_cwd(t_env *env, char *arg)
{
	char	*update;
	char	*cwd;

	update = ft_strjoin("OLDPWD=", arg);
	ft_export_cd(env, "OLDPWD", update);
	free(update);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_perror("minishell: cd", 0, 0);
		return (EXIT_FAILURE);
	}
	update = ft_strjoin("PWD=", cwd);
	ft_export_cd(env, "PWD", update);
	return (free(cwd), free(update), EXIT_SUCCESS);
}

int	go_back(t_env *env, char *arg, char *cwd)
{
	char	*update;

	update = ft_strjoin("OLDPWD=", cwd);
	ft_export_cd(env, "OLDPWD", update);
	free(update);
	update = ft_strjoin("PWD=", arg);
	ft_export_cd(env, "PWD", update);
	return (free(update), EXIT_SUCCESS);
}

int	chdir_(char *arg)
{
	if (chdir(arg))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_perror(arg, 0, 0);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*retr_env_value(t_env *env, char *var)
{
	int		i;
	char	*eq_sign;

	i = 0;
	while (env->env[i])
	{
		if (!ft_strncmp(env->env[i], var, ft_strlen(var)))
		{
			eq_sign = ft_strchr(env->env[i], '=');
			if (eq_sign)
				var = ft_substr(eq_sign, 1, ft_strlen(env->env[i]));
			return (var);
		}
		i++;
	}
	return (NULL);
}
