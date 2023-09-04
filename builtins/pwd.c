#include "../minishell.h"
#include "../errnu.h"

int	pwd_(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_perror("pwd");
		return (EXIT_FAILURE);
	}
	else
		printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	main(void)
{
	pwd_();
}