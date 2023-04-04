NAME = libft.a

SOURCE = ft_atoi.c \
ft_calloc.c \
ft_isalpha.c \
ft_isdigit.c \
ft_memchr.c \
ft_memcpy.c \
ft_memset.c \
ft_strdup.c \
ft_strlcpy.c \
ft_strncmp.c \
ft_strrchr.c \
ft_toupper.c \
ft_bzero.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_memcmp.c \
ft_memmove.c \
ft_strchr.c \
ft_strlcat.c \
ft_strlen.c \
ft_strnstr.c \
ft_tolower.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c

PRINTF_DIR = ft_printf

SOURCE_PRINTF = $(addprefix $(PRINTF_DIR)/, \
ft_printf.c \
parser.c \
print_conversions.c \
print_c.c \
print_di.c \
print_p.c \
print_s.c \
print_u.c \
print_x.c \
nbr_printer.c \
char_printer.c \
prc_wdt_helper.c \
sign_prefix_helper.c)

SOURCE_BONUS = ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c

OBJECT = $(SOURCE:.c=.o)
OBJECT_PRINTF = $(SOURCE_PRINTF:.c=.o)
OBJECT_BONUS = $(SOURCE_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECT) $(OBJECT_PRINTF)
	@ar rcs $(NAME) $?

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECT) $(OBJECT_BONUS) $(OBJECT_PRINTF)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJECT_BONUS)
	@ar -rcs $(NAME) $?

$(OBJECT_BONUS) : $(SOURCE_BONUS)
	@$(CC) -c $(CFLAGS) $?
