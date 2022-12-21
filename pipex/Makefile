# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olahrizi <olahrizi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 08:14:10 by mhrima            #+#    #+#              #
#    Updated: 2022/12/21 21:54:35 by olahrizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = pipex.c libft/libft.a
NAME = pipex 



all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(SRC) -o $(NAME) -fsanitize=address -g3

#bonus: $(OBJS_BONUS) $(OBJS)
#	$(AR) $(NAME) $(OBJS_BONUS) $(OBJS)


clean : 
	$(RM) $(NAME)
	
fclean : clean
	$(RM) $(NAME)

re : fclean all