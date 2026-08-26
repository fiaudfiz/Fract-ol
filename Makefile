# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miouali <miouali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 12:56:33 by miouali           #+#    #+#              #
#    Updated: 2026/08/26 13:29:07 by miouali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

DEF_COLOR = \033[0;39m
CYAN    = \033[0;96m
GREEN = \033[0;92m
PURPLE  = \033[0;95m
YELLOW  = \033[0;93m
RED     = \033[0;91m
RESET   = \033[0m

ERR_LOG = .errors.log

CC = cc
CFLAGS =  -O3 -march=native -Wall -Wextra -Werror -I include -I libs/libft/includes -std=c11
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lft -L/usr/lib -lXext -lX11
DFLAGS = -fsanitize=address -fsanitize=undefined -g -Wshadow -Wunused-function

#Dossiers
SRC_DIR = src/
OBJ_DIR = obj/
HEADER_DIR = include/
MLX_DIR = libs/mlx-linux/
MLX_LIB = $(MLX_DIR)libmlx_Linux.a

LIBFT_DIR = libs/libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a

SRC_FRACTOL = main.c prog_usage.c calculate_iteration.c color.c \
				init.c render_fractal.c key_handler.c \
				mouse_handler.c compute_simd_fractal.c \
				parser.c



ALL_SRC = $(addprefix $(SRC_DIR), $(SRC_FRACTOL))

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))

HEADER = $(HEADER_DIR)fractol.h

RM = rm -rf

all: header start_timer $(NAME) end_timer

header:
	@printf "\n$(YELLOW)Démarrage de la compilation de Fract-ol...$(RESET)\n"

start_timer:
	$(eval START_TIME := $(shell date +%s))

debug: $(MLX_LIB) $(LIBFT_LIB) header start_timer $(OBJ) end_timer
	@$(CC) $(OBJ) $(LDFLAGS) $(DFLAGS) -o $(NAME)
	@printf "$(GREEN) Fract-ol debug ready !$(DEF_COLOR)\n"

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	@printf "\n\n$(CYAN) ███████████                               █████                        ████\n"
	@sleep 0.1
	@printf "░░███░░░░░░█                              ░░███                        ░░███\n"
	@sleep 0.1
	@printf " ░███   █ ░  ████████   ██████    ██████  ███████               ██████  ░███\n"
	@sleep 0.1
	@printf " ░███████   ░░███░░███ ░░░░░███  ███░░███░░░███░    ██████████ ███░░███ ░███\n"
	@sleep 0.1
	@printf " ░███░░░█    ░███ ░░░   ███████ ░███ ░░░   ░███    ░░░░░░░░░░ ░███ ░███ ░███\n"
	@sleep 0.1
	@printf " ░███  ░     ░███      ███░░███ ░███  ███  ░███ ███           ░███ ░███ ░███\n"
	@sleep 0.1
	@printf " █████       █████    ░░████████░░██████   ░░█████            ░░██████  █████\n"
	@sleep 0.1
	@printf "░░░░░       ░░░░░      ░░░░░░░░  ░░░░░░     ░░░░░              ░░░░░░  ░░░░░ $(DEF_COLOR)\n"
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@printf "\n\n$(GREEN) Fract-ol is ready to be used !$(DEF_COLOR)\n"


# Variables pour la barre
TOTAL_FILES := $(words $(ALL_SRC))
CURRENT_FILE := 0

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell printf $$(($(CURRENT_FILE) + 1))))
	@$(eval PERCENT=$(shell printf $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	@printf "\r$(CYAN)🛠️  Compiling Fract-ol... [%-20s] %d%%" \
		"$(shell printf '#%.0s' $$(seq 1 $$(($(PERCENT) / 5))))" $(PERCENT)
	@$(CC) $(CFLAGS) -c $< -o $@ 2> .temp_err || \
		(printf "\n$(PURPLE)❌ Erreur dans $< :$(RESET)\n" && cat .temp_err >> $(ERR_LOG) && cat .temp_err && rm -f .temp_err)


end_timer:
	@$(eval END_TIME := $(shell date +%s))
	@$(eval DURATION := $(shell printf $$(($(END_TIME) - $(START_TIME)))))
	@$(eval ERRORS := $(shell if [ -f $(ERR_LOG) ]; then grep -c "error:" $(ERR_LOG); else printf 0; fi))
	@printf "\n%s\n" "--------------------------------------------------"
	@if [ $(ERRORS) -eq 0 ]; then \
		printf "$(GREEN)✅ COMPILATION TERMINÉE !$(RESET)\n"; \
	else \
		printf "$(RED)❌ COMPILATION TERMINÉE AVEC DES ERREURS$(RESET)\n"; \
	fi
	@printf "Temps écoulé : $(DURATION) secondes\n"
	@printf "  Nombre d'erreurs : $(ERRORS)\n"
	@printf "%s\n" "--------------------------------------------------"
	@rm -f $(ERR_LOG)

clean:
	$(RM) $(OBJ_DIR)
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	@printf "$(PURPLE) Objects cleaned!$(DEF_COLOR)\n"

fclean: clean
		$(RM) $(NAME)
		@make fclean -C $(LIBFT_DIR)
		@printf "$(PURPLE) $(NAME) deleted!$(DEF_COLOR)\n"

re: fclean all

.PHONY : all clean fclean re debug
