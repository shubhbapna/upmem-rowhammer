all: hammer hammer_host

hammer: hammer.c ../shared.h ../device.h ../device.c
	dpu-upmem-dpurte-clang -o hammer hammer.c ../device.c

hammer_host: hammer_host.c hammer ../shared.h
	gcc --std=c99 hammer_host.c -o hammer_host `dpu-pkg-config --cflags --libs dpu`

clean:
	rm -f hammer hammer_host
