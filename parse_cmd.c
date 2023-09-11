/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:52 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/11 18:54:47 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *flags, char curr)
{
	static char	flag;
	int			res;

	res = 0;
	if (flag)
		res = 1;
	while (*flags)
	{
		if (*flags == curr)
		{
			if (flag == curr)
				flag = 0;
			else if (!flag)
				flag = curr;
		}
		flags++;
	}
	return (res);
}

char	*next_word(char *s, int *i)
{
	int		len;
	char	*res;

	while (s && *s && (*s == ' ' || *s == '\t'))
	{
		s++;
		(*i)++;
	}
	len = 0;
	while (s && s[len] && s[len] != ' ' && s[len] != '\t'
		&& s[len] != '\n' && s[len] != '>' && s[len] != '<')
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = 0;
	(*i) += len;
	ft_strlcpy(res, s, len + 1);
	return (res);
}

void	parse_out(char *s, int *i, t_cmd *res)
{
	t_rdrct	*node;
	int		start;
	int		end;

	if (!res->out_rdrcts)
	{
		res->out_rdrcts = new_rdrct_node();
		if (!res->out_rdrcts)
			return ;
	}
	node = res->out_rdrcts;
	node->open_flags = O_WRONLY | O_CREAT;
	while (node->next)
		node = node->next;
	start = *i;
	end = *i;
	if (start - 1 > 0 && s[start - 1] == '&')
	{
		node->stderr_to_1 = 1;
		start--;
	}
	while (start && --start && ft_isdigit(s[start]))
		;
	if (!ft_isdigit(s[start]))
		start++;
	if (start != *i)
		node->in_fd = ft_atoi(s + start);
	else
		node->in_fd = 1;
	if (s[++end] == '>')
	{
		node->open_flags |= O_APPEND;
		end++;
		(*i)++;
	}
	if (s[end] == '|')
	{
		end++;
		(*i)++;
	}
	if (s[end] == '&' && !ft_isdigit(s[end + 1]))
	{
		if (node->stderr_to_1)
		{
			errno = SYNTAX;
			ft_perror("minishell");
			return ;
		}
		node->stderr_to_1 = 1;
		(*i)++;
	}
	else if (s[end] == '&')
	{
		node->out_fd = ft_atoi(s + ++end);
		print_t_rdrct(node);
		(*i)++;
		while (ft_isdigit(s[*i]))
			(*i)++;
		return ;
	}
	node->word = next_word(s + end, i);
	print_t_rdrct(node);
}

t_cmd	*parse_cmd(char *s)
{
	int		i;
	t_cmd	*res;

	res = new_cmd_node();
	if (!res)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '>' && !check_flag("\'\"", s[i]))
		{
			parse_out(s, &i, res);
		}
		else if (s[i] == '<' && !check_flag("\'\"", s[i]))
		{

		}
	}
	return (res);
}
