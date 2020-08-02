# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/15 15:15:15 by thgermai          #+#    #+#              #
#    Updated: 2020/07/25 16:43:11 by thgermai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = display.c\
		initiate.c\
		utiles.c\
		main.c

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
