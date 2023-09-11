/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:59 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/11 18:54:41 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <term.h>
# include <stdlib.h>
# include <unistd.h>
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
	REDIR_OUT,
	REDIR_IN,
	REDIR_CLOSE,
	REDIR_HEREDOC,
	PARANTH_OPEN,
	PARANTH_CLOSE,
	PIPE,
	AND,
	OR,
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
typedef struct s_rdr_l
{
	t_tocken		*token;
	char			*word;
	struct s_rdr_l	*next;
}					t_rdr_l;
typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_tocken		*tocken;
	t_list			*args;
	t_rdr_l			*redirections;
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
	char			**args;
	char			*cmd;
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
void	ft_env(char **envp);
int		env_cpy(t_builtins *data, char **envp);
int		ft_export(t_builtins *data, char *arg);
char	**realloc_env(t_builtins *data, int size);
void	ch_env(t_builtins *data, int i, char *arg);
t_tree	*ast(char *s);
int		execute(t_tree *tree, char **env);
char	*path_to_exec(char *exec, char **env);
int		str_contains(char c, char *s);

// Debug
void	print_t_rdrct(t_rdrct *node);
void	print_t_cmd(t_cmd *cmd);
void	print_tree(t_tree *tree);
void	print_ast(char *s);
#endif
