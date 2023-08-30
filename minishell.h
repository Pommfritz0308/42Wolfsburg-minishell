/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:59 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 09:36:47 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct		s_cmd
{
	char			*cmd;
	char			**args;
	int				*in_fds;
	int				*out_fds;
	struct s_cmd	*next_cmd;
	int				next_cmd_cnd;
}					t_cmd;

#endif