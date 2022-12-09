# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 08:14:10 by mhrima            #+#    #+#              #
#    Updated: 2022/12/09 08:27:42 by mhrima           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = pipex.c libft/libft.a
OUT = pipex 



all : $(OUT)

$(OUT) : $(SRC)
	$(CC) $(SRC) -o $(OUT)

#bonus: $(OBJS_BONUS) $(OBJS)
#	$(AR) $(NAME) $(OBJS_BONUS) $(OBJS)


clean : 
	$(RM) $(OUT)
	
fclean : clean
	$(RM) $(OUT)

re : fclean all