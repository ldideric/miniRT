# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ldideric <ldideric@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/06 14:04:07 by ldideric      #+#    #+#                  #
#    Updated: 2020/09/05 18:40:41 by ldideric      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	miniRT

SRC_PATH		=	src
PARS_PATH		=	./$(SRC_PATH)/parsing/
RAY_PATH		=	./$(SRC_PATH)/raytracing/
EXTRA_PATH		=	./$(SRC_PATH)/extras/
# LIBFT_PATH		=	./$(SRC_PATH)/libft/
# PRINTF_PATH		=	./$(SRC_PATH)/printf/

PARS_SRC		=	reader.c \
					reader_basic.c \
					read_object.c

RAY_SRC			=	raytracer.c \
					ndc.c \
					math1.c \
					sphere.c \
					plane.c \
					triangle.c

EXTRA_SRC		=	error.c \
					hooks.c \
					extra1.c \
					t_graphing.c

PARS_SRC_DIR	=	$(PARS_SRC:%=$(PARS_PATH)%)
RAY_SRC_DIR		=	$(RAY_SRC:%=$(RAY_PATH)%)
EXTRA_SRC_DIR	=	$(EXTRA_SRC:%=$(EXTRA_PATH)%)
# LIBFT_SRC_DIR	=	$(LIBFT_SRC:%=$(LIBFT_PATH)%)
# PRINTF_SRC_DIR	=	$(PRINTF_SRC:%=$(PRINTF_PATH)%)

PARS_OBJ_DIR	=	$(PARS_SRC_DIR:.c=.o)
RAY_OBJ_DIR		=	$(RAY_SRC_DIR:.c=.o)
EXTRA_OBJ_DIR	=	$(EXTRA_SRC_DIR:.c=.o)
# LIBFT_OBJ_DIR	=	$(LIBFT_SRC_DIR:.c=.o)
# PRINTF_OBJ_DIR	=	$(PRINTF_SRC_DIR:.c=.o)

C_FILES			=	./$(SRC_PATH)/minirt.c $(PARS_SRC_DIR) $(RAY_SRC_DIR)\
					$(EXTRA_SRC_DIR) #$(LIBFT_SRC_DIR) $(PRINTF_SRC_DIR)
O_FILES			=	$(C_FILES:.c=.o)
FILES			=	$(O_FILES) mlx/libmlx.dylib
EXTRAS			=	libmlx.dylib $(SRC_PATH)/biglib.a

W_FLAGS			=	-Wall -Werror -Wextra
LIB_FLAGS		=	-framework OpenGL -framework AppKit -Imlx -Iinc
FLAGS			=	$(W_FLAGS) $(LIB_FLAGS)
MMLX			=	make -C ./mlx && cp mlx/libmlx.dylib .
CMLX			=	$(NAME) libmlx.dylib

ifdef DEBUG
FLAGS	+= -g
endif
ifdef FSAN
FLAGS	+= -fsanitize=address
endif
ifdef MLX
MMLX	= @echo "$(R)Skipping re-compiling the MLX Library.$(RES)"
CMLX	= $(NAME)
endif

#COLOR CODES
#red
R	= \x1b[38;5;196m
#orange
O	= \x1b[38;5;208m
#yellow
Y	= \x1b[38;5;3m
#green
G	= \x1b[38;5;83m
#blue
B	= \x1b[38;5;21m
#purple
P	= \x1b[38;5;129m
#light pink
PI	= \x1b[38;5;219m
#grey
GR	= \x1b[38;5;244m
#reset to white
RES	= \x1b[0m

SUM		= \x1b[38;5;$(X)m
X		= 1

all: $(NAME)

$(NAME):
	@echo "$(P)Compiling MiniLibX Library$(O)"
	$(MMLX)
	@echo "$(P)Compiling miniRT$(PI)"
	gcc $(C_FILES) $(FLAGS) $(EXTRAS) -o $(NAME)
	@echo "$(G)Done!$(RES)"

realmake:
	@echo "Compiling..."

clean:
	@echo "$(P)Cleaning mlx object files$(RES)"
	@make clean -C ./mlx
	@echo "$(P)Cleaning minirt object files$(RES)"
	@rm -rf $(O_FILES)

fclean: clean
	@echo "$(P)Cleaning executable$(RES)"
	rm -rf $(CMLX)

re: fclean all

test:
	@echo "$(O_FILES:.o=.o\n)"

norm:
	@echo "$(R)Norminette:$(RES)"
	@norminette $(C_FILES) Makefile \
		| grep -c "Error" || printf ""
	@echo "$(R)Norminette+:$(RES)"
	@python ~/norminette+/run.py $(C_FILES) Makefile \
		| grep -c "Error" || printf ""

normall:
	@echo "$(R)Norminette:$(RES)"
	@norminette $(C_FILES) Makefile
	@echo "$(R)Norminette+:$(RES)"
	@python ~/norminette+/run.py $(C_FILES) Makefile
