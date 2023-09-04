#include "../minishell.h"
#include "../errnu.h"

bool	env_cpy(char **envp)
{
	t_builtins	data;

	data.env_size = 0;
	while (envp && envp[data.env_size])
		data.env_size++;
	data.env = ft_calloc(data.env_size + 1, sizeof(char *));
	if (!data.env)
		return (false);
	
}