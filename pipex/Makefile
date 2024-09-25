# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 13:06:03 by lcuevas-          #+#    #+#              #
#    Updated: 2024/03/06 20:44:10 by lcuevas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

PIPEX = obj/pipex.a

PIPEX_BONUS = obj_bonus/pipex_bonus.a

LIBFT_PATH = libs/libft
LIBFT = $(LIBFT_PATH)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS =	src/pipex.c\
		src/utils.c\

SRCS_BONUS =	src_bonus/pipex_bonus.c\
				src_bonus/utils_bonus.c\

OBJS = $(SRCS:src/%.c=obj/%.o)

OBJS_BONUS = $(SRCS_BONUS:src_bonus/%.c=obj_bonus/%.o)

all : $(LIBFT) $(NAME)

# .SILENT: pa silenciar echos rollo "all $(LIBFT_LIB_PATH) $(NAME) $(NAME_BONUS) $(OBJ) etc..
bonus : $(LIBFT) $(NAME_BONUS)

$(NAME):	$(OBJS) $(LIBFT)
				ar -rcs $(PIPEX) $(OBJS)
				$(CC) $(CFLAGS) $(PIPEX) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME_BONUS):	$(OBJS_BONUS) $(LIBFT)
					ar -rcs $(PIPEX_BONUS) $(OBJS_BONUS)
					$(CC) $(CFLAGS) $(PIPEX_BONUS) $(LIBFT) -o $(NAME_BONUS)

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(FLAGS) -c $< -o $@

obj_bonus/%.o: src_bonus/%.c
	mkdir -p obj_bonus
	$(CC) $(FLAGS) -c $< -o $@ 

clean:
	$(RM) obj obj_bonus
	make -C $(LIBFT_PATH) clean

fclean:
	$(RM) obj obj_bonus $(NAME) $(NAME_BONUS)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all bonus clean fclean re
