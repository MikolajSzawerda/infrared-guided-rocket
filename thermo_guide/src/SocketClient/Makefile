CLIENT_LIBS = Client.c
CLIENT_LIBS_OBJS = $(CLIENT_LIBS:.c=.o)

CLIENT_TEST_SRCS = app.c
CLIENT_TEST_OBJS = $(CLIENT_TEST_SRCS:.c=.o)

AR = ar

CLIENT_LIBRARY = libclient.a
CLIENT_TEST = client_test

all: $(CLIENT_LIBRARY) $(CLIENT_TEST)

$(CLIENT_LIBRARY): $(CLIENT_LIBS_OBJS)
	$(AR) rcs $(CLIENT_LIBRARY) $(CLIENT_LIBS_OBJS)

$(CLIENT_TEST): $(CLIENT_TEST_OBJS)
	$(CC) -o $(CLIENT_TEST) $(CLIENT_TEST_OBJS) -L. -lclient -L../ImageProcessor -lprocessor

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(CLIENT_LIBS_OBJS) $(CLIENT_TEST_OBJS) $(CLIENT_LIBRARY) $(CLIENT_TEST)