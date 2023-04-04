# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 19:04:53 by eunskim           #+#    #+#              #
#    Updated: 2023/01/24 20:31:03 by eunskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
SOURCE = get_next_line.c \
get_next_line_utils.c

SOURCE_BONUS = get_next_line_bonus.c \
get_next_line_utils_bonus.c

OBJECT = $(SOURCE:.c=.o)
OBJECT_BONUS = $(SOURCE_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=10000

all: $(NAME)

$(NAME): $(OBJECT)
	@ar rcs $(NAME) $?

$(OBJECT) : $(SOURCE)
	@$(CC) -c $(CFLAGS) $?

clean:
	@rm -f $(OBJECT) $(OBJECT_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJECT_BONUS)
	@ar -rcs $(NAME) $?

$(OBJECT_BONUS) : $(SOURCE_BONUS)
	@$(CC) -c $(CFLAGS) $?