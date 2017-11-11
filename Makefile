CC = gcc --enable-libstdcxx-debug

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
	@make -C $(LIBDIR) -f Makefile clean
	@echo "Fillit: objects removed"

fclean: clean
	@rm -f $(TARGET)
	@make -C $(LIBDIR) -f Makefile fclean
	@echo "Fillit: binary removed"

re:				fclean all

.PHONY:			all clean fclean re $(TARGET)
