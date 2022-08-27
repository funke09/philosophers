# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 18:29:19 by zcherrad          #+#    #+#              #
#    Updated: 2022/08/27 16:43:50 by zcherrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = cc
FLAGS =  -Wall -Wextra -Werror  -pthread #-g -fsanitize=address

HEADER = philosophers.h

SRC = main.c utils.c routine.c utils2.c philos_actions.c ft_free.c
			  

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) 

fclean : clean
	rm -rf $(NAME)
	
re : fclean all