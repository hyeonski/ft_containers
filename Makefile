SRCNAME	= list.cpp

SRCDIR = ./tests/

SRCS = $(addprefix $(SRCDIR), $(SRCNAME))

INC = -I ./

NAME = test.out

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98 $(INC)
DFLAGS = -Wall -Wextra -Werror -std=c++98 $(INC) -g3 -fsanitize=address

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) 

dbg : $(SRCS)
	$(CC) $(DFLAGS) $(SRCS) -o $(NAME) 
	lldb $(NAME)

test : $(SRCS)
	@echo "compiling ft..."
	@$(CC) $(DFLAGS) -D NS=ft $(SRCS) -o $(NAME)
	@./test.out > ft_result.txt
	@echo "compiling std..."
	@$(CC) $(DFLAGS) -D NS=std $(SRCS) -o $(NAME)
	@./test.out > std_result.txt
	@echo "diff between ft & std"
	@diff ft_result.txt std_result.txt
	
clean:
	rm -rf test.out
	rm -rf ft_result.txt
	rm -rf std_result.txt
	rm -rf test.out.dSYM

fclean:
	rm -rf test.out
	rm -rf ft_result.txt
	rm -rf std_result.txt
	rm -rf test.out.dSYM


re : fclean all

all : $(NAME)

.PHONY : fclean re test