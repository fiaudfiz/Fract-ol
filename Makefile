# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 12:56:33 by miouali           #+#    #+#              #
#    Updated: 2026/10/22 12:57:36 by fiaudfiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_simd     = fractol_simd
NAME_threads  = fractol_threads

CC      = cc
INC     = -I include -I libs/libft/include
WFLAGS  = -Wall -Wextra -Werror -std=c11 -pthread
LIBS    = -L$(MLX_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -pthread

MLX_DIR   = libs/mlx-linux/
LIBFT_DIR = libs/libft/
MLX_LIB   = $(MLX_DIR)libmlx_Linux.a
LIBFT_LIB = $(LIBFT_DIR)libft.a

# --- Axes de config (utilisés par la cible interne "build") ---
VERSION ?= simd
VARIANT ?= release

OPT_release = -O3 -march=native
OPT_debug   = -O0 -g3 -Wshadow -fsanitize=address,undefined
OPT_prof    = -O2 -march=native -g -fno-omit-frame-pointer -pg
OPT_perf    = -O2 -march=native -g -fno-omit-frame-pointer

SUFFIX_release =
SUFFIX_debug   = _debug
SUFFIX_prof    = _prof
SUFFIX_perf    = _perf

OPT     = $(OPT_$(VARIANT))
BIN     = $(NAME_$(VERSION))$(SUFFIX_$(VARIANT))
OBJ_DIR = obj/$(VERSION)-$(VARIANT)/
SRC_DIR = src/

SRC_simd    = main_simd.c prog_usage.c calculate_iteration.c color.c init.c \
              render_fractal.c key_handler_simd.c mouse_handler_simd.c \
              compute_simd_fractal.c parser.c

SRC_threads = main_threads.c prog_usage.c color.c calculate_tile.c init.c \
              key_handler_threads.c mouse_handler_threads.c parser.c pool.c \
              benchmark.c

OBJS = $(addprefix $(OBJ_DIR), $(SRC_$(VERSION):.c=.o))
DEPS = $(OBJS:.o=.d)

ALL_BINS = $(foreach v,simd threads,\
           $(foreach s,$(SUFFIX_release) $(SUFFIX_debug) $(SUFFIX_prof) $(SUFFIX_perf),\
           $(NAME_$(v))$(s)))

# --- Cibles ambiguës : elles n'affichent que l'aide ---
all debug prof perf re: help

help:
	@printf "Usage :\n"
	@printf "  make simd | threads              build release\n"
	@printf "  make debug_simd | debug_threads  sanitizers (ASan + UBSan)\n"
	@printf "  make prof_simd | prof_threads    gprof (-pg) + perf\n"
	@printf "  make perf_simd | perf_threads    perf seul (sans -pg)\n"
	@printf "  make re_simd | re_threads        fclean + rebuild release\n"
	@printf "  make clean | fclean\n"

# --- Points d'entrée explicites ---
simd threads:
	@$(MAKE) --no-print-directory build VERSION=$@

DEBUG_T = debug_simd debug_threads
PROF_T  = prof_simd prof_threads
PERF_T  = perf_simd perf_threads

$(DEBUG_T): debug_%:
	@$(MAKE) --no-print-directory build VERSION=$* VARIANT=debug

$(PROF_T): prof_%:
	@$(MAKE) --no-print-directory build VERSION=$* VARIANT=prof

$(PERF_T): perf_%:
	@$(MAKE) --no-print-directory build VERSION=$* VARIANT=perf

re_simd: fclean simd
re_threads: fclean threads

# --- Build réel (interne) ---
build: $(MLX_LIB) $(LIBFT_LIB) $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(OPT) $(LIBS) -o $@
	@printf "✅ $@ ready\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(WFLAGS) $(OPT) $(INC) -MMD -MP -c $< -o $@

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf obj gmon.out perf.data perf.data.old
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(ALL_BINS)
	@$(MAKE) -C $(LIBFT_DIR) fclean

-include $(DEPS)

.PHONY: all help simd threads $(DEBUG_T) $(PROF_T) $(PERF_T) \
        re re_simd re_threads build debug prof perf clean fclean