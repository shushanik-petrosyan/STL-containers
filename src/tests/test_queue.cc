#include <queue>

#include "tests_init.h"

class Point {
 public:
  Point(double x = 0, double y = 0) : x_(x), y_(y) {}
  bool operator<(const Point& other) const {
    return (x_ * x_ + y_ * y_) < (other.x_ * other.x_ + other.y_ * other.y_);
  }
  bool operator==(const Point& other) const {
    return x_ == other.x_ && y_ == other.y_;
  }

 private:
  double x_, y_;
};

TEST(queue, constructorDefault) {
  EXPECT_NO_THROW(s21::queue<int>());
  EXPECT_NO_THROW(s21::queue<char>());
  EXPECT_NO_THROW(s21::queue<double>());
  EXPECT_NO_THROW(s21::queue<s21::queue<int>>());
  EXPECT_NO_THROW(s21::queue<Point>());
}

TEST(queue, constructorInitializer) {
  EXPECT_NO_THROW(s21::queue<int>({0, 1, 2, 3, 3, 4, 2, 1}));
  EXPECT_NO_THROW(s21::queue<char>({'1', 'a', '[', '\n'}));
  EXPECT_NO_THROW(s21::queue<double>({12.34, 56.78, 0, -346.76}));
  EXPECT_NO_THROW(s21::queue<Point>({Point(1, 2), Point(12, 4), Point()}));
}

TEST(queue, constructorCopy) {
  s21::queue<int> queue_int({0, 1, 2, 3});
  EXPECT_NO_THROW(s21::queue<int> queue_other_int = queue_int);

  s21::queue<char> queue_char({'1', 'a', '[', '\t'});
  EXPECT_NO_THROW(s21::queue<char> queue_other_char = queue_char);

  s21::queue<double> queue_double({12.34, 45, 9348.2, 0.0, 23});
  EXPECT_NO_THROW(s21::queue<double> queue_other_double = queue_double);

  s21::queue<Point> queue_point({Point(1, 2), Point(12, 4), Point()});
  EXPECT_NO_THROW(s21::queue<Point> queue_other_point = queue_point);
}

TEST(queue, constructorMove) {
  s21::queue<int> queue_int({0, 1, 2, 3});
  EXPECT_NO_THROW(s21::queue<int> queue_other_int = std::move(queue_int));

  s21::queue<char> queue_char({'1', 'a', '[', '\t'});
  EXPECT_NO_THROW(s21::queue<char> queue_other_char = std::move(queue_char));

  s21::queue<double> queue_double({12.34, 45, 9348.2, 0.0, 23});
  EXPECT_NO_THROW(s21::queue<double> queue_other_double =
                      std::move(queue_double));

  s21::queue<Point> queue_point({Point(1, 2), Point(12, 4), Point()});
  EXPECT_NO_THROW(s21::queue<Point> queue_other_point = std::move(queue_point));
}

TEST(queue, capacityEmpty) {
  EXPECT_EQ((s21::queue<int>()).empty(), true);
  EXPECT_EQ((s21::queue<char>()).empty(), true);
  EXPECT_EQ((s21::queue<double>()).empty(), true);
  EXPECT_EQ((s21::queue<s21::list<int>>()).empty(), true);
  EXPECT_EQ((s21::queue<s21::queue<int>>()).empty(), true);
  EXPECT_EQ((s21::queue<Point>()).empty(), true);

  EXPECT_EQ((s21::queue<int>({0, 1, 2, 3})).empty(), false);
  EXPECT_EQ((s21::queue<char>({'1', 'a', '[', '\n'})).empty(), false);
  EXPECT_EQ((s21::queue<double>({12.34, 56.78, 0, -346.76})).empty(), false);
  EXPECT_EQ((s21::queue<Point>({Point(1, 2), Point(12, 4), Point()})).empty(),
            false);
}

TEST(queue, capacitySize) {
  EXPECT_EQ((s21::queue<int>()).size(), (s21::queue<int>::size_type)0);
  EXPECT_EQ((s21::queue<char>()).size(), (s21::queue<char>::size_type)0);
  EXPECT_EQ((s21::queue<double>()).size(), (s21::queue<double>::size_type)0);
  EXPECT_EQ((s21::queue<s21::list<int>>()).size(),
            (s21::queue<s21::list<int>>::size_type)0);
  EXPECT_EQ((s21::queue<s21::queue<int>>()).size(),
            (s21::queue<s21::queue<int>>::size_type)0);
  EXPECT_EQ((s21::queue<Point>()).size(), (s21::queue<Point>::size_type)0);

  EXPECT_EQ((s21::queue<int>({0, 1, 2, 3})).size(),
            (s21::queue<int>::size_type)4);
  EXPECT_EQ((s21::queue<char>({'1', 'a', '[', '\n'})).size(),
            (s21::queue<char>::size_type)4);
  EXPECT_EQ((s21::queue<double>({12.34, 56.78, 0, -346.76})).size(),
            (s21::queue<double>::size_type)4);
  EXPECT_EQ((s21::queue<Point>({Point(1, 2), Point(12, 4), Point()})).size(),
            (s21::queue<Point>::size_type)3);
}

TEST(queue, modifiersPushPopSwap) {
  for (int i = 0; i < 100; ++i) {
    int q;
    s21::queue<int> test, test_other;
    std::queue<int> check, check_other;
    for (int n = 0; n < rand() % 100; ++n) {
      q = rand() % 20;
      if (test.empty()) {
        test.push(q);
        check.push(q);
      } else {
        if (rand() % 2) {
          test.push(q);
          check.push(q);
        } else {
          test.pop();
          check.pop();
        }
      }
      if (!test.empty()) {
        EXPECT_EQ(test.front(), check.front());
        EXPECT_EQ(test.back(), check.back());
        EXPECT_EQ(test.size(), check.size());
      }
      test.swap(test_other);
      check.swap(check_other);
    }
  }
}

TEST(queue, insertManyBack) {
  s21::queue<int> s21_queue({1});
  std::queue<int> std_queue({1, -1, -23, 4, 1, 5, 6, 4, -1, -1});

  s21_queue.insert_many_back(-1, -23, 4, 1, 5, 6, 4, -1, -1);

  while (!s21_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    s21_queue.pop();
    std_queue.pop();
  }
}