NAME = sfml-app

SFML_PATH = sfml
SFML_LIB =	-lsfml-graphics -lsfml-window -lsfml-system

SFML_INCLUDE_PATH = $(SFML_PATH)/include
SFML_LIB_PATH = $(SFML_PATH)/lib

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

# add SFML path to the above rule
%.o: %.cpp
	g++ -c $< -o $@ -I $(SFML_INCLUDE_PATH)

all: $(OBJ)
	g++ $(OBJ) -o $(NAME) -I $(SFML_INCLUDE_PATH) -L $(SFML_LIB_PATH) $(SFML_LIB)

test: all
	LD_LIBRARY_PATH=$(SFML_LIB_PATH) ./$(NAME)
	$(MAKE) clean

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
