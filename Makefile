# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 12:02:38 by amoinier          #+#    #+#              #
#    Updated: 2016/03/25 14:41:49 by amoinier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED =		\033[31m
GRE =		\033[32m
YEL =		\033[33m
BLU =		\033[34m
CYA =		\033[36m
STD =		\033[39m

NAME =		breadman

IDIR =		./incs/

SDIR =		./srcs/
SRCS =		$(shell ls srcs/)

ODIR =		./objs/
OBJS =		$(SRCS:.cpp=.o)
OBCC =		$(addprefix $(ODIR),$(OBJS))

FLAG =		-Wall -Wextra -Werror -I$(IDIR)

all: $(NAME)

$(NAME): header $(OBCC)
	@echo "  ${BLU}+ Compilation program:${STD} $@"
	@g++ $(OBCC) -g -I./incs/ -I/Library/Frameworks/SDL.framework/Headers SDLMain.m -framework SDL -framework Cocoa -o $(NAME)

$(ODIR)%.o: $(SDIR)%.cpp
	@echo "  ${GRE}+ Compilation:${STD} $^"
	@g++ -g -I./incs/ $^ -c -o $@

header:
	@mkdir -p $(ODIR)
	@echo "${YEL}"
	@echo "WOLF 3D"
	@echo "By: amoinier"
	@echo
	@echo "${STD}"

clean: header
	@echo "  ${RED}- Remove objects${STD}"
	@rm -rf $(OBCC)

fclean: clean
	@echo "  ${RED}- Remove $(NAME)${STD}"
	@rm -f $(NAME)

.PHONY: all $(NAME) $(ODIR)%.o header norme clean fclean re

re: fclean all
