/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:57:46 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/22 17:57:49 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
	}
	return (EXIT_SUCCESS);
}
