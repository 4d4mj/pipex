# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 15:03:52 by ajabado           #+#    #+#              #
#    Updated: 2024/07/03 15:03:52 by ajabado          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# color codes
END=\033[0m
BOLD=\033[1m
UNDER=\033[4m
REV=\033[7m
GREY=\033[30m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
PURPLE=\033[35m
CYAN=\033[36m
WHITE=\033[37m
HIDE=\033[?25l
SHOW=\033[?25h

# pipex
OBJS = $(SRC:.c=.o)
SRC = $(addprefix $(SRC_DIR), \
utils.c here_doc.c split_command.c main.c \
)

SRC_DIR	= ./src/
INC_DIR	= ./includes/
CC = gcc
MF = Makefile

FLAGS = -Wall -Wextra -Werror

NAME = pipex
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)/libft.a
HEADER	= $(LIBFT_DIR)$(INC_DIR)/libft.h

COUNTER = 0
TOTAL_FILES = $(shell echo $$(($(words $(SRC)))))

all : $(LIBFT) $(NAME)

bonus: $(LIBFT) $(NAME)

$(NAME) : $(OBJS) $(HEADER) $(MF)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@/bin/echo -e "\n$(BOLD)$(GREEN)> $(NAME) has been created$(END)$(SHOW)"

$(LIBFT) :
	@make -C $(LIBFT_DIR)

clean :
	@rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	@/bin/echo -e "$(YELLOW)> All objects files of $(NAME) have been deleted$(END)"

fclean :
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@/bin/echo -e "$(YELLOW)> All objects files of $(NAME) have been deleted$(END)"
	@/bin/echo -e "$(BOLD)$(GREEN)> Cleaning of $(NAME) has been done$(END)"

re : fclean all

%.o : %.c $(HEADER) Makefile
	@/bin/echo -en "$(HIDE)"
	@$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR)
	@/bin/echo -en "$(BOLD)$(YELLOW)\rCompiling $(NAME): $(END)["
	@printf "%0.s#" $(shell seq 1 $(COUNTER))
	@if [ $(COUNTER) -lt $(TOTAL_FILES) ]; then \
		printf "%0.s." $(shell seq 1 $$(($(TOTAL_FILES) - $(COUNTER)))); \
	fi
	@printf "] (%d/%d)" $(COUNTER) $(TOTAL_FILES)

.PHONY: all clean fclean re
