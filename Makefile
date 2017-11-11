# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amichak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/11 12:49:49 by amichak           #+#    #+#              #
#    Updated: 2017/11/11 12:51:58 by amichak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:			all clean fclean re $(TARGET)

CC = gcc

TARGET = fillit

SRC = main.c valid.c frame.c join.c

CFLAGS = -Wall -Wextra -Werror

HEADER = -I ./includes/

LIBINCL = -L. includes/libft/libft.a

LIBDIR = includes/libft

OBJFOLD = ./obj/

OBJ = $(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(SRC)))

all: 			$(TARGET)

$(TARGET):		$(OBJ)
	@make -C $(LIBDIR) -f Makefile
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBINCL)
	@echo "Fillit: done"

$(OBJFOLD)%.o: %.c
	@mkdir -p $(OBJFOLD)
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

clean:
	@rm -rf $(OBJFOLD)
	@echo "Fillit: objects removed"

fclean: clean
	@rm -f $(TARGET)
	@make -C $(LIBDIR) -f Makefile fclean
	@echo "Fillit: binary removed"

re:				fclean all
