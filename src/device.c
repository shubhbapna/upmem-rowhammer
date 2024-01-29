#include "device.h"
#include<alloc.h>
#include<mram.h>
#include<perfcounter.h>

// needs to be global for some reason??
uint8_t __mram_noinit mem[MRAM_BUFFER];
__mram_ptr void *allocate_mram_mem() {
	// wram has only 64KB available so can't allocate enough for one mram_write
	__dma_aligned uint8_t mem_init[MAX_MRAM_WRITE_SIZE];
	memset(mem_init, 0, MAX_MRAM_WRITE_SIZE);
	for (int i = 0; i < MRAM_BUFFER / MAX_MRAM_WRITE_SIZE; i++) {
		mram_write(mem_init, mem + (i * MAX_MRAM_WRITE_SIZE), MAX_MRAM_WRITE_SIZE); 
	}
	return (__mram_ptr void *)mem;
}

uint32_t hammer(__mram_ptr void *victim, __mram_ptr void *attacker1, __mram_ptr void *attacker2) {
	__dma_aligned uint8_t victim_init[MAX_MRAM_WRITE_SIZE];
	__dma_aligned uint8_t attacker_init[MAX_MRAM_WRITE_SIZE];
	memset(victim_init, 0x55, MAX_MRAM_WRITE_SIZE);
	memset(attacker_init, 0xAA, MAX_MRAM_WRITE_SIZE);

	for (int i = 0; i < ROW_SIZE / MAX_MRAM_WRITE_SIZE; i++) {
		mram_write(victim_init, victim + (i * MAX_MRAM_WRITE_SIZE), MAX_MRAM_WRITE_SIZE);
		mram_write(attacker_init, attacker1 + (i * MAX_MRAM_WRITE_SIZE), MAX_MRAM_WRITE_SIZE);
		mram_write(attacker_init, attacker2 + (i * MAX_MRAM_WRITE_SIZE), MAX_MRAM_WRITE_SIZE);
	}
	
	__dma_aligned uint8_t wram_cache[MAX_MRAM_WRITE_SIZE];
	int num_reads = HAMMERS_PER_ITER;
	while(num_reads-- > 0) {
		// should be enough to activate the row, don't have to read the entire row
		mram_read(attacker1, wram_cache, MAX_MRAM_WRITE_SIZE);
		mram_read(attacker2, wram_cache, MAX_MRAM_WRITE_SIZE);
	}

	uint32_t number_of_bitflips = 0;
	__dma_aligned uint8_t victim_output[ROW_SIZE];
	for (int i = 0; i < ROW_SIZE / MAX_MRAM_WRITE_SIZE; i++) {
		mram_read(victim + (i * MAX_MRAM_WRITE_SIZE), victim_output + (i * MAX_MRAM_WRITE_SIZE), MAX_MRAM_WRITE_SIZE);
	}

	for (int i = 0; i < ROW_SIZE; i++) {
		if (victim_output[i] != 0x55) {
			number_of_bitflips++;
		}
	}

	return number_of_bitflips;
}

uint32_t maccess_t(__mram_ptr void *address1, __mram_ptr void *address2) {
        __dma_aligned uint64_t buffer;
        perfcounter_config(COUNT_CYCLES, true);
        mram_read(address1, &buffer, sizeof(buffer));
        mram_read(address2, &buffer, sizeof(buffer));
        uint32_t cycles = perfcounter_get();
        return cycles;
}
