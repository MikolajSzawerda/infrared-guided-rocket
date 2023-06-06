
all: servo_lib client_lib camera_lib app

camera_lib:
	$(MAKE) -C Camera

client_lib:
	$(MAKE) -C SocketClient

servo_lib:
	$(MAKE) -C ServoController

app: camera_lib client_lib servo_lib
	$(MAKE) -C app

clean:
	$(MAKE) -C camera_lib clean
	$(MAKE) -C client_lib clean
	$(MAKE) -C servo_lib clean
	$(MAKE) -C app clean