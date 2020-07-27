##
## EPITECH PROJECT, 2020
## corewar
## File description:
## Makefile
##

NAME1	=	./my_mailer

NAME2	=	./gen

NAME 	=	$(NAME1) $(NAME2)

SRC1	=	./source/my_mailer.c	\
		./source/get_next_line.c	

SRC2	=	./source/generate.c

OBJ1    =       $(SRC1:.c=.o)

OBJ2    =       $(SRC2:.c=.o)

all:            $(NAME)

$(NAME1):       $(OBJ1)
		@echo -e "\033[3;34m"
		gcc -o $(NAME1) $(OBJ1) -lpthread
		@echo "-------------"
		@echo "| MY_MAILER |"
		@echo "-------------"
		@echo -e "\033[0m"

$(NAME2):	$(OBJ2)
		@echo -e "\033[3;32m"
		gcc -o $(NAME2) $(OBJ2) 
		@echo "------------------"
		@echo "| LIST_GENERATOR |"
		@echo "------------------"
		@echo -e "\033[0m"


CFLAGS += -g3  -Werror -Wextra -Wall -ansi -pedantic -std=gnu11

clean:
		rm -f  $(OBJ1) $(OBJ2)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		clean all fclean 
