# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 19:35:16 by alida-si          #+#    #+#              #
#    Updated: 2022/04/19 22:31:27 by alida-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRC	=	ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_calloc.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strdup.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_itoa.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putnbr_fd.c \
		ft_split.c \
		conversions.c \
		ft_printf.c \
		itohex.c \
		utoa.c \
		ft_printf_utils.c \
		get_next_line.c \
		ft_strrncmp.c \
		ft_strcat.c \
		ft_split2.c \

OBJ	= $(SRC:.c=.o)

BONUS	=	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

BONUS_OBJ	= $(BONUS:.c=.o)

CC	= gcc
FLAG	= -Wall -Wextra -Werror
AR	= ar -rcs
RM	= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)

bonus: $(BONUS_OBJ)
	$(AR) $(NAME) $(BONUS_OBJ)

$(BONUS_OBJ): $(BONUS)
	$(CC) $(FLAGS) -c $(BONUS)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
