/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:15:19 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 20:06:23 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>

# define NOT_EXEC 126
# define CMD_N_FOUND 127
# define FATAL_SIGNAL 128
# define INCORRECT_USAGE 258

# define BOLD  "\033[1m"
# define GREEN  "\033[1;32m"
# define RED  "\033[1;31m"
# define CYAN  "\033[1;36m"
# define END " \033[0m"

typedef enum tokens{
	EMPTY,
	HEREDOC, 
	PIPE,
	IN_REDIREC, 
	APP, 
	OUT_REDIREC,
	OPTION,
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}t_tokens;

typedef struct s_list
{
	char			*content;
	int				outside_quote;
	int				any_quotes;
	int				expand;
	t_tokens		tokens;
	struct s_list	*next;
	struct s_list	*prev;
}t_list;
typedef struct s_cmd
{
	char			**cmd;
	struct s_list	*redirec;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	bool			equal;
}t_env;

typedef struct s_msh
{
	int		is_runing;
	int		fd_in;
	int		fd_out;
	int		standard_out;
	int		standard_in;
	int		exit_status;
	int		cmd_index;
	int		cmd_nbrs;
	int		here;
	t_env	*env;
	t_cmd	*t_cmd;
	pid_t	*pid;
}t_msh;

typedef struct fill_exp
{
	int	s_q;
	int	d_q;
	int	pat_i;
	int	i;
	int	j;
}t_fill_exp;

extern t_msh	g_msh;

int		check_quotes(char *read);
int		ft_strlen(char *s);
t_list	*split_operator(t_list *list);
void	lst_add_back(t_list *head, t_list *new);
t_list	*lst_new(void);
void	lst_add_front(t_list *list, t_list *new);
t_list	*lst_add_mid(t_list *list, t_list *head);
t_list	*check_empty_node(t_list *list);
char	**fill_pattern_content(char *content);
char	*ft_fill_content(t_list *list, char *read);
void	link_it(t_list *head, t_list *new);
char	**fill_pattern_value(char **pattern, char **env);
void	check_operator_fail(t_list *new, int oper, t_list *l_hd, t_list *hd);
void	ft_fill_pat_cont(char *content, char **patterns);
char	*expand_exit(int exit_status_nb, char *cmd, char *value, t_list *begin);
void	expand_exit_status(t_list *list);
int		howmany_words(char *s);
int		expand_delim(char c);
int		ft_iswhitespace(char c);
char	*ft_expanded_content(char **value, char **pattern, char *s);
t_list	*check_expanded_value(t_list *list);
char	*chars_inside_quotes(int *count, char *read, char c);
void	check_outside_quote(t_list *list);
void	cmd_fails(t_list *list, t_cmd *cmd);
void	check_head_fail(t_cmd *cmd, t_list *list);
void	fill_operator_content(char *content, char *s, int *i);
void	check_content_fails(t_list *list, t_list *list_head, t_list *new);
char	*no_expand(char *content, char *patt);
char	*insert_path_cont(char *cont, char *patterns);
int		chars_to_split(char *s);
t_list	*fill_new_nodes(t_list *list);
int		len_without_quotes(char *s);
int		check_operation(char *s, int i);
void	ft_free_list(t_list *list);
int		tokenize_list(t_list *list);
int		ft_strmatch(char *s0, char *s1);
void	print_list(t_list *list);
int		check_syntax(t_list *list);
t_list	*delete_quotes(t_list *head);
t_cmd	*build_command(t_list *list);
t_list	*delete_redirec_nodes(t_list *list);
void	check_for_quotes(char c, int *s_quotes, int *d_quotes);
char	*ft_strcp(char *src);
t_cmd	*fill_cmd(t_list *list, t_cmd *cmd_l);
void	expand(t_list *list, char **env);
void	ft_free_arr(char **arr);
void	print_cmd(t_cmd *head);
void	ft_echo(char **cmd, int fd);
void	ft_cd(char **cmd);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
void	ft_pwd(void);
void	ft_env_init(char **env);
t_env	*ft_lstnew_env(char *name, char *value, bool equal);
void	ft_lstadd_back(t_env **lst, t_env *new);
char	*ft_get_env(char *str);
void	print_env(int p);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	**ft_list_to_tab(t_env *head);
void	free_tab(char **tab);
void	ft_export(char **cmd);
void	ft_unset(char **cmd);
int		equal_index(char *str);
char	*ft_strdup(const char *s);
void	ft_lst_delete_node(t_env **head_ref, char *name_to_delete);
char	**ft_split(char const *s, char c);
void	exec_pipes(t_cmd *commands);
void	builtin_exec(t_cmd *t_cmd);
bool	is_builtin(t_cmd *t_cmd);
void	handle_herdoc(t_list *r_head);
t_list	*lexer(char *read);
void	ft_handle_redirections(t_list *r_head);
int		ft_isalnum(int c);
char	*expand_into_str(char *str);
int		has_dollar(char *str);
int		commands_nbr(t_cmd *cmd);
int		ft_isalpha(int c);
int		ft_isdigit(int d);
void	ft_putnbr_fd(int n, int fd);
int		ft_strncmp(char *s1, char *s2, int n);
void	edit_node(t_env **env, char *name, char *value, int inc);
void	ft_put_error(char *cmd, char *str);
int		check_cmd(char	**cmd);
char	*fix_cmd(t_cmd *cmd_ptr);
int		ft_execve(char *cmd, t_cmd *cmd_ptr, char **env);
void	run_child(t_cmd *cmd_ptr, int pipes_fd[2], int cmd_index, int p_r_e);
void	minishell(char **env, char *read);
void	handle_back_s(int signal);
void	handle_ctrl_c(int signal);
void	ft_free_cmd(t_cmd *cmd);
void	print_cmd(t_cmd *head);
int		ft_pipe(int pipes_fd[2], int cmd_index, int cmd_nbrs);
void	handle(int signal);
void	handle_s(int sig);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	child_sig(void);
void	parent_sig(void);
int		has_name(char *name);
int		update_exit_status(int status);
void	exit_cmd(char *cmd);
void	exit_dir(char *cmd);
void	reset_std(void);
void	exit_with(int e);
void	ft_free_sub(char *sub, char *sub2, char *env);
#endif