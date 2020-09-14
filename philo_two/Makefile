# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/15 15:15:15 by thgermai          #+#    #+#              #
#    Updated: 2020/08/02 11:45:39 by thgermai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = display.c\
		initiate.c\
		utiles.c\
		main.c\
		wait_for_death.c

INCLUDES = -I .
OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DPDCS = $(OBJS:.o=.d)
LIB = -lpthread
CFLAGS = -Wall -Wextra -Werror -pthread

opti :
	@(make -j all)

all : $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@(gcc $(CFLAGS) $(LIB) $(INCLUDES) $(OBJS) -o $(NAME))
	@(echo "$(NAME) created")

$(OBJSDIR)/%.o : $(SRCSDIR)/%.c | $(OBJSDIR)
	@(echo "Compiling -> $^")
	@(gcc $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@)

$(OBJSDIR) :
	@(mkdir -p .objs)

clean :
	@(rm -f $(NAME))

fclean: clean
	@(rm -rf $(OBJSDIR))

re : fclean all
