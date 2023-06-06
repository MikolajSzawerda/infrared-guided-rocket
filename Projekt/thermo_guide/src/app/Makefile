APP_SRCS =  main.c
APP_OBJS = $(APP_SRCS:.c=.o)

LDFLAGS += -pthread -lrt

MAIN = thermo_client

all: $(MAIN)

$(MAIN): $(APP_OBJS)
	$(CC) -o $(MAIN) $(APP_OBJS) -L../Camera -lcamera -L../SocketClient -lclient -L../ServoController -lservo

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(APP_OBJS) $(MAIN)