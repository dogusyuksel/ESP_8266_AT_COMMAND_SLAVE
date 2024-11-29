CFILES = tcp_client.c
  
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LIB_PATH = ./../cjson/build
INC_PATH = ./../cjson
LIB_NAME = cjson

NAME = tcp_client.exe

all:
	gcc $(CFILES) -L$(LIB_PATH) -l$(LIB_NAME) -I$(INC_PATH) -o $(NAME) -Wl,-rpath=$(LIB_PATH)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
