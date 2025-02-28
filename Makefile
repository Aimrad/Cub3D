#Standard

NAME		=	cub3D
INCLUDES	=	includes
INCLUDES2	=	/usr/include -Imlx
SRCS_DIR 	=	srcs/
MLX_DIR		=	./mlx
MLX_LIB		=	$(MLX_DIR)/libmlx.a
OBJS_DIR	=	obj/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I
RM			=	rm -f
AR			=	ar rcs
MLX_FLAGS	=	-Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
LIBFT		= libft

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources



SRC_FILES	=	draw_game draw_minimap exit image input main map_padding \
				map_parsing map_setup map_validator move parsing player_setup \
				rendering texture utils


SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJSF		=	.cache_exists

all:		$(MLX_LIB) $(NAME)

$(NAME):	$(OBJS)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@$(AR) $(NAME) $(OBJS)
			$(CC) $(OBJS) $(INCLUDE) -L./libft -lft -o $(NAME) $(MLX_FLAGS)
			@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJSF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(MLX_FLAGS) $(CFLAGS) $(INCLUDES) $(INCLUDES2) -c $< -o $@

$(OBJSF):
			@mkdir -p $(OBJS_DIR)

clean:
			@$(RM) -rf $(OBJS_DIR)
			@make clean -C $(LIBFT)
			@$(RM) -f $(OBJSF)
			@echo "$(BLUE)cub3D objects files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)/libft.a
			cd mlx/ && make clean
			@echo "$(CYAN)cub3D executable files cleaned!$(DEF_COLOR)"
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

norm:
	@norminette $(SRCS) $(INCLUDES) $(INCLUDES2) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm