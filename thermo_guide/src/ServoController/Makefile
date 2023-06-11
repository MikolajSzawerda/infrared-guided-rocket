SERVO_LIBS = ServoController.c pwm.c
SERVO_LIBS_OBJS = $(SERVO_LIBS:.c=.o)

SERVO_TEST_SRCS = app.c
SERVO_TEST_OBJS = $(SERVO_TEST_SRCS:.c=.o)

AR = ar

SERVO_LIBRARY = libservo.a
SERVO_TEST = servo_test

all: $(SERVO_LIBRARY) $(SERVO_TEST)

$(SERVO_LIBRARY): $(SERVO_LIBS_OBJS)
	$(AR) rcs $(SERVO_LIBRARY) $(SERVO_LIBS_OBJS)

$(SERVO_TEST): $(SERVO_TEST_OBJS)
	$(CC) -o $(SERVO_TEST) $(SERVO_TEST_OBJS) -L. -lservo

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(SERVO_LIBS_OBJS) $(SERVO_LIBRARY) $(SERVO_TEST_OBJS) $(SERVO_TEST)