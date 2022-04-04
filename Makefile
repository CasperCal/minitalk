# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccaluwe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 13:21:08 by ccaluwe           #+#    #+#              #
#    Updated: 2022/04/01 13:50:14 by ccaluwe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SRV	= server
NAME_CLT	= client

SRC_SRV		= server.c utils.c
SRC_CLT		= client.c utils.c

RM			= rm -rf

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

OBJ_SRV		= ${SRC_SRV:.c=.o}
OBJ_CLT		= ${SRC_CLT:.c=.o}

all:		$(NAME_CLT) $(NAME_SRV)

$(NAME_CLT):	$(OBJ_CLT)
					$(CC) $(CFLAGS) $(OBJ_CLT) -o $@

$(NAME_SRV):	$(OBJ_SRV)
					$(CC) $(CFLAGS) $(OBJ_SRV) -o $@

clean:	
			$(RM) $(OBJ_SRV) $(OBJ_CLT)

fclean:		clean
				$(RM) $(NAME_SRV) $(NAME_CLT)

re:		fclean all

.PHONY:	all clean fclean re


