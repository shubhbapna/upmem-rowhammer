#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include "shared.h"

__mram_ptr void *allocate_mram_mem();
uint32_t hammer(__mram_ptr void *victim, __mram_ptr void *attacker1, __mram_ptr void *attacker2);
uint32_t maccess_t(__mram_ptr void *address1, __mram_ptr void *address2);
