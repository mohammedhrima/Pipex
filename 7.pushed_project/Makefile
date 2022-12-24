# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 04:46:24 by mhrima            #+#    #+#              #
#    Updated: 2022/12/24 09:05:45 by mhrima           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

CFILES = pipex.c 0.here_doc.c 1.here_doc.c 2.multi_pipe.c 3.tools.c 4.tools.c 5.tools.c 6.tools.c 7.tools.c 8.tools.c 9.tools.c
NAME = pipex

OFILES = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME) 

bonus: $(NAME)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME) 

clean : 
	$(RM) $(OFILES)
	
fclean : clean
	$(RM) $(NAME)

re : fclean all