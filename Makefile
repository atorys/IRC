NAME	=	ircserv

SRCS	=	./Sources/app/main.cpp \
			./Sources/server/Server.cpp\
			./Sources/service/UsersService.cpp\
			./Sources/service/Postman.cpp\
			./Sources/models/User.cpp

HEADERS	=	./Sources/server/Server.hpp \
			./Sources/service/Service.hpp
			./Sources/service/UsersService.hpp
			./Sources/service/Postman.hpp
			./Sources/models/User.hpp


VPATH	=	./Sources/ \
			./Sources/app \
			./Sources/models \
			./Sources/service \
			./Sources/server

OBJ_DIR	=	./obj/
OBJS	=	$(SRCS:.cpp=.o)	\

#FLAGS	=	-Wall -Wextra -Werror -std=c++98

.PHONY	:	all clean fclean re
all		:	$(NAME)

$(NAME)	:	$(OBJS)
			c++ $(FLAGS) $(OBJ_DIR)* -o $@

$(OBJS)	:	$(SRCS) $(HEADERS)
			c++ $(FLAGS) -c $< -o $@
			@mkdir -p $(OBJ_DIR)
			@mv ./Sources/*/*.o $(OBJ_DIR)

clean	:
			@rm -rf $(OBJ_DIR)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all