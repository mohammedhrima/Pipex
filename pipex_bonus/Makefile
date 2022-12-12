# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 08:14:10 by mhrima            #+#    #+#              #
#    Updated: 2022/12/11 15:00:18 by mhrima           ###   ########.fr        #
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

#bonus: $(OBJS_BONUS) $(OBJS)
#	$(AR) $(NAME) $(OBJS_BONUS) $(OBJS)


clean : 
	$(RM) $(NAME)
	
fclean : clean
	$(RM) $(NAME)

re : fclean all