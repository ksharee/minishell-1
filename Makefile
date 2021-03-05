NAME=minishell
SRCS =	get_next_line.c get_next_line_utils.c\
		cd.c echo.c env.c env_2.c env_3.c env_4.c error.c exec.c exit.c export.c free.c ft_strjoin_three.c\
		pipe.c pwd.c utils.c unset.c parser.c my_main.c signal.c redirect.c\
		check_syntax.c parser_utils.c parsing_spec_syms.c processor.c
OBJDIR = ./objs
SRCDIR = ./srcs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
LIBS = libft/libft.a
INC_DIRS = ./includes
HEAD_MINI = $(addprefix $(INC_DIRS)/, minishell.h)
HEAD_LIB = ./libft/libft.h
HEAD_GNL = $(addprefix $(INC_DIRS)/, get_next_line.h)

all: make_libft $(OBJDIR) $(NAME)

make_libft:
	make -C libft/

$(NAME): $(OBJS) $(HEAD_LIB) $(LIBS)
	gcc -o $(NAME) $(OBJS) $(LIBS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEAD_MINI) $(HEAD_GNL)
	gcc -g -Wall -Wextra -Werror -Iincludes -Ilibft -c $< -o $@

clean:
	make -C libft/ fclean
	rm -rf $(OBJDIR) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: $(OBJS)
	gcc -g -Iincludes $(OBJS) $(LIBS) -o $(NAME)

run:
	./$(NAME)

.PHONY: clean fclean re debug run all
