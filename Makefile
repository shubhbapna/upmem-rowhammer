all: hammer timing

hammer:
	make -C ./src/rowhammer

timing:
	make -C ./src/timing

clean:
	make -C ./src/rowhammer	clean
	make -C ./src/timing clean
