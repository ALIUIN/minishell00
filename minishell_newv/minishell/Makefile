# Compiler and Flags
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
INCLUDES = -I./ft_printf -I./srcs -I./readline/include
LIBS = -L./ft_printf -lftprintf -L./readline/lib -lreadline

# Source files and object files
SRCS = srcs/main.c srcs/commands_1.c srcs/env_controle.c\
	srcs/handle_quotes.c srcs/complete.c srcs/lines_op.c\
	srcs/split.c srcs/pipes_controle.c srcs/linked_list_op.c\
	srcs/heredoc.c srcs/pipes_handle.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

# Build the static library for ft_printf
FT_PRINTF_LIB = ./ft_printf/libftprintf.a

# Default target
all: $(FT_PRINTF_LIB) $(NAME)

# Build the static library
$(FT_PRINTF_LIB):
	$(MAKE) -C ./ft_printf

# Build the pipex executable
$(NAME): $(FT_PRINTF_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIBS)

# Compile source files into object files
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files and executables
clean:
	rm -f $(OBJS)
	$(MAKE) -C ./ft_printf clean

# Clean everything including the static library
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./ft_printf fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
