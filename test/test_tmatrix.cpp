#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)//скопированная матрица равна исходной
{
	TDynamicMatrix<int> m1(2);
	m1[0][1] = 1;
	TDynamicMatrix<int> m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)//скопированная матрица имеет свою собственную память
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(m1);
	EXPECT_EQ(&m1, &m2);
}

TEST(TDynamicMatrix, can_get_size)
{

	TDynamicMatrix<int> m1(2);
	EXPECT_EQ(2, m1.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)//можно установить и узнать элемент
{
	TDynamicMatrix<int> m1(2);
	m1[0][1] = 1;
	EXPECT_EQ(1,m1[0][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m1(2);
	ASSERT_ANY_THROW(m1[-1][1]=1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m1(2);
	ASSERT_ANY_THROW(m1[0][2] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)//может присвоить матрицу самому себе
{
	TDynamicMatrix<int> m1(2);
	ASSERT_NO_THROW(m1=m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)//можно приравнять матрицы однго размера
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);
	m1[1][1] = 5;
	m1 = m2;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)//назначить оператору изменение размера матрицы
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	m1[1][1] = 5;
	m1 = m2;
	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)//сравнение равных матриц возвращает значение true
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);
	m1[1][1] = 2;
	m2[1][1] = 2;
	ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)//сравнение одной и той же матрицы возвращает значение truе
{
	TDynamicMatrix<int> m1(2);
	ASSERT_TRUE(m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	ASSERT_NO_THROW(m1!= m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2); m1[0][0] = 1; m1[0][1] = 2;
	TDynamicMatrix<int> m2(2); m2[0][0] = 1; m2[0][1] = 2;
	TDynamicMatrix<int> m3(2); m3[0][0] = 2; m3[0][1] = 4;
	TDynamicMatrix<int> m4(2); m4 = m1 + m2;
	EXPECT_EQ(m3,m4);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2); 
	TDynamicMatrix<int> m2(3); 
	ASSERT_ANY_THROW(m1+m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2); m1[0][0] = 1; m1[0][1] = 2;
	TDynamicMatrix<int> m2(2); m2[0][0] = 1; m2[0][1] = 2;
	TDynamicMatrix<int> m3(2); m3[0][0] = 0; m3[0][1] = 0;
	TDynamicMatrix<int> m4(2); m4 = m1 - m2;
	EXPECT_EQ(m3, m4);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	ASSERT_ANY_THROW(m1 - m2);
}

