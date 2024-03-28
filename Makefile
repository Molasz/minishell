# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 16:38:42 by akozin            #+#    #+#              #
#    Updated: 2024/03/28 12:15:35 by molasz-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/
LIBFT_A = $(addprefix $(LIBFT), libft.a)

RL = readline/
RL_A = $(addprefix $(RL), libreadline.a)
RLHIST_A = $(addprefix $(RL), libhistory.a)
RL_URL = http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz
RL_FILE = readline-master.tar.gz

NAME = minishell

MAKE = make

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEFS = -DREADLINE_LIBRARY

SRCNAMES = main.c \
			shell_loop.c \
			expand_vars.c \
			tokenize.c \
			tokenize_utils.c \
			token_error_probe.c \
			token_error_probe_utils.c \
			redir_exec.c \
			enviroment/create_env.c \
			enviroment/export.c \
			enviroment/unset.c \
			enviroment/env_utils.c \

SRCS = $(SRCNAMES)
OBJS = $(addprefix obj/, $(SRCS:.c=.o))
DEPS = $(addprefix obj/, $(SRCS:.c=.d))

RM = rm -rf

all:		folders make_libs $(NAME)

folders:
	mkdir -p obj
	mkdir -p obj/enviroment


make_libs: $(RL)
	if [ ! -f $(RL)config.status ] ; then \
		cd $(RL) && ./configure ; \
	fi
	$(MAKE) -C $(RL)
	$(MAKE) -C $(LIBFT)

$(RL):
	curl $(RL_URL) > $(RL_FILE)
	tar -xf $(RL_FILE) && mv readline-master/ $(RL)
	rm -rf $(RL_FILE)

$(NAME):	$(OBJS) $(LIBFT_A) $(RL_A) $(RLHIST_A)
	$(CC) $(CFLAGS) $(DEFS) $(OBJS) $(LIBFT_A) $(RL_A) $(RLHIST_A) -L$(RL) -lreadline -ltermcap -o $(NAME)

obj/%.o:	src/%.c Makefile
	$(CC) $(CFLAGS) $(DEFS) -c $< -MMD -o $@

-include $(DEPS)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(RL)
	$(RM) obj

fclean:	
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) clean -C $(RL)
	$(RM) obj $(NAME)

re:			fclean all

.PHONY: all clean fclean re
