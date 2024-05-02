#include "CUnit/Basic.h"
#include "ft_printf.h"

void	test_ft_integer(void)
{
	CU_ASSERT_EQUAL(ft_integer(0), 1);
	CU_ASSERT_EQUAL(ft_integer(-2147483648), 11);
	CU_ASSERT_EQUAL(ft_integer(12345), 5);
	CU_ASSERT_EQUAL(ft_integer(-12345), 6);
}

void	test_ft_unsigned_int(void)
{
	CU_ASSERT_EQUAL(ft_unsigned_int(0), 1);
	CU_ASSERT_EQUAL(ft_unsigned_int(12345), 5);
	CU_ASSERT_EQUAL(ft_unsigned_int(4294967295), 10);
	// Maximum value of unsigned int
}

void	test_ft_string(void)
{
	CU_ASSERT_EQUAL(ft_string("mert"), 4);
	CU_ASSERT_EQUAL(ft_string(""), 0);
	CU_ASSERT_EQUAL(ft_string("\0"), 0);
	CU_ASSERT_EQUAL(ft_string("2234"), 4);
	CU_ASSERT_EQUAL(ft_string("1"), 1);
	CU_ASSERT_EQUAL(ft_string("xcv--l3467"), 10);
}

void	test_ft_hexadecimal(void)
{
	CU_ASSERT_EQUAL(ft_hexadecimal(123, 'X'), 2);
	CU_ASSERT_EQUAL(ft_hexadecimal(0, 'x'), 1);
	// Diğer test durumları...
}

void	test_ft_pointer(void)
{
	int	a;

	a = 10;
	CU_ASSERT_EQUAL(ft_pointer((unsigned long)&a, 1), 3);
	CU_ASSERT_EQUAL(ft_pointer(0, 1), 5);
	// Diğer test durumları...
}
int	main(void)
{
	CU_pSuite	suite1;

	CU_initialize_registry();
	suite1 = CU_add_suite("ft_printf_utils_test", 0, 0);
	CU_add_test(suite1, "test_ft_integer", test_ft_integer);
	CU_add_test(suite1, "test_ft_unsigned_int", test_ft_unsigned_int);
	CU_add_test(suite1, "test_ft_string", test_ft_string);
	CU_add_test(suite1, "test_ft_hexadecimal", test_ft_hexadecimal);
	CU_add_test(suite1, "test_ft_pointer", test_ft_pointer);
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return (0);
}

// TDD öğrennn
