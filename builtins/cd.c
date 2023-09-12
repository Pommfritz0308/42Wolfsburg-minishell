#include "../minishell.h"
#include "../errnu.h"

int	ft_cd(t_env *env, char *arg)
{
	if (!ft_strncmp(arg, "-", ft_strlen("-")))
	{
		arg = retr_oldpwd(env);
	}
	if (!arg | !arg[0])
		return (EXIT_SUCCESS);
	if (chdir(arg))
	{
		ft_perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*retr_oldpwd(t_env *env)
{
	int		end;
	int		i;
	char	*oldpwd;
	char	*eq_sign;

	i = 0;
	while (env->env[i])
	{
		if (!ft_strncmp(env->env[i], "OLDPWD", ft_strlen("OLDPWD")))
		{
			eq_sign = ft_strchr(env->env[i], '=');
			if (eq_sign)
				oldpwd = ft_substr(env->env[i], 0, eq_sign - env->env[i]);
			return (oldpwd);
		}
		i++;
	}
	return (NULL);
}

