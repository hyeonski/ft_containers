MLI_TESTER_DIR = ./containers_test
MY_TESTER_DIR = ./tests
TEST_RESULT = $(MY_TESTER_DIR)/result
CONT = vector
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address
INCLUDE = -I .
STD_NS = -D TEST_NS=std

#COLORS
RED=\033[0;31m
NC=\033[0m
GREEN=\033[0;32m
BLUE=\033[0;34m

.PHONY : all my mli my_unit mli_unit v l m s q

all :
	@printf "\n\n$(BLUE) [*** START OWN TESTER ***] $(NC)\n\n"
	@make my
	@printf "\n\n$(BLUE) [*** START MLI TESTER ***] $(NC)\n\n"
	@make mli
my :
	@make my_unit
	@make CONT=list my_unit
	@make CONT=map my_unit
	@make CONT=stack my_unit
	@make CONT=queue my_unit
	@make CONT=deque my_unit
	@make CONT=multimap my_unit
	@make CONT=set my_unit
	@make CONT=multiset my_unit

mli :
	@make mli_unit
	@make CONT=list mli_unit
	@make CONT=map mli_unit
	@make CONT=stack mli_unit
	@make CONT=queue mli_unit
v :
	@printf "\n\n$(BLUE) [*** START VECTOR TESTER ***] $(NC)\n\n"
	@make my_unit
	@make mli_unit
l :
	@printf "\n\n$(BLUE) [*** START LIST TESTER ***] $(NC)\n\n"
	@make my_unit CONT=list
	@make mli_unit CONT=list
q :
	@printf "\n\n$(BLUE) [*** START QUEUE TESTER ***] $(NC)\n\n"
	@make my_unit CONT=queue
	@make mli_unit CONT=queue
s :
	@printf "\n\n$(BLUE) [*** START STACK TESTER ***] $(NC)\n\n"
	@make my_unit CONT=stack
	@make mli_unit CONT=stack
m :
	@printf "\n\n$(BLUE) [*** START MAP TESTER ***] $(NC)\n\n"
	@make my_unit CONT=map
	@make mli_unit CONT=map

mli_unit :
	@cd $(MLI_TESTER_DIR) && ./do.sh $(CONT)

my_unit :
	@printf "***************************************************\n"
	@printf "**                                               **\n"
	@printf "**$(GREEN)               $(CONT) TEST START!              $(NC)**\n"
	@printf "**                                               **\n"
	@printf "***************************************************\n"
	@c++ $(CXXFLAGS) $(INCLUDE) $(MY_TESTER_DIR)/$(CONT).cpp -o $(CONT)
	@./$(CONT) > $(TEST_RESULT)/ft.$(CONT).result
	@rm $(CONT)
	@rm -rf $(CONT).dSYM
	@c++ $(CXXFLAGS) $(INCLUDE) $(STD_NS) $(MY_TESTER_DIR)/$(CONT).cpp -o $(CONT)
	@./$(CONT) > $(TEST_RESULT)/std.$(CONT).result
	@rm $(CONT)
	@rm -rf $(CONT).dSYM
	@diff -d $(TEST_RESULT)/std.$(CONT).result $(TEST_RESULT)/ft.$(CONT).result > $(TEST_RESULT)/$(CONT).diff || exit 0
	@if [ -s "$(TEST_RESULT)/$(CONT).diff" ]; then \
		printf "\n                   🔥 $(RED)FAILED$(NC) 🔥\n";\
		printf "====================== DIFF =======================\n\n";\
		cat $(TEST_RESULT)/$(CONT).diff;\
		printf "\n======================++++++=======================\n";\
	else\
		printf "\n                   😀 $(BLUE)SUCCESS$(NC) 😀\n\n";\
	fi