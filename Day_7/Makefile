NAME = dayseven

CC = c++
C_FLAGS = -Wall -Wextra -Werror

C_FILES = main.cpp
O_FILES = $(C_FILES:.cpp=.o)

INCLUDES = -I .

%.o: %.cpp
	@printf "\033[0;33mGenerating ${NAME} objects... %-33.33s\r\033[0m" $@
	@${CC} ${C_FLAGS} ${INCLUDES} -c $< -o $@

all: ${NAME}

${NAME}: ${O_FILES}
	@echo "\n\n\033[0;34mCompiling ${NAME}...\033[0m\n"
	@${CC} ${O_FILES} -o ${NAME}
	@echo "\n\033[0;35m####Res in C :\033[0m"
	@./${NAME}
	@echo "\033[0;35m##############\033[0m \n"
	@echo "\n\033[0;35m####Res in Python :\033[0m"
	@python3 main.py
	@echo "\033[0;35m##################\033[0m \n"
	@make fclean

valgrind: ${O_FILES}
	@echo "\n\n\033[0;34mCompiling ${NAME}...\033[0m\n"
	@${CC} ${O_FILES} -o ${NAME}
	@echo "\n\033[0;35m####Res in C :\033[0m"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./${NAME}
	@echo "\033[0;35m##############\033[0m \n"
	@make fclean

clean:
	@echo "\n\033[0;31mRemoving objects files...\033[0m"
	@rm -f ${O_FILES}

fclean: clean
	@echo "\n\033[0;31mRemoving ${NAME} executable...\033[0m\n"
	@rm -f ${NAME}

re: fclean all