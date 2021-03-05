/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:36:33 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/06 00:23:52 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>

# define SUCCEEDED 0
# define FAILED 1
# define IS_DIR 126
# define PERMISSION_DENIED 126
# define SYNTAX_ERROR 258
# define COMMAND_NOT_FOUND 127
# define CTRL_C 130
# define CTRL_BKSLSH 131
# define ERROR_SIGINT 0xA
# define ERROR_SIGQUIT 0xB
# define SYNT_ERR_STR "syntax error near unexpected token"

typedef struct	s_envcopy
{
	char				*key;
	char				*value;
	int					sep;
	int					unset;
	struct s_envcopy	*next;
}				t_envcopy;

typedef struct	s_param
{
	char		**line;
	char		*tilda;
	t_envcopy	*env_new;
	t_envcopy	*env_copy;
	int			echo_n;
	char		**env_array;
	int			pipe_flag;
	int			fd_0;
	int			fd_1;
	int			fd[2];
	int			fd_redir;
	int			is_redirect;
	int			redirect_size;
	int			pipe_size;
	t_envcopy	*ptr;
	t_envcopy	*prev;
	bool		flag;
	int			is_quote;
}				t_param;

typedef struct	s_exit
{
	int			mini;
	int			exit;
	int			is_signal;
}				t_exit;

t_exit			g_exit;

void			free_split(char **split);
char			*ft_strjoin_three(char const *s1,
					char const *s2, char const *s3);
void			error(char *command, char *param, char *error);
int				size_arg(t_param *all);
int				is_num_char(char *str);
char			*get_exit_status(t_param *all);
void			wait_pipe(t_param *all);
void			shlvl_up(t_param *all);
int				check_line(char *str);
int				pid_init(pid_t *pid);

void			signal_init(void);
void			sig_catcher_exec(int num);
void			exit_ctrd(void);
void			display_msg(void);
void			pwd_clear(t_param *all);

void			redirect(t_param *all);
void			sort_list(t_param *all);
void			free_array(t_param *all);

void			exec_run(t_param *all);
int				echo_run(t_param *all);
int				pwd_run(t_param *all);
int				cd_run(t_param *all);
void			exit_run(t_param *all);
int				env_run(t_param *all);
int				export_run(t_param *all);
int				unset_run(t_param *all);

void			ft_lst_copy(t_param *all);
int				env_size(t_envcopy *lst);
void			env_join(t_param *all, char *str, char *new_str, int unset);
char			*env_search(char *str, t_param *all);
char			*env_search_all(char *str, t_param *all);
void			env_to_array(t_param *all);
t_envcopy		*env_copy(char **envp, t_param *all);
void			env_update(t_param *all, char *str, char *new_str, int unset);
void			env_clear(t_envcopy **lst, void (*del)(void*));
void			env_add_back(t_envcopy **head, t_envcopy *new);
t_envcopy		*env_new(char *key, char *value, int sep);
t_envcopy		*env_new_copy(char *key, char *value, int sep, int unset);
void			swap_envcopy(t_envcopy **ptr, t_envcopy **b);
void			free_env(t_envcopy **head);

void			pipe_run(t_param *all);

void			exec_absolut_path(t_param *all);
void			exec_env_path(t_param *all);

int				parsing(t_param *all, char *line, int i);
void			ft_free_all_line(t_param *all);

int				is_correct_syntax(t_param *all, char *line);
int				ft_error(char *message, t_param *all, int err, char *param);
void			ft_line_add_back(char ***line, char **last);
void			ft_str_add_back(char **str, char last);
int				parsing_quotes(char *line, char **arg, int i, t_param *all);
int				parsing_env_variable(t_param *all,
					char *line, char **arg, int i);
int				parsing_dub_quotes(t_param *all, char *line, char **arg, int i);
int				parsing_redirections(t_param *all, char *line,
				int i, char **arg);
int				adding_next_arg(t_param *all, char *line, int i, char **arg);
int				redirect_file(t_param *all, char **arg, int i, char *line);

void			processor(t_param *all);

#endif
