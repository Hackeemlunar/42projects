NAME = main

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -Wno-shadow -std=c++98

SOURCES = Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp \
          RobotomyRequestForm.cpp PresidentialPardonForm.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f *_shrubbery

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
