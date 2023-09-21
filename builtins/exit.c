#include "../includes/minishell.h"

int	ft_exit(t_env *env, char **args)
{
	int	i;

	i = -1;
	if (!args || !args[0])
		return (env->curr_exit_code);
	if (ft_count_rows(args) > 2)
	{
		while (!args[1][++i])
		{
			if (!ft_isdigit(args[1][++i]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				return (255);
			}
		}
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (ft_atoi(args[1] > 256))
	{

	}
	return (env->curr_exit_code);
}

int	calc_exit_code(char *numb)
{
	long long int	result;
	int				sign;
	int				i;

	i = 0;
	sign = 1;
	result = 0;
	while (numb[i] == ' ' || numb[i] == '\t')
		i++;
	if (numb[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (numb[i] == '+')
		i++;
	while (numb[i] >= '0' && numb[i] <= '9')
	{
		if (check_range)
		{}
		result = result * 10 + (numb[i] - '0');
		i++;
	}
	return (result * sign);
}

bool	check_range(long long int result, int sign, char *str, int i)
{
	if (result > LLONG_MAX / 10 || (result == LLONG_MAX
			/ 10 && (str[i] - '0') > LLONG_MAX % 10))
		return (false);
	return (true);
}
