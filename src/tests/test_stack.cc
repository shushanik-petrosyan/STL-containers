#include <stack>

#include "tests_init.h"

namespace {
TEST(stack, сonstructorDefault) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack, сonstructorInitializeList) {
  s21::stack<int> s21_stack_1 = {1, 2, 3, 4};
  for (int i = 4; i > 0; i--) {
    EXPECT_EQ(s21_stack_1.top(), i);
    s21_stack_1.pop();
  }
}

TEST(stack, constructorCopy) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::stack<char> s21_stack_2 = s21_stack_1;

  EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());
  EXPECT_EQ(s21_stack_1.size(), 4);
  EXPECT_EQ(s21_stack_1.top(), s21_stack_2.top());
}

TEST(stack, sizeAndTopAfterCopy) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::stack<char> s21_stack_2 = s21_stack_1;

  EXPECT_EQ(s21_stack_1.size(), 4);
  EXPECT_EQ(s21_stack_1.top(), 'd');
}

TEST(stack, popOperations) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};

  s21_stack_1.pop();
  EXPECT_EQ(s21_stack_1.top(), 'c');
  s21_stack_1.pop();
  EXPECT_EQ(s21_stack_1.top(), 'b');
  s21_stack_1.pop();
  EXPECT_EQ(s21_stack_1.top(), 'a');
}

TEST(stack, moveConstructor) {
  s21::stack<int> s1 = {1, 2, 3, 4};
  s21::stack<int> s2(std::move(s1));

  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 4);
  EXPECT_EQ(s2.top(), 4);
  s2.pop();
  EXPECT_EQ(s2.top(), 3);
}

TEST(stack, moveAssignment) {
  s21::stack<int> s1 = {1, 2, 3, 4};
  s21::stack<int> s2 = std::move(s1);

  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 4);
  EXPECT_EQ(s2.top(), 4);
  s2.pop();
  EXPECT_EQ(s2.top(), 3);
}

TEST(stack, pushTop) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);

  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack, pushSize) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(stack, pushEmptyState) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack, popAfterInitialPush) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);

  s21_stack.pop();
  std_stack.pop();

  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack, popAfterPushAndPop) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  s21_stack.pop();
  std_stack.pop();
  s21_stack.pop();
  std_stack.pop();

  EXPECT_TRUE(s21_stack.empty());
  EXPECT_TRUE(std_stack.empty());
}

TEST(stack, popAfterRepush) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  s21_stack.pop();
  std_stack.pop();
  s21_stack.pop();
  std_stack.pop();
  s21_stack.push(15);
  s21_stack.push(10);
  std_stack.push(15);
  std_stack.push(10);
  s21_stack.pop();
  std_stack.pop();

  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack, initialState) {
  s21::stack<std::string> s21_stack_1 = {"The", "sun", "Is", "Far", "Away"};
  s21::stack<std::string> s21_stack_2 = {"It", "Goes", "In", "Circles"};
  s21::stack<std::string> s21_stack_3 = {"The", "sun", "Is", "Far", "Away"};
  s21::stack<std::string> s21_stack_4 = {"It", "Goes", "In", "Circles"};

  EXPECT_EQ(s21_stack_1.size(), s21_stack_3.size());
  EXPECT_EQ(s21_stack_2.size(), s21_stack_4.size());
}

TEST(stack, swapOperation) {
  s21::stack<std::string> s21_stack_1 = {"The", "sun", "Is", "Far", "Away"};
  s21::stack<std::string> s21_stack_2 = {"It", "Goes", "In", "Circles"};
  s21::stack<std::string> s21_stack_3 = {"The", "sun", "Is", "Far", "Away"};
  s21::stack<std::string> s21_stack_4 = {"It", "Goes", "In", "Circles"};

  s21_stack_1.swap(s21_stack_2);

  EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
}
TEST(stack, swapAndPopOperationstack1) {
  s21::stack<std::string> s21_stack_1 = {"The", "sun", "Is", "Far", "Away"};
  s21::stack<std::string> s21_stack_2 = {"It", "Goes", "In", "Circles"};
  s21::stack<std::string> s21_stack_4 = {"It", "Goes", "In", "Circles"};

  s21_stack_1.swap(s21_stack_2);

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_4.top());
    s21_stack_1.pop();
    s21_stack_4.pop();
  }
}

TEST(stack, swapAndPopOperationstack2) {
  s21::stack<std::string> s21_stack_1 = {"The", "sun", "Is", "Far", "Away"};
  s21::stack<std::string> s21_stack_2 = {"It", "Goes", "In", "Circles"};
  s21::stack<std::string> s21_stack_3 = {"The", "sun", "Is", "Far", "Away"};

  s21_stack_1.swap(s21_stack_2);

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_2.top(), s21_stack_3.top());
    s21_stack_2.pop();
    s21_stack_3.pop();
  }
}

TEST(stack, insertManyFront) {
  s21::stack<int> s1({1});
  std::stack<int> s2({1, 2, 3, 4});

  s1.insert_many_front(2, 3, 4);

  while (!s1.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    s1.pop();
    s2.pop();
  }
}

}  // namespace