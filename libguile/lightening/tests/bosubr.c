#include "test.h"

static const intmax_t overflowed = 0xcabba9e5;

static void
run_test(jit_state_t *j, uint8_t *arena_base, size_t arena_size)
{
  jit_begin(j, arena_base, arena_size);
  jit_load_args_2(j, jit_operand_gpr (JIT_OPERAND_ABI_INTMAX, JIT_R0),
                  jit_operand_gpr (JIT_OPERAND_ABI_INTMAX, JIT_R1));

  jit_reloc_t r = jit_bosubr(j, JIT_R0, JIT_R1);
  jit_retr(j, JIT_R0);
  jit_patch_here(j, r);
  jit_movi(j, JIT_R0, overflowed);
  jit_retr(j, JIT_R0);

  intmax_t (*f)(intmax_t, intmax_t) = jit_end(j, NULL);

  ASSERT(f(0, 0) == 0);
  ASSERT(f(0, 1) == -1);
  ASSERT(f(1, 1) == 0);
  ASSERT(f(1, -1) == 2);

#if __WORDSIZE == 32
  ASSERT(f(0xffffffff, 0xffffffff) == 0);
  ASSERT(f(0x7fffffff, 0) == 0x7fffffff);
  ASSERT(f(0x7fffffff, 1) == 0x7ffffffe);
  ASSERT(f(0x7fffffff, 0x7fffffff) == 0);
  ASSERT(f(0x80000000, 0x7fffffff) == overflowed);
  ASSERT(f(0x7fffffff, 0x80000000) == overflowed);
  ASSERT(f(0x80000000, 0x80000000) == 0);
#else
  ASSERT(f(0x7fffffffffffffff, 0x7fffffffffffffff) == 0);
  ASSERT(f(0x7fffffffffffffff, 0x8000000000000000) == overflowed);
  ASSERT(f(0x8000000000000000, 0x7fffffffffffffff) == overflowed);
  ASSERT(f(0x8000000000000000, 0x8000000000000000) == 0);
#endif
}

int
main (int argc, char *argv[])
{
  return main_helper(argc, argv, run_test);
}