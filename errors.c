#include "minishell.h"

char	*ft_strerror(void)
{
	if (errno == SYNTAX)
		return (SYNTAX_T);
	else if (errno == PIPE_ERR)
		return (PIPE_ERR_T);
	else if (errno == COND_ERR)
		return (COND_ERR_T);
	else if (errno < 107)
		return (strerror(errno));
	else
		return ("undefined error");
}

void	ft_perror(char *msg, int code)
{
	char	*str;

	if (!msg)
		msg = "minishell";
	if (code)
		errno = code;
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
}
