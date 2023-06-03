
all: camera_lib client_lib app

camera_lib:
	$(MAKE) -C Camera

client_lib:
	$(MAKE) -C SocketClient

app: camera_lib client_lib
	$(MAKE) -C app

clean:
	$(MAKE) -C camera_lib clean
	$(MAKE) -C client_lib clean
	$(MAKE) -C app clean