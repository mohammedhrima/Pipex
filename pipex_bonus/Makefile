# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 08:14:10 by mhrima            #+#    #+#              #
#    Updated: 2022/12/22 14:03:01 by mhrima           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = 002.c libft/libft.a 
NAME = pip



all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(SRC) -o $(NAME) 
#-fsanitize=address -g3

#bonus: $(OBJS_BONUS) $(OBJS)
#	$(AR) $(NAME) $(OBJS_BONUS) $(OBJS)


clean : 
	$(RM) $(NAME)
	
fclean : clean
	$(RM) $(NAME)

re : fclean all