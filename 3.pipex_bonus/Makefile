# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 08:14:10 by mhrima            #+#    #+#              #
#    Updated: 2022/12/23 03:25:32 by mhrima           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = pipex.c libft/libft.a 
NAME = pipex



all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(SRC) -o $(NAME) 
#-fsanitize=address -g3

bonus: $(NAME)
	$(CC) $(SRC) -o $(NAME) 


clean : 
	$(RM) $(NAME)
	
fclean : clean
	$(RM) $(NAME)

re : fclean all