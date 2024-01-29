#include<mram.h>
#include<perfcounter.h>
#include<stdio.h>
#include "../device.h"

int main() {
	// allocate large wram/mram memory
	__mram_ptr void *mem_mram = (__mram_ptr void *)allocate_mram_mem();
	printf("Accessing memory at 8KB gaps\n");
	uint64_t cycles = 0;
	for (int i = 1; i < SAMPLES; i++) {
		cycles += maccess_t(mem_mram, mem_mram + i * ROW_SIZE);	
	}
	cycles /= SAMPLES;
	printf("Avg cycles: %ld, Avg DPU time: %.2e secs\n", cycles / SAMPLES, (double)cycles / CLOCKS_PER_SEC);

	printf("Accessing memory within a 8KB interval but with 64B gap\n");
	cycles = 0;
	int max_cells = ROW_SIZE / 64;
	for (int i = 1; i < max_cells; i++) {
		cycles += maccess_t(mem_mram, mem_mram + i * 64);
	}
	cycles /= max_cells;
	printf("Avg cycles: %ld, Avg DPU time: %.2e secs\n", cycles, (double)cycles / CLOCKS_PER_SEC);	
	return 0;
}
