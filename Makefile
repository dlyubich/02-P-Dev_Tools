BLUE = echo "\033[0;36m"
RED = echo "\033[0;34m"
GREEN = echo "\033[0;32m"
END = echo "\033[0m"

NAME = find_determinant
SRC = find_determinant.c
OBJ = $(SRC:.c=.o)
CC = -gcc

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$$($(BLUE))Sources compiling...$$($(END))"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$$($(GREEN))Compile with SUCCESS!$$($(END))"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)
	@echo "$$($(RED))Objects removed...$$($(END))"

fclean: clean
	rm -f $(NAME)
	@echo "$$($(RED))find_determinant binary removed...$$($(END))"

re: fclean all