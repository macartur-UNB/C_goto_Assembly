#ifndef TEST_SYMBOL
#define TEST_SYMBOL
#include <CUnit/CUnit.h>


int
is_even (int x)
{
  return (x % 2 == 0);
}

void
test_is_even (void)
{
  CU_ASSERT(is_even(1)  == 0);
  CU_ASSERT(is_even(2)  == 1);
  CU_ASSERT(is_even(3)  == 0);
}

#endif
