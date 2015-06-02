# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/27 19:17:42 by mschmit           #+#    #+#              #
#    Updated: 2015/06/02 15:24:23 by mschmit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S		=	serveur

NAME_C		=	client

SRC			=	srcs/

INCDIR 		=	includes/

SRC_S		=	$(SRC)serveur/check_fd.c \
				$(SRC)serveur/clean_fd.c \
				$(SRC)serveur/client_read.c \
				$(SRC)serveur/client_write.c \
				$(SRC)serveur/do_select.c \
				$(SRC)serveur/get_opt.c \
				$(SRC)serveur/init_env.c \
				$(SRC)serveur/init_fd.c \
				$(SRC)serveur/main.c \
				$(SRC)serveur/main_loop.c \
				$(SRC)serveur/srv_accept.c \
				$(SRC)serveur/srv_create.c \
				$(SRC)serveur/x.c \
				$(SRC)serveur/fct_serv.c \
				$(SRC)serveur/fct_serv2.c


OBJ_S		=	$(SRC_S:.c=.o)

SRC_C		=	$(SRC)client/client.c \
				$(SRC)client/error.c  \
				$(SRC)client/fct_cli.c\
				$(SRC)client/select.c

OBJ_C		=	$(SRC_C:.c=.o)

LIBDIR 		=	libft/

LIB 		=	$(LIBDIR)libft.a

LIB_COMP 	=	-L ./$(LIBDIR) -lft

CC 			=	clang

FLAG 		=	-I $(INCDIR) -g3 -Wall -Wextra -Werror

RED = \033[33;31m
BLUE = \033[33;34m
GREEN = \033[33;32m
RESET = \033[0m

.PHONY: all re fclean

all: $(NAME_S) $(NAME_C)

$(LIB):
		@$(MAKE) -C $(LIBDIR)

$(NAME_S): $(LIB) $(OBJ_S)
		@$(CC) -o $(NAME_S) $(FLAG) $^ $(LIB_COMP)
		@rm -f $(DEP).gch
		@echo "[$(GREEN)Compilation $(BLUE)$(NAME_S) $(GREEN)ok$(RESET)]"


$(NAME_C): $(LIB) $(OBJ_C)
		@$(CC) -o $(NAME_C) $(FLAG) $^ $(LIB_COMP)
		@rm -f $(DEP).gch
		@echo "[$(GREEN)Compilation $(BLUE)$(NAME_C) $(GREEN)ok$(RESET)]"

%.o: %.c
		@$(CC) -c -o $@ $(FLAG) $^

clean:
	@cd $(LIBDIR) && $(MAKE) $@
	@rm -f $(OBJ_S)
	@rm -f $(OBJ_C)
	@echo "[$(RED)Supression des .o de $(BLUE)$(NAME_S) $(GREEN)ok$(RESET)]"
	@echo "[$(RED)Supression des .o de $(BLUE)$(NAME_C) $(GREEN)ok$(RESET)]"

fclean: clean
		@cd $(LIBDIR) && $(MAKE) $@
		@rm -f $(NAME_S)
		@rm -f $(NAME_C)
		@echo "[$(RED)Supression de $(BLUE)$(NAME_S) $(GREEN)ok$(RESET)]"
		@echo "[$(RED)Supression de $(BLUE)$(NAME_C) $(GREEN)ok$(RESET)]"

re: fclean all
