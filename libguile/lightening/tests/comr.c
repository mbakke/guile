#include "test.h"

static void
run_test(jit_state_t *j, uint8_t *arena_base, size_t arena_size)
{
  jit_begin(j, arena_base, arena_size);
  jit_load_args_1(j, jit_operand_gpr (JIT_OPERAND_ABI_INTMAX, JIT_R0));

  jit_comr(j, JIT_R0, JIT_R0);
  jit_retr(j, JIT_R0);

  intmax_t (*f)(intmax_t) = jit_end(j, NULL);

#if __WORDSIZE == 32
  ASSERT(f(0) == 0xffffffff);
  ASSERT(f(1) == 0xfffffffe);
  ASSERT(f(0xffffffff) == 0);
  ASSERT(f(0x80000000) == 0x7fffffff);
  ASSERT(f(0x7fffffff) == 0x80000000);
  ASSERT(f(0x80000001) == 0x7ffffffe);
#else
  ASSERT(f(0) == 0xffffffffffffffff);
  ASSERT(f(1) == 0xfffffffffffffffe);
  ASSERT(f(0xffffffff) == 0xffffffff00000000);
  ASSERT(f(0x80000000) == 0xffffffff7fffffff);
  ASSERT(f(0x7fffffff) == 0xffffffff80000000);
  ASSERT(f(0x80000001) == 0xffffffff7ffffffe);
  ASSERT(f(0xffffffffffffffff) == 0);
  ASSERT(f(0x8000000000000000) == 0x7fffffffffffffff);
  ASSERT(f(0x7fffffffffffffff) == 0x8000000000000000);
  ASSERT(f(0x8000000000000001) == 0x7ffffffffffffffe);
#endif
}

int
main (int argc, char *argv[])
{
  return main_helper(argc, argv, run_test);
}