NAME := pipex

RULE := all

CC := cc
CFLAGS := -Wall -Wextra -Werror
IFLAGS := -I includes -I ../libft/header

SRCDIR := srcs
OBJDIR := objs
ARCDIR := ../libft

SRCS	:= 	main.c \
			process.c \
			exec.c \
			wait.c \
			helper.c
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)
ARCS	:= $(ARCDIR)/libft.a

all: $(NAME)

debug: RULE=debug
debug: CC=gcc
debug: CFLAGS=-g3 -Wall -Wextra -Werror
debug: $(NAME)

memory: RULE=memory
memory: CC=cc
memory: CFLAGS=-Wall -Wextra -Werror -fsanitize=address
memory: $(NAME)

$(NAME): $(ARCS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(ARCS) $(IFLAGS) $(MLXFLAGS) -o $@

$(ARCS):
	@make -C $(ARCDIR) $(RULE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

clean:
	@make -C $(ARCDIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	@make -C $(ARCDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
