#include<stdio.h>
#include "../device.h"

// addresses sent by host
__mram_noinit hammer_address addresses[sizeof(hammer_address) * SAMPLES];

int main() {
	// allocate large wram/mram memory
	__mram_ptr void *mem_mram = allocate_mram_mem();
	
	uint64_t flips = 0;
	// pick 3 random addresses and hammer
	for (int i = 0; i < SAMPLES; i++) {
		__mram_ptr void *victim = mem_mram + addresses[i].victim;			
		__mram_ptr void *attacker1 = mem_mram + addresses[i].attacker1;			
		__mram_ptr void *attacker2 = mem_mram + addresses[i].attacker2;
		printf("Picked base: %p, victim: %p, attacker1: %p, attacker2: %p\n", mem_mram, victim, attacker1, attacker2);	
		flips += hammer(victim, attacker1, attacker2);
	}	
	

	printf("Detected %ld bitflips on avg across %d samples\n", flips / SAMPLES, SAMPLES);
	
	return 0;
}
