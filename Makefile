NAME	=	ircserv

SRCS	=	./Sources/app/main.cpp \
			./Sources/server/Server.cpp\
			./Sources/service/UsersService.cpp\
			./Sources/service/Postman.cpp\
			./Sources/models/User.cpp\
			./Sources/models/Channel.cpp\
			./Sources/utility/utility.cpp\
			./Sources/service/commands/away.cpp\
			./Sources/service/commands/nick.cpp\
			./Sources/service/commands/pass.cpp\
			./Sources/service/commands/privmsg.cpp\
			./Sources/service/commands/user.cpp\
			./Sources/service/commands/ping.cpp\
			./Sources/service/commands/notice.cpp\
			./Sources/service/commands/quit.cpp\
			./Sources/service/commands/join.cpp\
			./Sources/service/commands/ison.cpp\
			./Sources/service/commands/names.cpp\
			./Sources/service/commands/topic.cpp\
			./Sources/service/commands/mode.cpp\
			./Sources/service/commands/kick.cpp\
			./Sources/service/commands/part.cpp\
			./Sources/service/commands/invite.cpp\


HEADERS	=	./Sources/server/Server.hpp \
			./Sources/service/Service.hpp\
			./Sources/service/UsersService.hpp\
			./Sources/service/Postman.hpp\
			./Sources/models/User.hpp\
			./Sources/models/Channel.hpp\
			./Sources/utility/utility.hpp\


VPATH	=	./Sources/ \
			./Sources/app \
			./Sources/models \
			./Sources/service \
			./Sources/server

OBJ_DIR	=	./obj/
OBJS	=	$(SRCS:.cpp=.o)	\

CPPFLAGS	= -Wall -Wextra -Werror -std=c++98

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADERS)
			c++ $(CPPFLAGS) $(OBJS) -o $(NAME)

clean	:
			@rm -rf $(OBJS)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all