/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:59 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 20:13:52 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct		s_rdrct
{
	int				fd;
	char			*word;
	int				open_flags;
	int				heredoc;
	char			*limiter;
	struct s_rdrct	*next;
}					t_rdrct;
typedef struct		s_cmd
{
	char			*cmd;
	char			**args;
	t_rdrct			*in_rdrcts;
	t_rdrct			*out_rdrcts;
	struct s_cmd	*next_cmd;
	int				next_cmd_cnd;
}					t_cmd;

typedef struct s_split2
{
	int		count;
	int		*matches;
	char	**arr;
	size_t	s1_len;
	size_t	s2_len;
	int		arr_len;
	int		arr_y;
}	t_split2;

char	*resolve_env(char *s);
void	parse(char *user_input, t_cmd **cmds);
t_cmd	*parse_cmd(char *s);
int		exec_cmds(t_cmd *cmds);
void	handle_signals();
t_cmd	*new_cmd_node();
#endif
