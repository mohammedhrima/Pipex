# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 04:46:24 by mhrima            #+#    #+#              #
#    Updated: 2022/12/23 14:54:11 by mhrima           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

CFILES = pipex.c 0.multi_pipe.c 0.here_doc.c 
LIB = libft/libft.a
NAME = pipex

OFILES = $(CFILES:.c=.o)

all : $(NAME)

$(LIB) :
	make -C ./libft
	make clean -C ./libft

$(NAME) : $(OFILES) $(LIB)
	$(CC) $(CFLAGS) $(OFILES) $(LIB) -o $(NAME) 

bonus: $(NAME)
	$(CC) $(CFLAGS) $(OFILES) $(LIB) -o $(NAME) 

clean : 
	$(RM) $(OFILES)
	
fclean : clean
	$(RM) $(NAME) $(LIB)

re : fclean all