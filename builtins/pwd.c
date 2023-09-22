/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:58:07 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/22 17:58:08 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_perror("pwd", 0, 0);
		return (EXIT_FAILURE);
	}
	else
		printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
