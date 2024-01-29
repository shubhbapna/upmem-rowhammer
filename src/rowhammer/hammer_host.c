#include <assert.h>
#include <dpu.h>
#include <dpu_log.h>
#include <stdio.h>
#include <unistd.h>
#include "../shared.h"

#ifndef DPU_BINARY
#define DPU_BINARY "./hammer"
#endif

void generate_address(hammer_address* addresses) {
	for (int i = 0; i < SAMPLES; i++) {
		addresses[i].victim =  ROW_SIZE * (rand() % MRAM_NUM_ROWS);
		addresses[i].attacker1 = ROW_SIZE * (rand() % MRAM_NUM_ROWS);
		addresses[i].attacker2 = ROW_SIZE * (rand() % MRAM_NUM_ROWS);
	}
}

int main(void) {
  struct dpu_set_t set, dpu;

  DPU_ASSERT(dpu_alloc(1, NULL, &set));
  DPU_ASSERT(dpu_load(set, DPU_BINARY, NULL));
  
  // create SAMPLE sized 3-way tuple of random number for address generation in dpu
  hammer_address* addresses = malloc(sizeof(hammer_address) * SAMPLES);
  generate_address(addresses);
  DPU_FOREACH(set, dpu) {  
  	DPU_ASSERT(dpu_prepare_xfer(dpu, addresses));
  }
  DPU_ASSERT(dpu_push_xfer(set, DPU_XFER_TO_DPU, "addresses", 0, sizeof(hammer_address) * SAMPLES, DPU_XFER_DEFAULT));
  
  DPU_ASSERT(dpu_launch(set, DPU_SYNCHRONOUS));

  DPU_FOREACH(set, dpu) {
    DPU_ASSERT(dpu_log_read(dpu, stdout));
  }

  DPU_ASSERT(dpu_free(set));
  free(addresses);
  return 0;
}
