# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 18:20:49 by alida-si          #+#    #+#              #
#    Updated: 2022/04/02 02:07:53 by alida-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex

LIBFT_DIR =	./libft
LIBFT =		./libft/libft.a

SRC_DIR =	./src
OBJ_DIR =	./obj

SRC_FILES =	pipex.c \
			check.c \
			utils.c

SRC =		$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ =		$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC =		gcc
CCFLAGS =	-Wall -Wextra -Werror
LIBFLAGS =	-L./libft -lft

RM =		rm -f
RM_DIR =	rm -rf

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			$(CC) $(CCFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				mkdir -p $(OBJ_DIR)
				$(CC) $(CCFLAGS) -c $< -o $@

$(LIBFT):
			make -C ./libft

clean:
			make clean -C $(LIBFT_DIR)
			$(RM_DIR) $(OBJ_DIR)

fclean:		clean
			make fclean -C $(LIBFT_DIR)
			$(RM) $(NAME)

re:			fclean all