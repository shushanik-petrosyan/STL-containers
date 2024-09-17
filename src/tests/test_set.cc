

#include <climits>
#include <set>

#include "tests_init.h"

TEST(constructor, isdefault) {
  std::set<int> a;
  s21::set<int> b;
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(constructor, copy) {
  s21::set<int> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);
  a.insert(112);
  a.insert(-5);
  a.insert(4);
  a.insert(17);
  a.insert(4);
  s21::set<int> b(a);
  EXPECT_EQ(*a.begin(), *b.begin());
  EXPECT_EQ(a.size(), b.size());
}

TEST(constructor, move) {
  s21::set<int> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);
  a.insert(112);
  a.insert(-5);
  a.insert(4);
  a.insert(17);
  a.insert(4);
  s21::set<int> b(std::move(a));
  EXPECT_EQ(-5, *b.begin());
  EXPECT_EQ(7, b.size());
  s21::set<int> c;
  s21::set<int> d(std::move(c));
  std::set<int> e;
  std::set<int> f(std::move(e));
  EXPECT_EQ(f.size(), d.size());
  EXPECT_EQ(*d.begin(), *f.begin());
  EXPECT_EQ(f.empty(), d.empty());
}

TEST(method_set, maxsize) {
  s21::set<int> a;
  std::set<int> b;
  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(method_set, clear) {
  s21::set<int> a;
  std::set<int> b;
  a.clear();
  b.clear();
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(*a.begin(), *b.begin());
  a.insert(1);
  a.insert(2);
  b.insert(1);
  b.insert(2);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(*a.begin(), *b.begin());
  EXPECT_EQ(*a.begin()++, *b.begin()++);
}

TEST(method_set, erase) {
  s21::set<int> a{1, 2, 3, 4, 5, 6, 7};
  std::set<int> c{1, 2, 3, 4, 5, 6, 7};
  a.erase(a.begin());
  c.erase(c.begin());
  auto it1 = c.begin();
  for (auto it = a.begin(); it != a.end(); ++it) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method_set, swap) {
  s21::set<int> a{1, 2, 3, 4, 5, 6, 7};
  s21::set<int> b{3, 2};
  std::set<int> c{1, 2, 3, 4, 5, 6, 7};
  std::set<int> d{3, 2};
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
  a = std::move(b);
  auto it3 = a.begin();
  for (auto it4 = d.begin(); it4 != d.end(); it4++) {
    EXPECT_EQ(*it4, *it3);
    it3++;
  }
  EXPECT_EQ(a.size(), d.size());
}

TEST(method_set, merge) {
  s21::set<int> a{1, 2, 3, 4, 5, 6, 7};
  s21::set<int> b{3, 9};
  std::set<int> c{1, 2, 3, 4, 5, 6, 7, 9};
  a.merge(b);
  auto it1 = a.begin();
  for (auto it = c.begin(); it != c.end(); it++) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method_set, find) {
  s21::set<int> a{1, 2, 3, 4, 5, 6, 11, 7, 0};
  std::set<int> c{1, 2, 3, 4, 5, 6, 11, 7, 0};
  EXPECT_EQ(*a.find(7), *c.find(7));
  EXPECT_EQ(*a.find(0), *c.find(0));
  EXPECT_THROW(
      {
        auto it = a.find(12);
        *it;
      },
      std::out_of_range);
  EXPECT_EQ(*a.find(1), *c.find(1));
}

TEST(method_set, contains) {
  s21::set<int> a{1, 2, 3, 4, 5, 6, 11, 7, 0};
  EXPECT_EQ(a.contains(10), false);
  EXPECT_EQ(a.contains(5), true);
}

TEST(method_set, contains2) {
  const s21::set<int> a{1, 2, 3, 4, 5, 6, 11, 7, 0};
  EXPECT_EQ(a.contains(10), false);
  EXPECT_EQ(a.contains(5), true);
}

// Тест на insert_many с уникальными элементами
TEST(SetTest, InsertMany_UniqueElements) {
  s21::set<int> my_set;
  // Вставка множества уникальных элементов
  s21::vector<std::pair<s21::set<int>::iterator, bool>> result =
      my_set.insert_many(1, 2, 3, 4, 5);
  // Проверка на успешную вставку всех элементов
  for (const auto& res : result) {
    EXPECT_TRUE(res.second);
  }
  // Проверка размера сета
  EXPECT_EQ(my_set.size(), 5);
  // Проверка содержимого сета
  EXPECT_TRUE(my_set.contains(1));
  EXPECT_TRUE(my_set.contains(2));
  EXPECT_TRUE(my_set.contains(3));
  EXPECT_TRUE(my_set.contains(4));
  EXPECT_TRUE(my_set.contains(5));
}

TEST(SetTest, InsertMany_WithDuplicates) {
  s21::set<int> my_set;
  // Вставка множества элементов, включая дубликаты
  s21::vector<std::pair<s21::set<int>::iterator, bool>> result =
      my_set.insert_many(1, 2, 2, 3, 4, 1);
  // Проверка на успешную вставку уникальных элементов
  EXPECT_TRUE(result[0].second);
  EXPECT_TRUE(result[1].second);
  EXPECT_FALSE(result[2].second);
  EXPECT_TRUE(result[3].second);
  EXPECT_TRUE(result[4].second);
  EXPECT_FALSE(result[5].second);
  // Проверка размера сета
  EXPECT_EQ(my_set.size(), 4);
  // Проверка содержимого сета
  EXPECT_TRUE(my_set.contains(1));
  EXPECT_TRUE(my_set.contains(2));
  EXPECT_TRUE(my_set.contains(3));
  EXPECT_TRUE(my_set.contains(4));

  EXPECT_FALSE(my_set.contains(5));  // Элемент 5 не должен быть вставлен
}

// Тест на insert_many с пустым вызовом
TEST(SetTest, InsertMany_EmptyCall) {
  s21::set<int> my_set;
  s21::vector<std::pair<s21::set<int>::iterator, bool>> result =
      my_set.insert_many();
  EXPECT_TRUE(result.empty());
  EXPECT_EQ(my_set.size(), 0);
}

TEST(constructor, initializer_list) {
  s21::set<int> a{1, 2, 3, 4, 5};
  std::set<int> b{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), b.size());
  auto it1 = a.begin();
  for (auto it2 = b.begin(); it2 != b.end(); ++it2) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
  }
}

TEST(method_set, single_insert) {
  s21::set<int> a;
  a.insert(10);
  EXPECT_EQ(a.size(), 1);
  EXPECT_TRUE(a.contains(10));
  a.insert(10);            // Попытка вставить дубликат
  EXPECT_EQ(a.size(), 1);  // Размер не должен измениться
  EXPECT_TRUE(a.contains(10));
}

TEST(iterator, begin_end) {
  s21::set<int> a{10, 20, 30, 40, 50};
  std::set<int> b{10, 20, 30, 40, 50};

  auto it1 = a.begin();
  auto it2 = b.begin();
  while (it1 != a.end() && it2 != b.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  EXPECT_EQ(it1 == a.end(),
            it2 == b.end());  // Оба должны достичь конца одновременно
}

TEST(method_set, insert_return_value) {
  s21::set<int> a;
  auto result = a.insert(5);
  EXPECT_TRUE(result.second);  // Элемент был успешно вставлен
  EXPECT_EQ(*result.first, 5);  // Проверка значения
  result = a.insert(5);
  EXPECT_FALSE(result.second);  // Повторная вставка того же элемента
  EXPECT_EQ(*result.first,
            5);  // Итератор указывает на уже существующий элемент
}

TEST(method_set, clear_and_insert) {
  s21::set<int> a{1, 2, 3};
  a.clear();
  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  a.insert(10);
  EXPECT_EQ(a.size(), 1);
  EXPECT_TRUE(a.contains(10));
}

TEST(method_set, intersection) {
  s21::set<int> a{1, 2, 3, 4};
  s21::set<int> b{3, 4, 5, 6};

  s21::set<int> intersection;
  for (auto it = a.begin(); it != a.end(); ++it) {
    if (b.contains(*it)) {
      intersection.insert(*it);
    }
  }
  EXPECT_TRUE(intersection.contains(3));
  EXPECT_TRUE(intersection.contains(4));
  EXPECT_EQ(intersection.size(), 2);
}

TEST(edge_case, empty_set) {
  s21::set<int> a;
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0);
  EXPECT_NO_THROW(a.erase(a.begin()));
}

TEST(edge_case, single_element_insert_erase) {
  s21::set<int> a;
  a.insert(42);
  EXPECT_EQ(a.size(), 1);
  EXPECT_TRUE(a.contains(42));
  a.erase(a.begin());
  EXPECT_EQ(a.size(), 0);
  EXPECT_FALSE(a.contains(42));
}

TEST(edge_case, large_number_of_elements) {
  s21::set<int> a;
  for (int i = 0; i < 1000000; ++i) {
    a.insert(i);
  }
  EXPECT_EQ(a.size(), 1000000);
  EXPECT_EQ(*a.begin(), 0);
  EXPECT_EQ(*--a.end(), 999999);
  a.clear();
  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
}

TEST(edge_case, insert_negative_and_boundary_values) {
  s21::set<int> a;
  a.insert(-100);
  a.insert(0);
  a.insert(INT_MAX);
  a.insert(INT_MIN);
  EXPECT_TRUE(a.contains(-100));
  EXPECT_TRUE(a.contains(0));
  EXPECT_TRUE(a.contains(INT_MAX));
  EXPECT_TRUE(a.contains(INT_MIN));
  EXPECT_EQ(a.size(), 4);
}

TEST(edge_case, clear_and_reinsert) {
  s21::set<int> a{1, 2, 3, 4, 5};
  a.clear();
  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
  a.insert(10);
  EXPECT_EQ(a.size(), 1);
  EXPECT_TRUE(a.contains(10));
}

TEST(edge_case, insert_many_empty_and_duplicates) {
  s21::set<int> a;
  auto result = a.insert_many();
  EXPECT_TRUE(result.empty());
  EXPECT_EQ(a.size(), 0);
  result = a.insert_many(1, 1, 1, 1);
  EXPECT_EQ(a.size(), 1);
  EXPECT_TRUE(a.contains(1));
  EXPECT_FALSE(result[1].second);
}

TEST(edge_case, insert_double_boundary_values) {
  s21::set<double> a;
  a.insert(std::numeric_limits<double>::min());
  a.insert(std::numeric_limits<double>::max());
  a.insert(0.0);
  a.insert(-0.0);
  EXPECT_EQ(a.size(), 3);
  EXPECT_TRUE(a.contains(std::numeric_limits<double>::min()));
  EXPECT_TRUE(a.contains(std::numeric_limits<double>::max()));
  EXPECT_TRUE(a.contains(0.0));
}

TEST(edge_case, invalid_iterator_access) {
  s21::set<int> a{1, 2, 3};
  auto it = a.end();
  EXPECT_THROW({ *it; }, std::out_of_range);
}

struct CustomStruct {
  int a;
  bool operator<(const CustomStruct& other) const { return a < other.a; }
};

TEST(edge_case, insert_custom_type) {
  s21::set<CustomStruct> a;
  a.insert(CustomStruct{1});
  a.insert(CustomStruct{2});
  EXPECT_EQ(a.size(), 2);
  EXPECT_TRUE(a.contains(CustomStruct{1}));
  EXPECT_TRUE(a.contains(CustomStruct{2}));
}

TEST(SetTest, GrandparentReturnsNullptr) {
  s21::set<int> test_set;
  auto it = test_set.insert(10).first;
  // Поскольку дерево содержит только один элемент, у него нет родителей или
  // дедушек
  ASSERT_EQ(it.current_->grandparent(), nullptr);
}

TEST(SetTest, UncleReturnsNullptr) {
  s21::set<int> test_set;
  auto it = test_set.insert(10).first;
  // В дереве с одним элементом нет дяди
  ASSERT_EQ(it.current_->uncle(), nullptr);
}

TEST(SetTest, BrotherReturnsNullptr) {
  s21::set<int> test_set;
  auto it = test_set.insert(10).first;
  ASSERT_EQ(it.current_->brother(), nullptr);
}

TEST(SetTest, OperatorPlusPlus) {
  s21::set<int> test_set = {10, 20, 30};
  auto it = test_set.begin();
  ASSERT_EQ(*it, 10);
  ++it;
  ASSERT_EQ(*it, 20);
  ++it;
  ASSERT_EQ(*it, 30);
  ++it;
}

TEST(SetTest, OperatorMinusMinus) {
  s21::set<int> test_set = {10, 20, 30};
  auto it = test_set.end();
  --it;
  ASSERT_EQ(*it, 30);
  --it;
  ASSERT_EQ(*it, 20);
  --it;
  ASSERT_EQ(*it, 10);
}

TEST(SetTest, CopyConstructorWithEmptySet) {
  s21::set<int> test_set;
  s21::set<int> copied_set(test_set);
  ASSERT_TRUE(copied_set.empty());
  ASSERT_EQ(copied_set.size(), 0);
}

TEST(SetTest, CopyConstructorWithNonEmptySet) {
  s21::set<int> test_set = {10, 20, 30};
  s21::set<int> copied_set(test_set);
  ASSERT_EQ(copied_set.size(), 3);
  ASSERT_TRUE(copied_set.contains(10));
  ASSERT_TRUE(copied_set.contains(20));
  ASSERT_TRUE(copied_set.contains(30));
}

TEST(SetTest, AssignmentOperatorWithEmptySet) {
  s21::set<int> test_set;
  s21::set<int> assigned_set = test_set;
  ASSERT_TRUE(assigned_set.empty());
  ASSERT_EQ(assigned_set.size(), 0);
}

TEST(SetTest, AssignmentOperator) {
  s21::set<int> tree1;
  tree1.insert(10);
  tree1.insert(5);
  tree1.insert(15);
  tree1.insert(3);
  tree1.insert(7);
  s21::RBTree<int> tree2;
  tree2 = tree1;
  assert(!tree2.empty());
  assert(tree2.size() == tree1.size());
  auto it1 = tree1.begin();
  auto it2 = tree2.begin();
  while (it1 != tree1.end()) {
    assert(*it1 == *it2);
    ++it1;
    ++it2;
  }
}
