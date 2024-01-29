all: timing timing_host

timing: timing.c ../shared.h ../device.h ../device.c
	dpu-upmem-dpurte-clang -o timing timing.c ../device.c

timing_host: timing_host.c timing ../shared.h
	gcc --std=c99 timing_host.c -o timing_host `dpu-pkg-config --cflags --libs dpu`

clean:
	rm -f timing timing_host
