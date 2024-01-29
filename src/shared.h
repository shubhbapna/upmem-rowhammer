// Size of allocated buffer = 64 kb
#define BUFFER_SIZE_KB 65536

// Size of DRAM row (1 bank)
#define ROW_SIZE (8192)

// max size for wram to mram writes
#define MAX_MRAM_WRITE_SIZE 2048

// 80% of WRAM capacity
#define WRAM_BUFFER (BUFFER_SIZE_KB * 0.8)
#define WRAM_NUM_ROWS (BUFFER_SIZE_KB / ROW_SIZE)

// 87.5% of MRAM capactity (7000 rows)
#define MRAM_NUM_ROWS (BUFFER_SIZE_KB * 1024 / ROW_SIZE)
#define MRAM_BUFFER ((MRAM_NUM_ROWS - 1000) * ROW_SIZE)

// Number of hammers to perform per iteration: hammer 10x refresh period
#define HAMMERS_PER_ITER 4000000

// number of sample for measuring bank latency
#define SAMPLES 8

typedef struct hammer_address {
        int victim;
        int attacker1;
        int attacker2;
} hammer_address;
