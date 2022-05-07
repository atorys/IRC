NAME	=	ircserv

SRCS	=	./Sources/app/main.cpp \
			./Sources/server/Server.cpp\
			./Sources/service/UsersService.cpp\
			./Sources/service/Postman.cpp\
			./Sources/models/User.cpp\
			./Sources/models/Channel.cpp\
			./Sources/utility/utility.cpp\

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

CPPFLAGS	= 

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADERS)
			c++ $(CPPFLAGS) $(OBJS) -o $(NAME)

clean	:
			@rm -rf $(OBJS)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all