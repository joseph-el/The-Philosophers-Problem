# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/31 14:30:34 by yoel-idr          #+#    #+#              #
#    Updated: 2023/01/06 11:56:18 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

SRC  := philosophers.c utils.c 
OBJ  := $(SRC:.c=.o)
FLAG := -Wall -Wextra -Werror -pthread
RM   := rm -f

all : $(NAME)
	@echo "\n\033[0;32m<Dining Philosophers Problem>\033[0m"
	@echo "\nFor the students 42 who want to apply ur tests,\n"
	@echo "I want to tell u this version of the project does not handle\n"
	@echo "all tests like the version in my profile at intra 😃\n"

$(NAME) : $(OBJ)
		@cc $(FLAG) $^ -o $(NAME)

.c.o   :
		@echo "\033[0;33mGenerating Philosophers objects...\033[0m" $<
		@cc $(FLAG) -c $< -o $@
clean  :
		@echo "\033[0;31mDeleting objects...\033[0m"
		@$(RM) $(OBJ) $(NAME)
fclean : clean

re 	   : fclean all

.PHONY = all clean fclean re