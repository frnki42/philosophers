# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: .frnki <frnki@frnki.dev>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 16:20:42 by .frnki            #+#    #+#              #
#    Updated: 2025/04/20 16:42:42 by .frnki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILER
CC				= cc
CFLAGS 			= -Wall -Wextra -Werror

# VARIABLES
NAME			= philo

# LIBRARIES
# SRC- & OBJ-FILES
PHILO_SOURCE 	= checks.c handle_forks.c set_philo.c init_table.c philo.c \
					routine.c set_table.c threads.c utils.c monitor.c
PHILO_OBJECT 	= ${PHILO_SOURCE:.c=.o}

# TARGETS
all: $(NAME)

$(NAME): $(PHILO_OBJECT)
	@ $(CC) $(CFLAGS) $(PHILO_OBJECT) -o $(NAME) -pthread

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(PHILO_OBJECT)

fclean: clean
	@rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
