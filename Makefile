# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 19:20:31 by eunskim           #+#    #+#              #
#    Updated: 2023/04/05 21:56:43 by eunskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

#//= Mandatory part =//#
NAME 	:= pipex
CFLAGS 	:= -fsanitize=address -g3 -Wextra -Wall -Werror

LIBFT	:= lib/libft
LIBGNL	:= lib/get_next_line
LIB		:= $(LIBFT)/libft.a
GNL		:= $(LIBGNL)/get_next_line.a

INC_DIR	:= inc
HEADERS	:= -I $(LIBFT) -I $(LIBGNL) -I $(INC_DIR)

SRC_DIR	:= src
SRCS	:= $(addprefix $(SRC_DIR)/, \
			pipex.c \
			pipex_utils.c \
			pipex_error.c)
OBJS	:= $(SRCS:.c=.o)

#//= Make Rules =//#
all: libft libgnl $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

libgnl:
	@$(MAKE) -C $(LIBGNL)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBC) $(GNL) -o $(NAME) && \
	echo "$(YELLOW)$(BOLD)>> Mandatory part - pipex$(RESET)" && \
	echo "$(BLUE)$(BOLD)Compilation successful!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBGNL) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBC)
	@rm -f $(GNL)

re: fclean all

.PHONY: all, clean, fclean, re, libft, libgnl
