.PHONY: all, clean, fclean, re.
NAME = doom-editor

LIBFT_PATH = ../libft/

INC = -I ./include/ -I ./$(LIBFT_PATH)include/ -I ~/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/ -I ~/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2/ -I ~/.brew/Cellar/sdl2_image/2.0.5/include/SDL2/ -I ~/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2/

FRAMEWORKS = -L. ~/.brew/Cellar/sdl2/2.0.9_1/lib/libSDL2.a -L. ~/.brew/Cellar/sdl2_mixer/2.0.4/lib/libSDL2_mixer.a -L. ~/.brew/Cellar/sdl2_image/2.0.5/lib/libSDL2_image.a -L. ~/.brew/Cellar/sdl2_ttf/2.0.15/lib/libSDL2_ttf.a

SRCS_NAME = src/*.c

SRCO_NAME = $(SRCS_NAME:.c=.o)

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@gcc $(SRCS_NAME) $(INC) -L $(LIBFT_PATH) `sdl2-config --libs` -O3 -lft -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o $(NAME)
	@echo "\033[32m\033[1m[√] - Binary \033[1;33m\033[4m\033[1m$(NAME)\033[0m\033[1;0m\033[32m\033[1m created.\033[0m"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@rm -rf $(SRCO_NAME)
	@echo "\033[31m\033[1m[X] - \033[4m$(NAME)\033[0m\033[31m\033[1m Objects files removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@rm -rf $(NAME)
	@echo "\033[31m\033[1m[X] - Bin \033[4m$(NAME)\033[0m \033[31m\033[1mremoved.\033[0m"

re: fclean all