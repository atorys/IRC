NAME	=	bot

SRCS	=	sources/Bot.cpp\
			sources/main.cpp\
			../utility/utility.cpp\


HEADERS	=	sources/Bot.hpp\
			../../utility/utility.hpp\

VPATH	=	sources/

OBJ_DIR	=	./obj/
OBJS	=	$(SRCS:.cpp=.o)	\

CPPFLAGS = -Wall -Werror -Wextra

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADERS)
			c++ $(CPPFLAGS) $(OBJS) -o $(NAME)

clean	:
			@rm -rf $(OBJS)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all