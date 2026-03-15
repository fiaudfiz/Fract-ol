# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 12:56:33 by miouali           #+#    #+#              #
#    Updated: 2026/03/15 13:31:10 by fiaudfiz         ###   ########.fr        #
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
CFLAGS =  -O3 -march=native -Wall -Wextra -Werror -I includes -I libs/libft/includes -std=c11
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lft -L/usr/lib -lXext -lX11
DFLAGS = -fsanitize=address -fsanitize=undefined -g -Wshadow -Wunused-function

#Dossiers
SRCS_DIR = srcs/
OBJS_DIR = objs/
HEADER_DIR = includes/
MLX_DIR = libs/mlx-linux/
MLX_LIB = $(MLX_DIR)libmlx_Linux.a

LIBFT_DIR = libs/libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a

SRCS_FRACTOL = main.c prog_usage.c calculate_iteration.c color.c \
				init.c render_fractal.c key_handler.c \
				mouse_handler.c compute_simd_fractal.c \
				parser.c



ALL_SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FRACTOL))

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(ALL_SRCS))

HEADER = $(HEADER_DIR)fractol.h

RM = rm -rf

all: header start_timer $(NAME) end_timer

header:
	@echo -e "$(YELLOW) Démarrage de la compilation de Fract-ol...$(RESET)"

start_timer:
	$(eval START_TIME := $(shell date +%s))

debug: $(MLX_LIB) $(LIBFT_LIB) header start_timer $(OBJS) end_timer
	@$(CC) $(OBJS) $(LDFLAGS) $(DFLAGS) -o $(NAME)
	@echo -e "$(GREEN) Fract-ol debug ready !$(DEF_COLOR)"

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo -e "\n\n$(CYAN) ███████████                               █████                        ████"
	@sleep 0.1
	@echo -e "░░███░░░░░░█                              ░░███                        ░░███"
	@sleep 0.1
	@echo -e " ░███   █ ░  ████████   ██████    ██████  ███████               ██████  ░███"
	@sleep 0.1
	@echo -e " ░███████   ░░███░░███ ░░░░░███  ███░░███░░░███░    ██████████ ███░░███ ░███"
	@sleep 0.1
	@echo -e " ░███░░░█    ░███ ░░░   ███████ ░███ ░░░   ░███    ░░░░░░░░░░ ░███ ░███ ░███"
	@sleep 0.1
	@echo -e " ░███  ░     ░███      ███░░███ ░███  ███  ░███ ███           ░███ ░███ ░███"
	@sleep 0.1
	@echo -e " █████       █████    ░░████████░░██████   ░░█████            ░░██████  █████"
	@sleep 0.1
	@echo -e "░░░░░       ░░░░░      ░░░░░░░░  ░░░░░░     ░░░░░              ░░░░░░  ░░░░░ $(DEF_COLOR)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo -e "\n\n$(GREEN) Fract-ol is ready to be used !$(DEF_COLOR)"


# Variables pour la barre
TOTAL_FILES := $(words $(ALL_SRCS))
CURRENT_FILE := 0

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	@printf "\r$(CYAN)🛠️  Compiling Fract-ol... [%-20s] %d%%" \
		"$(shell printf '#%.0s' $$(seq 1 $$(($(PERCENT) / 5))))" $(PERCENT)
	@$(CC) $(CFLAGS) -c $< -o $@ 2> .temp_err || \
		(printf "\n$(PURPLE)❌ Erreur dans $< :$(RESET)\n" && cat .temp_err >> $(ERR_LOG) && cat .temp_err && rm -f .temp_err)


end_timer:
	@$(eval END_TIME := $(shell date +%s))
	@$(eval DURATION := $(shell echo $$(($(END_TIME) - $(START_TIME)))))
	@$(eval ERRORS := $(shell if [ -f $(ERR_LOG) ]; then grep -c "error:" $(ERR_LOG); else echo 0; fi))
	@echo -e "\n--------------------------------------------------"
	@if [ $(ERRORS) -eq 0 ]; then \
		echo "$(GREEN)✅ COMPILATION TERMINÉE !$(RESET)"; \
	else \
		echo "$(RED)❌ COMPILATION TERMINÉE AVEC DES ERREURS$(RESET)"; \
	fi
	@echo -e "Temps écoulé : $(DURATION) secondes"
	@echo -e "  Nombre d'erreurs : $(ERRORS)"
	@echo -e "--------------------------------------------------"
	@rm -f $(ERR_LOG)

clean:
	$(RM) $(OBJS_DIR)
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo -e "$(PURPLE) Objects cleaned!$(DEF_COLOR)"

fclean: clean
		$(RM) $(NAME)
		@make fclean -C $(LIBFT_DIR)
		@echo -e "$(PURPLE) $(NAME) deleted!$(DEF_COLOR)"

re: fclean all

.PHONY : all clean fclean re debug
