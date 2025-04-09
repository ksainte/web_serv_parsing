CC = c++
CFLAGS = -std=c++98
SRCS = main.cpp \
		Tokenizer.cpp
EXEC_NAME = tokenize
OBJS = $(notdir $(SRCS:.cpp=.o))
INCS = Tokenizer.hpp 
all: $(EXEC_NAME)
 
$(EXEC_NAME): $(OBJS) $(INCS)
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(OBJS)
 
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC_NAME)

re: fclean all

.PHONY: all