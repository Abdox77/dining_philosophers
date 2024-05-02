CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread -g
API = -pthread

SRCS = philo.c \
	   init.c   \
	   utils.c   \
	   utils_2.c  \
	   routine.c   \
	   routine_utils.c   \
	   monitor.c 	  \
	   cleanup.c

OBJS = $(SRCS:.c=.o)

RM = rm -rf
NAME = philo

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(API) -c $< -o $@ 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(API) $(OBJS) -o $(NAME)
	$(RM) $(OBJS)

clean : 
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all re clean fclean

.SECONDARY : $(OBJS)
