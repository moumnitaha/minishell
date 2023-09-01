# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 18:03:42 by eyassine          #+#    #+#              #
#    Updated: 2023/08/31 18:30:20 by eyassine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
GREEN = \033[1;32m
RED=\033[1;31m
CYAN = \033[1;36m
END = \033[0m

NAME = minishell
HEADER = msh.h

L = -L/goinfre/tmoumni/.brew/opt/readline/lib
I = -I/goinfre/tmoumni/.brew/opt/readline/include

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = m.c check_quotes.c split_operator.c lst_new.c lexer.c lst_add_back.c ft_strlen.c ft_free_list.c \
		tokenize_list.c print_list.c check_syntax.c delete_quotes.c build_command.c delete_redirec_nodes.c \
		ft_strcp.c fill_cmd.c expand.c check_expanded_value.c expand_exit_status.c delete_empty_node.c expanded_content.c fill_content.c fill_new_node.c\
		fill_pattern_content.c fill_pattern_value.c howmany_words.c len_without_quote.c\
		lst_add_front.c lst_add_mid.c ft_free_arr.c builtins/ft_echo.c builtins/ft_substr.c\
		builtins/ft_cd.c builtins/ft_strjoin.c builtins/ft_pwd.c builtins/ft_env.c builtins/ft_lstnew.c\
		builtins/ft_lstadd_back.c builtins/ft_get_env.c builtins/ft_putstr_fd.c builtins/ft_putchar_fd.c\
		builtins/ft_list_to_tab.c builtins/ft_free_mem.c builtins/ft_export.c builtins/ft_strdup.c\
		builtins/ft_unset.c builtins/ft_lstdelone.c builtins/ft_split.c exec.c ft_isalnum.c\
		ft_redirections.c builtins/ft_putnbr_fd.c builtins/ft_strncmp.c builtins/ft_export_help.c\
		builtins/ft_heredoc.c builtins/ft_put_error.c exec_help.c builtins/ft_builtin.c minishell.c\
		builtins/ft_itoa.c builtins/ft_atoi.c ft_exit_status.c 
OBJ_DIR = obj
BUILTINS_OBJ_DIR = $(OBJ_DIR)/builtins

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(SRCS) $(HEADER)
	@$(CC) $(FLAGS) $(OBJS) -lreadline  -o $@ $(L)
	@echo "\n$(GREEN)[[ minishell created successfully! ]]$(END)\n"

$(OBJ_DIR)/%.o: %.c msh.h
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@ $(I)
	@echo "$(CYAN)Compiling:$(END)" $< "..."

clean:
	$(RM) $(OBJ_DIR)
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all