/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:13:53 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/27 12:32:33 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_dots(char *wild, char *file)
{
	if (wild[0] == '.')
		return (true);
	if (file[0] == '.')
		return (false);
	return (true);
}

bool	no_pattern(char *wild)
{
	size_t	i;

	i = 0;
	while (wild[i] == '*')
		i++;
	if (i == ft_strlen(wild))
		return (true);
	else
		return (false);
}

bool	pattern_at_end(char *dir, char	*wild)
{
	if (rev_search_str(dir, wild))
		return (true);
	else
		return (false);
}
