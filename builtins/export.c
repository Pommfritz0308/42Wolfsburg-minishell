#include "../minishell.h"
#include "../errnu.h"

int	ft_export(t_builtins *data, char *arg)
{
	char	**temp;
	int		ret;
	int		i;

	i = -1;
	temp = new_env(data, arg);
	if (!check_identifier(temp[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(temp[0], 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		ret = EXIT_FAILURE;
	}
	else
	{
		while (data->env[++i])
		{
			if ()
		}
	}
	return (ret);
}

char	**new_env(t_builtins *data, char *arg)
{
	char	**new_env;
	char	*eq_sign;
	int		i;

	eq_sign = ft_strchr(arg, '=');
	new_env = calloc(3, sizeof(char *));
	new_env[0] = ft_substr(arg, 0, eq_sign - arg);
	new_env[1] = ft_substr(eq_sign, 1, ft_strlen(eq_sign));
	new_env[2] = NULL;
	return (new_env);
}

bool	check_identifier(char *arg)
{
	int	i;

	i = -1;
	if (!arg[0] | !arg)
		return (false);
	while (arg[++i])
	{
		if (arg[i] == '_' | !ft_isalpha(arg[i]))
			return (false);
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	print_env(envp);
}