# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/15 15:15:15 by thgermai          #+#    #+#              #
#    Updated: 2020/11/04 05:38:02 by thgermai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = initiate.c\
		utiles.c\
		main.c\
		display.c\
		routine.c

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

fg : $(OBJS)
	@(gcc $(CFLAGS) -g3 -fsanitize=address $(LIB) $(INCLUDES) $(OBJS) -o $(NAME))
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
