/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:59 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/06 19:03:27 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <term.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "errnu.h"
# include <stdbool.h>

// Settings
# define SUCCESS_PROMPT	"\e[0;32mminishell\e[0m$ "
# define FAILED_PROMPT	"\e[0;31mminishell\e[0m$ "
# define MINISHELLRC	"/.minishellrc"

typedef enum e_token_type
{
	WORD,
	PARANTHESIS,
	AND,
	OR,
	PIPE,
	REDIRECTION,
	END
}					t_tocken_type;
typedef enum e_parser_state
{
	TOKEN_,
	SPACE_
}					t_parser_state;
typedef struct s_tocken
{
	t_tocken_type	type;
	char			*val;
}					t_tocken;
typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_tocken		*tocken;
}					t_tree;
typedef struct s_rdrct
{
	int				in_fd;
	int				out_fd;
	char			*word;
	int				open_flags;
	int				heredoc;
	int				stderr_to_1;
	char			*limiter;
	struct s_rdrct	*next;
}					t_rdrct;
typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_rdrct			*in_rdrcts;
	t_rdrct			*out_rdrcts;
	struct s_cmd	*next_cmd;
	int				next_cmd_cnd;
}					t_cmd;

typedef struct s_builtins
{
	char	**env;
	int		env_size;
	int		flag;
}	t_builtins;

char	*resolve_env(char *s);
void	parse(char *user_input, t_cmd **cmds);
t_cmd	*parse_cmd(char *s);
int		exec_cmds(t_cmd *cmds);
void	handle_signals(void);
t_cmd	*new_cmd_node(void);
t_rdrct	*new_rdrct_node(void);
int		ft_new_putchar(int c);
void	init_settings(void);
void	ft_perror(char *msg);
t_tree	*tokenize(char *s);

// Debug
void	print_t_rdrct(t_rdrct *node);
void	print_t_cmd(t_cmd *cmd);
#endif
