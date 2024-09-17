

#include <map>
#include <string>
#include <vector>

#include "tests_init.h"

template <class T, class K>
using map = s21::map<T, K>;

template <class T, class K>
using og_map = std::map<T, K>;

using std::pair;

class MapTest : public ::testing::Test {};

TEST(MapTest, DefaultConstructor) {
  map<int, char> A;
  map<char, char> B;
  const map<double, char> C;
  const map<char, int> D;
  EXPECT_EQ(A.size(), 0);
  EXPECT_EQ(B.size(), 0);
  EXPECT_EQ(C.size(), 0);
  EXPECT_EQ(D.size(), 0);
}

TEST(MapTest, InitConstructor) {
  map<int, int> A({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
  og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});

  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ(i.second, (*j).second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, ConstructorsAndAssignment) {
  // Testing copy constructor
  map<int, int> A({pair(1, 123), pair(2, 345), pair(3, 567)});
  map<int, int> B(A);  // Copy constructor

  EXPECT_EQ(A.at(1), B.at(1));
  EXPECT_EQ(A.at(2), B.at(2));
  EXPECT_EQ(A.at(3), B.at(3));

  // Modify A and check if B remains unchanged
  A.at(3) = 200;
  EXPECT_EQ(A.at(3), 200);
  EXPECT_EQ(B.at(3), 567);

  // Testing move constructor
  map<int, int> C(std::move(A));  // Move constructor

  EXPECT_EQ(C.at(1), 123);
  EXPECT_EQ(C.at(2), 345);
  EXPECT_EQ(C.at(3), 200);

  // A is now in a moved-from state; accessing it might be undefined
  EXPECT_THROW({ A.at(1); }, std::out_of_range);

  // Testing move assignment operator
  map<int, int> D;
  D = std::move(C);  // Move assignment operator

  EXPECT_EQ(D.at(1), 123);
  EXPECT_EQ(D.at(2), 345);
  EXPECT_EQ(D.at(3), 200);

  // C is now in a moved-from state; accessing it might be undefined
  EXPECT_THROW({ C.at(1); }, std::out_of_range);

  // Testing with double and char types
  map<double, char> AA(
      {pair(0.234567, 'a'), pair(9.5678, 'b'), pair(3.45678, 'd')});
  map<double, char> BB(AA);  // Copy constructor

  EXPECT_EQ(AA.at(0.234567), BB.at(0.234567));
  EXPECT_EQ(AA.at(9.5678), BB.at(9.5678));
  EXPECT_EQ(AA.at(3.45678), BB.at(3.45678));

  // Modify AA and check if BB remains unchanged
  AA.at(3.45678) = 'K';
  EXPECT_EQ(AA.at(3.45678), 'K');
  EXPECT_EQ(BB.at(3.45678), 'd');

  // Testing move constructor
  map<double, char> CC(std::move(AA));  // Move constructor

  EXPECT_EQ(CC.at(0.234567), 'a');
  EXPECT_EQ(CC.at(9.5678), 'b');
  EXPECT_EQ(CC.at(3.45678), 'K');

  // AA is now in a moved-from state; accessing it might be undefined
  EXPECT_THROW({ AA.at(0.234567); }, std::out_of_range);

  // Testing move assignment operator
  map<double, char> DD;
  DD = std::move(CC);  // Move assignment operator

  EXPECT_EQ(DD.at(0.234567), 'a');
  EXPECT_EQ(DD.at(9.5678), 'b');
  EXPECT_EQ(DD.at(3.45678), 'K');

  // CC is now in a moved-from state; accessing it might be undefined
  EXPECT_THROW({ CC.at(0.234567); }, std::out_of_range);
}

TEST(MapTest, At) {
  map<int, int> A({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
  og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});

  EXPECT_EQ(A.at(1), B.at(1));
  EXPECT_EQ(A.at(2), B.at(2));
  EXPECT_EQ(A.at(3), B.at(3));
  A.at(3) = 200;
  B.at(3) = 200;
  EXPECT_EQ(A.at(3), B.at(3));

  EXPECT_THROW({ A.at(10) = 1; }, std::out_of_range);

  map<double, char> AA({pair(0.234567, 'a'), pair(9.5678, 'b'),
                        pair(9.5678, 'c'), pair(3.45678, 'd')});
  og_map<double, char> BB({pair(0.234567, 'a'), pair(9.5678, 'b'),
                           pair(9.5678, 'c'), pair(3.45678, 'd')});

  EXPECT_EQ(AA.at(0.234567), BB.at(0.234567));
  EXPECT_EQ(AA.at(9.5678), BB.at(9.5678));
  EXPECT_EQ(AA.at(3.45678), BB.at(3.45678));

  AA.at(3.45678) = 'K';
  BB.at(3.45678) = 'K';
  EXPECT_EQ(AA.at(3.45678), BB.at(3.45678));
}

TEST(MapTest, brackets) {
  map<int, int> A({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
  og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});

  EXPECT_EQ(A[1], B[1]);
  EXPECT_EQ(A[2], B[2]);
  EXPECT_EQ(A[3], B[3]);
  A[3] = 200;
  B[3] = 200;
  EXPECT_EQ(A[3], B[3]);

  A[7] = 200;
  B[7] = 200;
  EXPECT_EQ(A[7], B[7]);

  map<double, char> AA({pair(0.234567, 'a'), pair(9.5678, 'b'),
                        pair(9.5678, 'c'), pair(3.45678, 'd')});
  og_map<double, char> BB({pair(0.234567, 'a'), pair(9.5678, 'b'),
                           pair(9.5678, 'c'), pair(3.45678, 'd')});

  EXPECT_EQ(AA[0.234567], BB[0.234567]);
  EXPECT_EQ(AA[9.5678], BB[9.5678]);
  EXPECT_EQ(AA[3.45678], BB[3.45678]);

  AA[3.45678] = 'K';
  BB[3.45678] = 'K';
  EXPECT_EQ(AA[3.45678], BB[3.45678]);
}

TEST(MapTest, contains) {
  map<int, int> A({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
  og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
  int a = A.contains(1);
  EXPECT_EQ(a, 1);
  EXPECT_EQ(A.contains(2), 1);
  EXPECT_EQ(A.contains(3), 1);
  EXPECT_EQ(A.contains(4), 0);
  EXPECT_EQ(A.contains(9), 0);
}

TEST(MapTest, Insert) {
  map<int, int> A({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
  og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});

  auto j = B.begin();
  auto insert_pair = A.insert(std::pair(6, 666));
  auto og_insert_pair = B.insert(std::pair(6, 666));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);

  insert_pair = A.insert(std::pair(666, 6));
  og_insert_pair = B.insert(std::pair(666, 6));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);

  insert_pair = A.insert(std::pair(6, 666));
  og_insert_pair = B.insert(std::pair(6, 666));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);

  j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, Insert2) {
  map<double, char> A({pair(0.234567, 'a'), pair(9.5678, 'b'),
                       pair(9.5678, 'c'), pair(3.45678, 'd')});
  og_map<double, char> B({pair(0.234567, 'a'), pair(9.5678, 'b'),
                          pair(9.5678, 'c'), pair(3.45678, 'd')});

  auto j = B.begin();
  A.insert(11.23456, 'M');
  B.insert(std::pair(11.23456, 'M'));

  A.insert(-456.45678, '!');
  B.insert(std::pair(-456.45678, '!'));

  A.insert(11.23456, 'M');
  B.insert(std::pair(11.23456, 'M'));

  A.insert(623849, '*');
  B.insert(std::pair(623849, '*'));
  j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, InsertOrAssign) {
  map<double, char> A({pair(0.234567, 'a'), pair(9.5678, 'b'),
                       pair(9.5678, 'c'), pair(3.45678, 'd')});
  og_map<double, char> B({pair(0.234567, 'a'), pair(9.5678, 'b'),
                          pair(9.5678, 'c'), pair(3.45678, 'd')});

  A.insert_or_assign(3.45678, 'e');
  B.insert_or_assign(3.45678, 'e');
  A.insert_or_assign(3.55678, 'e');
  B.insert_or_assign(3.55678, 'e');
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, Swap) {
  map<double, char> A({pair(0.234567, 'a'), pair(9.5678, 'b'),
                       pair(9.5678, 'c'), pair(3.45678, 'd')});
  map<double, char> AA;
  og_map<double, char> B({pair(0.234567, 'a'), pair(9.5678, 'b'),
                          pair(9.5678, 'c'), pair(3.45678, 'd')});
  og_map<double, char> BB;

  AA.swap(A);
  BB.swap(B);
  auto j = BB.begin();
  for (auto i : AA) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(AA.size(), BB.size());
}

TEST(MapTest, Merge) {
  map<double, char> A({pair(0.234567, 'a'), pair(9.5678, 'b'),
                       pair(9.5678, 'c'), pair(3.45678, 'd')});
  map<double, char> AA(
      {pair(0.5, 'K'), pair(9.111, 'M'), pair(9.09, 'N'), pair(2.45678, 'O')});

  og_map<double, char> B({pair(0.234567, 'a'), pair(9.5678, 'b'),
                          pair(9.5678, 'c'), pair(3.45678, 'd')});
  og_map<double, char> BB(
      {pair(0.5, 'K'), pair(9.111, 'M'), pair(9.09, 'N'), pair(2.45678, 'O')});

  A.merge(AA);
  B.merge(BB);
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, Merge2) {
  map<int, double> A;
  map<int, double> AA;

  og_map<int, double> B;
  og_map<int, double> BB;

  for (int i = 0; i < 10; i++) {
    A.insert(i, i * 1.0 / 0.12345);
    AA.insert(i * 5, i * 9.87654);
    B.insert(std::pair(i, i * 1.0 / 0.12345));
    BB.insert(std::pair(i * 5, i * 9.87654));
  }

  A.merge(AA);
  B.merge(BB);
  auto j = A.begin();
  for (auto i : B) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, EraseAndOthers) {
  map<double, char> A;
  og_map<double, char> B;
  for (int i = 0; i < 50; i++) {
    A.insert(i * 0.1234, char(i));
    B.insert(std::pair(i * 0.1234, char(i)));
  }
  EXPECT_EQ(A.at(5.0594), ')');
  EXPECT_EQ(A.at(5.0594), B.at(5.0594));
  EXPECT_EQ(A.at(4.4424), '$');
  EXPECT_EQ(A.at(4.4424), B.at(4.4424));
  EXPECT_EQ(A.at(5.9232), '0');
  EXPECT_EQ(A.at(5.9232), B.at(5.9232));
  EXPECT_EQ(A.size(), 50);
  EXPECT_EQ(A.size(), B.size());

  for (int i = 0; i < 10; i++) {
    A.erase(A.begin());
    B.erase(B.begin());
  }
  EXPECT_EQ(A.size(), 40);
  EXPECT_EQ(A.size(), B.size());

  A.insert(61 * 0.1234, char(61));
  B.insert(std::pair(61 * 0.1234, char(61)));
  A.insert(62 * 0.1234, char(62));
  B.insert(std::pair(62 * 0.1234, char(62)));
  A.insert(63 * 0.1234, char(63));
  B.insert(std::pair(63 * 0.1234, char(63)));
  EXPECT_EQ(A.size(), 43);
  EXPECT_EQ(A.size(), B.size());

  for (int i = 0; i < 40; i++) {
    A.erase(A.begin());
    B.erase(B.begin());
  }
  EXPECT_EQ(A.size(), 3);
  EXPECT_EQ(A.size(), B.size());
  A.clear();
  B.clear();
  EXPECT_EQ(A.size(), 0);
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, SizeAndOthers) {
  map<char, char> A({pair('a', '1'), pair('b', '2'), pair('b', '3'),
                     pair('c', '4'), pair('d', '5'), pair('e', '1'),
                     pair('f', '2'), pair('g', '3'), pair('h', '4'),
                     pair('k', '5'), pair('l', '1'), pair('m', '2'),
                     pair('n', '3'), pair('o', '4'), pair('p', '5')});
  og_map<char, char> B({pair('a', '1'), pair('b', '2'), pair('b', '3'),
                        pair('c', '4'), pair('d', '5'), pair('e', '1'),
                        pair('f', '2'), pair('g', '3'), pair('h', '4'),
                        pair('k', '5'), pair('l', '1'), pair('m', '2'),
                        pair('n', '3'), pair('o', '4'), pair('p', '5')});
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.size(), 14);
  EXPECT_EQ(B.size(), 14);
  A.erase(A.begin());
  EXPECT_EQ(A.size(), 13);
  std::cout << B.max_size() << std::endl;
  std::cout << A.max_size() << std::endl;
  EXPECT_EQ(A.max_size(), 230584300921369395);

  A.clear();
  B.clear();
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.size(), 0);
  EXPECT_EQ(B.size(), 0);
  EXPECT_TRUE(A.empty());
  EXPECT_TRUE(B.empty());
}

TEST(MapTest, InsertMany_UniqueElements) {
  s21::map<int, int> my_map;

  // Вставка множества уникальных элементов
  s21::vector<std::pair<s21::map<int, int>::iterator, bool>> result =
      my_map.insert_many(std::make_pair(1, 100), std::make_pair(2, 200),
                         std::make_pair(3, 300), std::make_pair(4, 400),
                         std::make_pair(5, 500));

  // Проверка на успешную вставку всех элементов
  for (const auto& res : result) {
    EXPECT_TRUE(res.second);
  }

  // Проверка размера map
  EXPECT_EQ(my_map.size(), 5);

  // Проверка содержимого map
  EXPECT_EQ(my_map.at(1), 100);
  EXPECT_EQ(my_map.at(2), 200);
  EXPECT_EQ(my_map.at(3), 300);
  EXPECT_EQ(my_map.at(4), 400);
  EXPECT_EQ(my_map.at(5), 500);
}

TEST(MapTest, InsertMany_WithDuplicates) {
  s21::map<int, int> my_map;

  // Вставка множества элементов, включая дубликаты
  s21::vector<std::pair<s21::map<int, int>::iterator, bool>> result =
      my_map.insert_many(std::make_pair(1, 100), std::make_pair(2, 200),
                         std::make_pair(2, 250),  // дубликат 2
                         std::make_pair(3, 300), std::make_pair(4, 400),
                         std::make_pair(1, 150)  // дубликат 1
      );

  // Проверка на успешную вставку уникальных элементов
  EXPECT_TRUE(result[0].second);   // 1
  EXPECT_TRUE(result[1].second);   // 2
  EXPECT_FALSE(result[2].second);  // дубликат 2
  EXPECT_TRUE(result[3].second);   // 3
  EXPECT_TRUE(result[4].second);   // 4
  EXPECT_FALSE(result[5].second);  // дубликат 1

  // Проверка размера map
  EXPECT_EQ(my_map.size(), 4);

  // Проверка содержимого map
  EXPECT_EQ(my_map.at(1), 100);  // Значение 150 не должно было заменить 100
  EXPECT_EQ(my_map.at(2), 200);  // Значение 250 не должно было заменить 200
  EXPECT_EQ(my_map.at(3), 300);
  EXPECT_EQ(my_map.at(4), 400);
  EXPECT_FALSE(my_map.contains(5));  // Элемент 5 не должен быть вставлен
}

TEST(MapTest, InsertMany_EmptyCall) {
  s21::map<int, int> my_map;

  // Пустой вызов insert_many
  s21::vector<std::pair<s21::map<int, int>::iterator, bool>> result =
      my_map.insert_many();

  // Проверка на пустой результат
  EXPECT_TRUE(result.empty());

  // Убедиться, что размер map равен 0
  EXPECT_EQ(my_map.size(), 0);
}
