NAME =				genom-ai

SFML_PATH =			sfml
SFML_LIB =			-lsfml-graphics -lsfml-window -lsfml-system

SFML_INCLUDE_PATH =	$(SFML_PATH)/include
SFML_LIB_PATH =		$(SFML_PATH)/lib

SRC =				main.cpp						\
					loop.cpp						\
					Renderer/render.cpp				\
					Environnement/environnement.cpp	\
					Simulation/die.cpp				\
					Simulation/reproduction.cpp		\
					Cell/cell.cpp

OBJ =				$(SRC:.cpp=.o)


%.o: %.cpp
	g++ -c $< -o $@ -I $(SFML_INCLUDE_PATH) -I include

all: $(OBJ)
	g++ $(OBJ) -o $(NAME) -I $(SFML_INCLUDE_PATH) -I include -L $(SFML_LIB_PATH) $(SFML_LIB)

test: re
	LD_LIBRARY_PATH=$(SFML_LIB_PATH) ./$(NAME)
	$(MAKE) clean

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
