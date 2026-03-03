CXX=c++

SRC= main.cpp  RPN.cpp

OBJ=$(SRC:.cpp=.o)

NAME = RPN

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all: ${NAME}

${NAME}:${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o ${NAME}

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re