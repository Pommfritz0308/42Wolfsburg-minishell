/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errnu.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:33:54 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:33:55 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRNU_H
# define ERRNU_H
# define SY_PIPE		107
# define SY_PIPE_T		"syntax error near unexpected token `|'"
# define SYNTAX			108
# define SYNTAX_T		"syntax error near unexpected token `&'"
# define COND_ERR		109
# define COND_ERR_T		"wrong condition usage"
# define N_FOUND		110
# define N_FOUND_T		"command not found"
# define IS_DIR			111
# define IS_DIR_T		"is a directory"
# define IDENT			112
# define IDENT_T		"\': not a valid identifier"
# define HIGH_SHLVL		113
# define HIGH_SHLVL_T	"warning: shell level too high, resetting to 1"
#endif
