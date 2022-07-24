# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 18:29:19 by zcherrad          #+#    #+#              #
#    Updated: 2022/07/24 02:45:57 by zcherrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = cc
FLAGS =  -Wall -Wextra -Werror #-g -fsanitize=address

HEADER = philosophers.h

SRC =	main.c routine.c utils.c
			  

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@make clean -C 
	rm -rf $(OBJS) 

fclean : clean
	rm -rf $(NAME)
	rm -rf $(BNS)

re : fclean all