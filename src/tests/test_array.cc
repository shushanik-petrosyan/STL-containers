#include <array>

#include "tests_init.h"

TEST(arrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(arrayTest, InitListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }
}

// Вынесем код, который вызывает исключение, в отдельную функцию.
void CreateArrayWithTooManyElements() {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5, 7, 8};
}

TEST(arrayTest, InitListConstructor_break) {
  EXPECT_THROW(CreateArrayWithTooManyElements(), std::length_error);
}

TEST(arrayTest, CopyConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrCopy(arr);

  EXPECT_EQ(arrCopy.size(), 5);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arrCopy[i], arr[i]);
  }
}

TEST(arrayTest, MoveConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrMoved(std::move(arr));
  EXPECT_EQ(arrMoved.size(), 5);
  for (size_t i = 0; i < arrMoved.size(); ++i) {
    EXPECT_EQ(arrMoved[i], static_cast<int>(i) + 1);
  }
}

TEST(arrayTest, Begin) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(arr[0], 10);
}

TEST(arrayTest, End) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.end();
  auto beginIt = arr.begin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(arrayTest, CBegin) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.cbegin();
  EXPECT_EQ(*it, 1);
}

TEST(arrayTest, CEnd) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.cend();
  auto beginIt = arr.cbegin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(arrayTest, At_ValidIndex) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.at(2);
  EXPECT_EQ(value, 3);
}

TEST(arrayTest, At_OutOfBounds) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(arrayTest, ConstAt_ValidIndex) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.at(2);
  EXPECT_EQ(value, 3);
}

TEST(arrayTest, ConstAt_OutOfBounds) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(arrayTest, Front) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.front();
  EXPECT_EQ(value, 1);
}

TEST(arrayTest, Back) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.back();
  EXPECT_EQ(value, 5);
}

TEST(arrayTest, ConstFront) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.front();
  EXPECT_EQ(value, 1);
}

TEST(arrayTest, ConstBack) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int value = arr.back();
  EXPECT_EQ(value, 5);
}

TEST(arrayTest, OperatorBracketConst) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  ASSERT_EQ(arr[0], 1);
  ASSERT_EQ(arr[1], 2);
  ASSERT_EQ(arr[2], 3);
  ASSERT_EQ(arr[3], 4);
  ASSERT_EQ(arr[4], 5);

  const s21::array<int, 5>& const_arr = arr;
  ASSERT_EQ(const_arr[0], 1);
  ASSERT_EQ(const_arr[1], 2);
  ASSERT_EQ(const_arr[2], 3);
  ASSERT_EQ(const_arr[3], 4);
  ASSERT_EQ(const_arr[4], 5);
}

TEST(arrayTest, Data) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  ASSERT_EQ(arr.data(), &arr[0]);

  const s21::array<int, 5>& const_arr = arr;
  ASSERT_EQ(const_arr.data(), &const_arr[0]);
}

TEST(arrayTest, Empty_NonEmptyarray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_FALSE(arr.empty());
}

TEST(arrayTest, Empty_Emptyarray) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(arrayTest, Size_NonEmptyarray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
}

TEST(arrayTest, Size_Emptyarray) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.size(), 0);
}

TEST(arrayTest, MaxSize) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(arrayTest, Swap) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1.swap(arr2);

  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }

  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], static_cast<int>(i) + 1);
  }
}

TEST(arrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(10);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 10);
  }
}

TEST(arrayTest, CopyAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1 = arr2;

  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(arrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};

  arr1 = std::move(arr2);

  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }
}

TEST(arrayTest, OperatorBracket) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }

  arr[2] = 10;
  EXPECT_EQ(arr[2], 10);
}
