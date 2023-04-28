#include <../src/libgeometry/geometry.h>
#include <../thirdparty/ctest.h>

CTEST(parsing_suite, input_initial)
{
  //Given
  size_t p = 7;
  string line = "circle(2.5 2.4, 3)";
  int circleCounter = 0;
  double circleArray[100][100];
  
  //When
  const int result = parsing(p, line, circleCounter, circleArray);
  
  //Then
  const int expected = 1;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(parsing_suite, parsing_initial)
{
  //Given
  size_t p = 7;
  int j = 0;
  string line = "circle(2.5 2.4, 3)";
  int circleCounter = 0;
  double circleArray[100][100];
  
  //When
  const int result = checkNumber(p, j, line, circleCounter, circleArray);
  
  //Then
  const int expected = 1;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, calculate_initial)
{
  //Given
  int circleCounter = 0;
  double circleArray[100][100];
  
  //When
  const int result = circleCalculation(circleCounter, circleArray);
  
  //Then
  const int expected = 0;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(parsing_suite, print_initial)
{
  //Given
  int I = 0;
  double a[100][100];
  
  //When
  const int result = print(I, a);
  
  //Then
  const int expected = 0;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(parsing_suite, input_situational)
{
  //Given
  size_t p = 7;
  string line = "circle(2.5 2.4, 3)";
  int circleCounter = 1;
  double circleArray[100][100];
  
  //When
  const int result = parsing(p, line, circleCounter, circleArray);
  
  //Then
  const int expected = 1;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(parsing_suite, parsing_error)
{
  //Given
  size_t pointer = 7;
  int c = 1;
  string s = "circle(2 32, 1)";
  int c_index = 1;
  double A[100][100];
  
  //When
  const int result = checkNumber(pointer, c, s, c_index, A);
  
  //Then
  const int expected = 1;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, calculate_fail_test)
{
  //Given
  int counter = 1;
  double Array[100][100];
  
  //When
  const int result = circleCalculation(counter, Array);
  
  //Then
  const int expected = 0;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(parsing_suite, print_Array_fail)
{
  //Given
  double a[100][100];
  int temp = 0;
  
  //When
  const int result = print(temp, a);
  
  //Then
  const int expected = 0;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(parsing_suite, input_error_exceed)
{
  //Given
  string line = "circle(10 0.4, 3)";
  size_t p = 7;
  int circleCounter = 1;
  double circleArray[100][100];
  
  //When
  const int result = parsing(p, line, circleCounter, circleArray);
  
  //Then
  const int expected = 1;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(parsing_suite, parsing_max)
{
  //Given
  double circleArray[100][100];
  size_t p = 7;
  int j = 1;
  int circleCounter = 1;
  string line = "circle(10 0.4, 3)";
  
  //When
  const int result = checkNumber(p, j, line, circleCounter, circleArray);
  
  //Then
  const int expected = 1;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, calculate_boundary_min)
{
  //Given
  int x_test = 0;
  double f[100][100];
  
  //When
  const int result = circleCalculation(x_test, f);
  
  //Then
  const int expected = 0;
  
  ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic_suite, calculate_boundary_max)
{
  //Given
  double y[100][100];
  int situational_i = 0;
  
  //When
  const int result = print(situational_i, y);
  
  //Then
  const int expected = 0;
  
  ASSERT_EQUAL(expected, result);
}
