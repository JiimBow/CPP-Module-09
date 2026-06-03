# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/08 10:36:14 by jodone            #+#    #+#              #
#    Updated: 2026/06/03 11:42:56 by jimbow           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98

# COLOR
GREEN   := \033[1;38;5;46m
RESET   := \033[0m

# DIR
OBJ_DIR		= objects/

# PmergeMe
NAME		= PmergeMe

HEADER		= -I. 

SRC			= main.cpp \
				PmergeMe.cpp

OBJ			= $(SRC:%.cpp=$(OBJ_DIR)%.o)

all :		$(NAME)

$(NAME): $(OBJ)
			@$(CC) $(CFLAGS) $(HEADER) $(OBJ) -o $(NAME)
			@printf "${GREEN}\r[▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬] SUCCESS 100%%${RESET}\n"

TOTAL		:= $(words $(SRC))
COUNT		:= 0

$(OBJ_DIR)%.o: %.cpp
			@mkdir -p $(dir $@)
			@$(CC) -c $(CFLAGS) $(HEADER) $< -o $@
			@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
			@PERCENT=$$(($(COUNT)*99/$(TOTAL))) ; \
			BAR=$$(($(COUNT)*39/$(TOTAL))) ; \
			if [ $$PERCENT -lt 33 ]; then \
				COLOR_CODE=196; \
			elif [ $$PERCENT -lt 66 ]; then \
				COLOR_CODE=208; \
			else \
				COLOR_CODE=226; \
			fi ; \
			printf "\033[38;5;%sm\r[" $$COLOR_CODE ; \
			i=1; while [ $$i -le $$BAR ]; do printf "▬"; i=$$((i+1)); done ; \
			while [ $$i -le 40 ]; do printf " "; i=$$((i+1)); done ; \
			printf "] LOADING %3d%%\033[0m" $$PERCENT


clean:
			@if ls $(OBJ_DIR) >/dev/null 2>&1; then \
			echo "${GREEN}====   $(NAME)   ==== : >>>OBJ CLEANED<<<${RESET}"; \
			fi
			@rm -f $(OBJ)
			@rm -rf $(OBJ_DIR)

fclean:		clean
			@if ls $(NAME) >/dev/null 2>&1; then \
			echo "${GREEN}====   $(NAME)   ==== : >>>ALL CLEANED<<<${RESET}"; \
			fi
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re