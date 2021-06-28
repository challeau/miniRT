NAME			=	miniRT


SRCS_MAIN_PATH		=	./srcs
SRCS_MAIN_NAME		=	minirt.c	\
				events.c	\
				images.c

OBJS_MAIN_PATH		=	objs
OBJS_MAIN_NAME		=	$(SRCS_MAIN_NAME:.c=.o)

SRCS_MAIN = $(addprefix $(SRCS_MAIN_PATH)/,$(SRCS_MAIN_NAME))
OBJS_MAIN = $(addprefix $(OBJS_MAIN_PATH)/,$(OBJS_MAIN_NAME))

SRCS_PARSER_PATH	=	./srcs/parser
SRCS_PARSER_NAME	=	get_scene_from_file.c		\
				checks_and_error_handling.c	\
				elem_set_fcts.c			\
				elem_set_fcts_2.c		\
				parser_utils.c			\
				parser_utils_2.c

OBJS_PARSER_PATH	=	objs/parser
OBJS_PARSER_NAME	=	$(SRCS_PARSER_NAME:.c=.o)

SRCS_PARSER = $(addprefix $(SRCS_PARSER_PATH)/,$(SRCS_PARSER_NAME))
OBJS_PARSER = $(addprefix $(OBJS_PARSER_PATH)/,$(OBJS_PARSER_NAME))

SRCS_BONUS_PATH		=	./bonus
SRCS_BONUS_NAME		=	parser/get_scene_from_file_bonus.c		\
				parser/checks_and_error_handling_bonus.c	\
				parser/elem_set_fcts_bonus.c			\
				parser/elem_set_fcts_2_bonus.c			\
				parser/parser_utils_bonus.c			\
				parser/parser_utils_2_bonus.c

OBJS_BONUS_PATH	=	objs/bonus
OBJS_BONUS_NAME	=	$(SRCS_BONUS_NAME:.c=.o)

SRCS_BONUS = $(addprefix $(SRCS_BONUS_PATH)/,$(SRCS_BONUS_NAME))
OBJS_BONUS = $(addprefix $(OBJS_BONUS_PATH)/,$(OBJS_BONUS_NAME))

CC		=	clang
CFLAGS		=	-Wall -Werror -Wextra -g 

CPPFLAGS	=	-I inc/libft/ -I inc/minilibx-linux/

LDFLAGS		=	inc/libft/libft.a inc/minilibx-linux/libmlx_Linux.a
LDLIBS		=	-lm -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS_PARSER)
	@make -C inc/libft
	@make -C inc/minilibx-linux
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "Compilation \033[1;32mOK\033[m"

$(OBJS_MAIN_PATH)/%.o: $(SRCS_MAIN_PATH)/%.c
	@mkdir $(OBJS_MAIN_PATH)   2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

$(OBJS_PARSER_PATH)/%.o: $(SRCS_PARSER_PATH)/%.c
	@mkdir $(OBJS_PARSER_PATH)   2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
	@make -C inc/libft clean
	@make -C inc/minilibx-linux clean
	@rm -f $(OBJS_MAIN) $(OBJS_PARSER)
	@rmdir $(OBJS_PARSER_PATH) $(OBJS_MAIN_PATH)
	@echo "Removing objs"

fclean: clean
	@make -C inc/libft fclean
	@make -C inc/minilibx-linux clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJS_BONUS)
	@make -C inc/libft
	@make -C inc/minilibx-linux
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "Bonus compilation \033[1;32mOK\033[m"

$(OBJS_BONUS_PATH)/%.o: $(SRCS_BONUS_PATH)/%.c
	@mkdir $(OBJS_BONUS_PATH)   2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

.PHONY: all, clean, fclean, re

