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

SRCS_UTILS_PATH		=	./srcs/utils
SRCS_UTILS_NAME		=	mat3.c			\
				mat4.c			\
				maths_utils.c		\
				vec2f.c			\
				vec2f_ops.c		\
				vec2f_scal_ops.c	\
				vec3f.c			\
				vec3f_ops.c		\
				vec3f_scal_ops.c	\
				vec4f.c			\
				vec_mat_ops.c

OBJS_UTILS_PATH	=	objs/utils
OBJS_UTILS_NAME	=	$(SRCS_UTILS_NAME:.c=.o)

SRCS_UTILS = $(addprefix $(SRCS_UTILS_PATH)/,$(SRCS_UTILS_NAME))
OBJS_UTILS = $(addprefix $(OBJS_UTILS_PATH)/,$(OBJS_UTILS_NAME))

SRCS_RMRCH_PATH		=	./srcs/raymarcher
SRCS_RMRCH_NAME		=	raymarcher.c		\
				sdfs.c			\
				get_light.c		\
				raymarcher_utils.c

OBJS_RMRCH_PATH	=	objs/raymarcher
OBJS_RMRCH_NAME	=	$(SRCS_RMRCH_NAME:.c=.o)

SRCS_RMRCH = $(addprefix $(SRCS_RMRCH_PATH)/,$(SRCS_RMRCH_NAME))
OBJS_RMRCH = $(addprefix $(OBJS_RMRCH_PATH)/,$(OBJS_RMRCH_NAME))

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

$(NAME): $(OBJS_MAIN) $(OBJS_PARSER) $(OBJS_UTILS) $(OBJS_RMRCH)
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

$(OBJS_UTILS_PATH)/%.o: $(SRCS_UTILS_PATH)/%.c
	@mkdir $(OBJS_UTILS_PATH)   2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

$(OBJS_RMRCH_PATH)/%.o: $(SRCS_RMRCH_PATH)/%.c
	@mkdir $(OBJS_RMRCH_PATH)   2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
	@make -C inc/libft clean
	@make -C inc/minilibx-linux clean
	@rm -f $(OBJS_PARSER) $(OBJS_UTILS) $(OBJS_RMRCH) $(OBJS_MAIN)
	@rmdir $(OBJS_PARSER_PATH) $(OBJS_UTILS_PATH) $(OBJS_RMRCH_PATH) $(OBJS_MAIN_PATH)
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

