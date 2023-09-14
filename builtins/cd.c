#include "../minishell.h"
#include "../errnu.h"

int	ft_cd(t_env *env, char *arg)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	// if (!arg)
	// {
	// 	to_home(env);
	// 	return (EXIT_FAILURE);
	// }
	else if (!ft_strncmp(arg, "-", ft_strlen("-")))
	{
		printf("OK\n");
		arg = retr_env_value(env, "OLDPWD");
		if (!arg)
		{
			free(pwd);
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (EXIT_FAILURE);
		}
		if (!chdir_(arg))
			go_back(env, arg, pwd);
		free(arg);
		return (EXIT_SUCCESS);
	}
	else if (chdir_(arg))
		return (EXIT_FAILURE);
	update_env(env, pwd);
	return (EXIT_SUCCESS);
}

int	update_env(t_env *env, char *arg)
{
	char	*update;
	char	*cwd;

	update = ft_strjoin("OLDPWD=", arg);
	ft_export_cd(env, "OLDPWD", arg);
	free(arg);
	free(update);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	update = ft_strjoin("PWD=", cwd);
	ft_export_cd(env, "PWD", cwd);
	free(cwd);
	free(update);
	return (EXIT_SUCCESS);
}

int	go_back(t_env *env, char *arg, char *cwd)
{
	char	*update;

	update = ft_strjoin("OLDPWD=", cwd);
	ft_export_cd(env, "OLDPWD", cwd);
	free(cwd);
	free(update);
	update = ft_strjoin("PWD=", arg);
	ft_export_cd(env, "PWD", arg);
	free(update);
	return (EXIT_SUCCESS);
}

int	chdir_(char *arg)
{
	if (chdir(arg))
	{
		ft_perror("cd");
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
				var = ft_substr(env->env[i], 0, eq_sign - env->env[i]);
			return (var);
		}
		i++;
	}
	return (NULL);
}

int ft_export_cd(t_env *env, char *str, char *update)
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

