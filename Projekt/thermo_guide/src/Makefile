CAMERA_LIBS = Camera/Camera.c Camera/i2c.c
CAMERA_LIBS_OBJS = $(CAMERA_LIBS:.c=.o)
CAMERA_LIBS_HEADERS = Camera/Camera.h Camera/i2c.h

APP_SRCS =  main.c
APP_OBJS = $(APP_SRCS:.c=.o)

AR = ar

LDFLAGS += -pthread -lrt

MAIN = thermo_client
CAMERA_LIBRARY = libcamera.a

all: $(CAMERA_LIBRARY) $(MAIN)

$(CAMERA_LIBRARY): $(CAMERA_LIBS_OBJS)
	$(AR) rcs $(CAMERA_LIBRARY) $(CAMERA_LIBS_OBJS)

$(MAIN): $(APP_OBJS) $(CAMERA_LIBRARY)
	$(CC) -o $(MAIN) $(APP_OBJS) -L. -lcamera

%.o: %.c $(CAMERA_LIBS_HEADERS)
	$(CC) -c $< -o $@

clean:
	rm -f $(CAMERA_LIBS_OBJS) $(CAMERA_LIBRARY) $(APP_OBJS) $(MAIN)