/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:00:32 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/29 16:00:45 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *prompt)
{
	if (!ft_strncmp(prompt, "exit", 4))
		return (0);
	return (1);
}

int	main(void)
{
	char *prompt;

	while (1)
	{
		prompt = readline("minishell$ ");
		if (!parse(prompt))
			break ;
	}
}
