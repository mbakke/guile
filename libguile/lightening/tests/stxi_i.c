#include "test.h"

static uint32_t data[] = { 0x12121212, 0x00000000, 0x34343434 };

static void
run_test(jit_state_t *j, uint8_t *arena_base, size_t arena_size)
{
  jit_begin(j, arena_base, arena_size);
  jit_load_args_2(j, jit_operand_gpr (JIT_OPERAND_ABI_INTMAX, JIT_R2),
                  jit_operand_gpr (JIT_OPERAND_ABI_INT32, JIT_R1));

  jit_stxi_i(j, (uintptr_t)data, JIT_R2, JIT_R1);
  jit_ret(j);

  void (*f)(intmax_t, int32_t) = jit_end(j, NULL);

  ASSERT(data[0] == 0x12121212);
  ASSERT(data[1] == 0x00);
  ASSERT(data[2] == 0x34343434);
  f(4, -1);
  ASSERT(data[0] == 0x12121212);
  ASSERT(data[1] == 0xffffffff);
  ASSERT(data[2] == 0x34343434);
}

int
main (int argc, char *argv[])
{
  return main_helper(argc, argv, run_test);
}