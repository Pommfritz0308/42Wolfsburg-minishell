#include "../includes/minishell.h"

char	*ft_strerror(void)
{
	if (errno == SYNTAX)
		return (SYNTAX_T);
	else if (errno == SY_PIPE)
		return (SY_PIPE_T);
	else if (errno == COND_ERR)
		return (COND_ERR_T);
	else if (errno == N_FOUND)
		return (N_FOUND_T);
	else if (errno == IS_DIR)
		return (IS_DIR_T);
	else if (errno == IDENT)
		return (IDENT_T);
	else if (errno == HIGH_SHLVL)
		return (HIGH_SHLVL_T);
	else if (errno < 107)
		return (strerror(errno));
	else
		return ("undefined error");
}

int	ft_perror(char *msg, int err_code, int exit_code)
{
	char	*str;

	write(2, "minishell: ", 12);
	if (err_code)
		errno = err_code;
	if (errno >= 107)
	{
		str = ft_strerror();
		if (msg && *msg)
		{
			write(2, msg, ft_strlen(msg));
			write(2, ": ", 2);
		}
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	else
		perror(msg);
	return (exit_code);
}
