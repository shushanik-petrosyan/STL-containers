

#include <set>

#include "tests_init.h"

TEST(method_multiset, constructor) {
  s21::multiset<int> a{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  s21::multiset<int> b(a);
  s21::multiset<int> c{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  auto it1 = b.begin();
  EXPECT_EQ(b.size(), c.size());
  for (auto it = c.begin(); it != c.end(); it++) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
  s21::multiset<int> d;
  d = std::move(a);
  auto it2 = d.begin();
  for (auto it = c.begin(); it != c.end(); it++) {
    EXPECT_EQ(*it, *it2);
    it2++;
  }
}

TEST(method_multiset, constructor2) {
  s21::multiset<int> a{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  s21::multiset<int> b(std::move(a));
  s21::multiset<int> c{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  auto it1 = b.begin();
  EXPECT_EQ(b.size(), c.size());
  for (auto it = c.begin(); it != c.end(); it++) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
  s21::multiset<int> d;
  d = std::move(b);
  auto it2 = d.begin();
  for (auto it = c.begin(); it != c.end(); it++) {
    EXPECT_EQ(*it, *it2);
    it2++;
  }
}

TEST(method_multiset, clear) {
  s21::multiset<int> a;
  std::multiset<int> b;
  a.clear();
  b.clear();
  EXPECT_EQ(*a.begin(), 0);
  EXPECT_EQ(*a.begin(), 0);
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.max_size(), b.max_size());
  a.insert(1);
  a.insert(1);
  a.insert(1);
  b.insert(1);
  b.insert(1);
  b.insert(1);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(*a.begin(), *b.begin());
  EXPECT_EQ(*a.begin(), *b.begin());
}

TEST(method_multiset, insert0) {
  s21::multiset<std::string> a{"clean", "add", "add", "is", "cat", "fox"};
  std::multiset<std::string> b{"clean", "add", "add", "is", "cat", "fox"};
  auto it1 = b.begin();
  for (auto it = a.begin(); it != a.end(); it++) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method_multiset, insert1) {
  s21::multiset<double> a{1.223, 32.234, 3.2, 1.2, 34.123, 3.908, 4.23};
  std::multiset<double> b{1.223, 32.234, 3.2, 1.2, 34.123, 3.908, 4.23};
  auto it1 = b.begin();
  for (auto it = a.begin(); it != a.end(); it++) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
  a.insert(123.3);
  b.insert(123.3);
  auto it2 = b.begin();
  for (auto it = a.begin(); it != a.end(); it++) {
    EXPECT_EQ(*it, *it2);
    it2++;
  }
}

TEST(method_multiset, insert2) {
  std::multiset<int> d;
  s21::multiset<std::multiset<int>> a1{d, d};
  std::multiset<std::multiset<int>> b1{d, d};
  auto it2 = a1.begin();
  for (auto it = b1.begin(); it != b1.end(); it++) {
    EXPECT_EQ(*it, *it2);
    it2++;
  }
}

TEST(method_multiset, erase) {
  s21::multiset<int> a;
  std::multiset<int> b;
  a.erase(a.begin());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(*a.begin(), 0);
  EXPECT_EQ(*a.begin(), 0);
  s21::multiset<int> c{1, 2, 3, 4, 4, 4, 4, 4};
  a = std::move(c);
  EXPECT_EQ(a.size(), 8);
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(*a.begin(), 1);
  // EXPECT_EQ(*a.begin(), 1);
}

TEST(method_multiset, swap) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  s21::multiset<int> b{1, 2, 2};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::multiset<int> d{1, 2, 2};
  a.swap(b);
  c.swap(d);
  auto it1 = a.begin();
  for (auto it = c.begin(); it != c.end(); it++) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
  auto it2 = b.begin();
  for (auto it3 = d.begin(); it3 != d.end(); it3++) {
    EXPECT_EQ(*it2, *it3);
    it2++;
  }
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
}

TEST(method_multiset, merge) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  s21::multiset<int> b{1, 2, 2};
  std::multiset<int> c{1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  a.merge(b);
  auto it1 = a.begin();
  for (auto it = c.begin(); it != c.end(); it++) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method_multiset, merge2) {
  s21::multiset<int> a;
  s21::multiset<int> b;
  std::multiset<int> c;
  a.merge(b);
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(a.empty(), c.empty());
  EXPECT_EQ(*a.begin(), 0);
  EXPECT_EQ(*a.begin(), 0);
}

TEST(method_multiset, find) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  EXPECT_EQ(*a.find(2), *c.find(2));

  EXPECT_THROW(
      {
        auto it = a.find(10);
        *it;
      },
      std::out_of_range);

  // EXPECT_EQ(*a.find(10), 0);
  EXPECT_EQ(*a.find(5), *c.find(5));
}

TEST(method_multiset, contains) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  s21::multiset<int> c;
  EXPECT_EQ(a.contains(1), true);
  EXPECT_EQ(a.contains(10), false);
  EXPECT_EQ(c.contains(10), false);
}

TEST(method_multiset, lower_bound) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};

  EXPECT_EQ(*a.lower_bound(1), *c.lower_bound(1));

  EXPECT_THROW(
      {
        auto it = a.lower_bound(6);
        *it;
      },
      std::out_of_range);

  EXPECT_THROW(
      {
        auto it = a.lower_bound(0);
        *it;
      },
      std::out_of_range);
}

TEST(method_multiset, lower_bound2) {
  s21::multiset<int> a;
  std::multiset<int> c;

  EXPECT_THROW(
      {
        auto it = a.lower_bound(1);
        *it;
      },
      std::out_of_range);
}

TEST(method_multiset, upper_bound) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  EXPECT_EQ(*a.upper_bound(1), *c.upper_bound(1));

  EXPECT_THROW(
      {
        auto it = a.upper_bound(5);
        *it;
      },
      std::out_of_range);

  EXPECT_THROW(
      {
        auto it = a.upper_bound(0);
        *it;
      },
      std::out_of_range);

  EXPECT_THROW(
      {
        auto it = a.upper_bound(-1);
        *it;
      },
      std::out_of_range);
}

TEST(method_multiset, upper_bound2) {
  s21::multiset<int> a;
  std::multiset<int> c;

  EXPECT_THROW(
      {
        auto it = a.upper_bound(1);
        *it;
      },
      std::out_of_range);
}

TEST(method_multiset, equal_range) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> b0 =
      a.equal_range(2);
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> d0 =
      c.equal_range(2);
  EXPECT_EQ(*b0.first, *d0.first);
  EXPECT_EQ(*b0.second, *d0.second);
  while (b0.first != b0.second && d0.first != d0.second) {
    EXPECT_EQ(*b0.first, *d0.first);
    b0.first++;
    d0.first++;
  }
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> b1 =
      a.equal_range(4);
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> d1 =
      c.equal_range(4);
  EXPECT_EQ(*b1.first, *d1.first);
  EXPECT_EQ(*b1.second, *d1.second);
  while (b1.first != b1.second && d1.first != d1.second) {
    EXPECT_EQ(*b1.first, *d1.first);
    b1.first++;
    d1.first++;
  }
}

TEST(method_multiset, count) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5};

  EXPECT_EQ(a.count(1), c.count(1));
  EXPECT_EQ(a.count(2), c.count(2));
  EXPECT_EQ(a.count(3), c.count(3));
  EXPECT_EQ(a.count(4), c.count(4));
  EXPECT_EQ(a.count(5), c.count(5));
}

// Тест на insert_many с уникальными элементами
TEST(MultiSetTest, InsertMany_UniqueElements) {
  s21::multiset<int> my_multiset;

  // Вставка множества уникальных элементов
  s21::vector<std::pair<s21::multiset<int>::iterator, bool>> result =
      my_multiset.insert_many(1, 2, 3, 4, 5);

  // Проверка на успешную вставку всех элементов
  for (const auto& res : result) {
    EXPECT_TRUE(res.second);
  }

  // Проверка размера мультимножества
  EXPECT_EQ(my_multiset.size(), 5);
  // Проверка содержимого мультимножества
  EXPECT_EQ(my_multiset.count(1), 1);
  EXPECT_EQ(my_multiset.count(2), 1);
  EXPECT_EQ(my_multiset.count(3), 1);
  EXPECT_EQ(my_multiset.count(4), 1);
  EXPECT_EQ(my_multiset.count(5), 1);
}

// Тест на insert_many с дубликатами
TEST(MultiSetTest, InsertMany_WithDuplicates) {
  s21::multiset<int> my_multiset;

  // Вставка множества элементов, включая дубликаты
  s21::vector<std::pair<s21::multiset<int>::iterator, bool>> result =
      my_multiset.insert_many(1, 2, 2, 3, 4, 1);

  // Проверка на успешную вставку уникальных элементов
  EXPECT_TRUE(result[0].second);
  EXPECT_TRUE(result[1].second);
  EXPECT_TRUE(result[2].second);
  EXPECT_TRUE(result[3].second);
  EXPECT_TRUE(result[4].second);
  EXPECT_TRUE(result[5].second);

  // Проверка размера мультимножества
  EXPECT_EQ(my_multiset.size(), 6);

  // Проверка содержимого мультимножества
  EXPECT_EQ(my_multiset.count(1), 2);
  EXPECT_EQ(my_multiset.count(2), 2);
  EXPECT_EQ(my_multiset.count(3), 1);
  EXPECT_EQ(my_multiset.count(4), 1);
}

// Тест на у брата левый ребенок красный, правый любой (удаляемый узел слева)
TEST(MultiSetTest, RBTree_del) {
  s21::multiset<int> my_multiset;
  my_multiset.insert(20);
  my_multiset.insert(3);
  my_multiset.insert(55);
  my_multiset.insert(25);
  my_multiset.erase(my_multiset.begin());
  EXPECT_EQ(*(my_multiset.begin()), 20);
}

// Тест у брата правый ребенок красный, левый любой (удаляемый узел справа)
TEST(MultiSetTest, RBTree_del2) {
  s21::multiset<int> my_multiset;
  my_multiset.insert(20);
  my_multiset.insert(3);
  my_multiset.insert(55);
  my_multiset.insert(10);
  my_multiset.erase(--my_multiset.end());
  EXPECT_EQ(*(--my_multiset.end()), 20);
}

TEST(MultiSetTest, RBTree_copy_empty) {
  s21::multiset<int> my_multiset;
  s21::multiset<int> my_multiset2(my_multiset);
  EXPECT_EQ(my_multiset2.size(), my_multiset.size());
}

// 561 строчка для поворота вправо
TEST(MultiSetTest, RBTree_right_rotate) {
  s21::multiset<int> my_multiset;
  my_multiset.insert(50);
  my_multiset.insert(100);
  my_multiset.insert(50);
  my_multiset.insert(44);
  my_multiset.insert(56);
  my_multiset.insert(52);
  my_multiset.insert(5);
  my_multiset.insert(4);
  my_multiset.insert(3);
  my_multiset.insert(2);
  my_multiset.insert(2);
  my_multiset.insert(1);
  my_multiset.insert(150);
  my_multiset.insert(198);
  EXPECT_EQ(*(--my_multiset.end()), 198);
}

// оператор ++ 97 строка
TEST(MultiSetTest, RBTree_increment) {
  s21::multiset<int> my_multiset;
  my_multiset.insert(50);
  my_multiset.insert(100);
  my_multiset.insert(50);
  my_multiset.insert(44);
  my_multiset.insert(56);
  my_multiset.insert(52);
  my_multiset.insert(5);
  my_multiset.insert(4);
  my_multiset.insert(3);
  my_multiset.insert(2);
  my_multiset.insert(2);
  my_multiset.insert(1);
  my_multiset.insert(150);
  my_multiset.insert(198);
  auto it = my_multiset.end();
  it++;
  EXPECT_EQ(*(it), *(my_multiset.begin()));
}

// оператор -- постфикс 97 строка
TEST(MultiSetTest, RBTree_decrement_post) {
  s21::multiset<int> my_multiset;
  my_multiset.insert(50);
  my_multiset.insert(100);
  my_multiset.insert(50);
  my_multiset.insert(44);
  my_multiset.insert(56);
  my_multiset.insert(52);
  my_multiset.insert(5);
  my_multiset.insert(4);
  my_multiset.insert(3);
  my_multiset.insert(2);
  my_multiset.insert(2);
  my_multiset.insert(1);
  my_multiset.insert(150);
  my_multiset.insert(198);
  auto it = my_multiset.end();
  it--;
  it--;
  EXPECT_EQ(*(it), 150);
  it--;
  EXPECT_EQ(*(it), 100);
  it--;
  EXPECT_EQ(*(it), 56);
}

TEST(MultiSetTest, RBtree_hed_minus) {
  s21::multiset<int> my_multiset;
  my_multiset.insert(77);
  auto it = my_multiset.begin();

  EXPECT_EQ(*(++it), 77);
  EXPECT_EQ(*(--it), 77);
}

// Тест на insert_many с пустым вызовом
TEST(MultiSetTest, InsertMany_EmptyCall) {
  s21::multiset<int> my_multiset;

  // Пустой вызов insert_many
  s21::vector<std::pair<s21::multiset<int>::iterator, bool>> result =
      my_multiset.insert_many();

  // Проверка на пустой результат
  EXPECT_TRUE(result.empty());

  // Убедиться, что размер мультимножества равен 0
  EXPECT_EQ(my_multiset.size(), 0);
}
