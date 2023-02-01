#include <gtest/gtest.h>
#include "sfleta_containers.h"
#include "sfleta_containersplus.h"

#include <array>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>

bool isEqual(double src1, double src2) {
    if (fabs(src1 - src2) < 1e-6) {
        return true;
    }
    return false;
}

template<typename K>
bool eq_set(const s21::set<K>& s1, const std::set<K>& s2) {
    if (s1.size() != s2.size()) {
        std::cout << "fail on size" <<std::endl;
        return false;
    }
    if (s1.size() > 0 || s2.size() > 0) {
        auto it2 = s2.begin();
        for (auto &&value : s1) {
            if (value != *it2) {
                std::cout << "fail on " << value <<std::endl;
                return false;
            }
            ++it2;
        }
    }
    return true;
}

template <typename T>
bool lists_eq(const s21::list<T> &sfleta_l, const std::list<T> &std_l) {
  bool res = true;
  if (sfleta_l.empty() != std_l.empty() && sfleta_l.size() != std_l.size()) {
    res = false;
  }
  if (res && !sfleta_l.empty()) {
    if (sfleta_l.front() != std_l.front() && sfleta_l.back() != std_l.back()) {
      res = false;
    }

    typename s21::list<T>::iterator sfleta_it = sfleta_l.cbegin();
    typename std::list<T>::const_iterator std_it = std_l.cbegin();

    while (res && sfleta_it != sfleta_l.cend()) {
      res = *sfleta_it == *std_it;
      ++sfleta_it;
      ++std_it;
    }
  }
  return res;
}

template<typename K>
bool eq_multiset(const s21::multiset<K>& s1, const std::multiset<K>& s2) {
    if (s1.size() != s2.size()) {
        std::cout << "fail on size" <<std::endl;
        return false;
    }
    if (s1.size() > 0 || s2.size() > 0) {
        auto it2 = s2.begin();
        for (auto &&value : s1) {
            if (value != *it2) {
                std::cout << "fail on " << value <<std::endl;
                return false;
            }
            ++it2;
        }
    }
    return true;
}

template <typename T>
bool eq_container(const s21::vector<T>& src, const std::vector<T>& other) {
    if (src.size() != other.size() || src.capacity() != other.capacity()) {
        std::cout << "fail on size/capacity" << std::endl;
        std::cout << "this size = " << src.size() << " vs "
            << "other size = " << other.size() << std::endl;
        std::cout << "this capacity = " << src.capacity() << " vs "
            << "other capacity = " << other.capacity() << std::endl;
        return false;
    }
    for (size_t i = 0; i < src.size(); i++) {
        if (!isEqual(src.at(i), other.at(i))) {
            std::cout << "fail on buffer_.at(" << i << ") =" << src.at(i)
                << std::endl;
            return false;
        }
    }
    return true;
}

template<typename T, size_t N>
bool eq_container(const s21::array<T, N>& src, const std::array<T, N>& other) {
    if (src.size() != other.size()) {
        std::cout << "fail on size_" << std::endl;
        return false;
    }
    for (size_t i = 0; i < src.size(); i++) {
        if (!isEqual(src.at(i), other.at(i))) {
            std::cout << "fail on buffer_.at(" << i << ")" << std::endl;
            return false;
        }
    }
    return true;
}

template<typename K, typename T>
bool eq_map(const s21::Map<K, T>& s1, const std::map<K, T>& s2) {
        auto it2 = s2.begin();
        for (auto value : s1) {
            if (value.first != (*it2).first || value.second != (*it2).second) {
                std::cout << "fail on s21: " << value.first << " " << value.second <<std::endl;
                std::cout << "fail on ORIG: " << (*it2).first << " " << (*it2).second <<std::endl;
                return false;
            }
            ++it2;
        }
    return true;
}

template <typename s21, typename std_or_s21>
bool eq_queue(s21 q1, std_or_s21 q2) {
    while (q1.size() || q2.size()) {
        bool res = (q1.empty() == q2.empty()) &&
                   (q1.size() == q2.size()) &&
                   (q1.front() == q2.front()) &&
                   (q1.back() == q2.back());
        if (!res) return false;
        q1.pop();
        q2.pop();
    }
    return true;
}

template <typename s21, typename std_or_s21>
bool eq_stack(s21 s1, std_or_s21 s2) {
    while (s1.size() || s2.size()) {
        bool res = (s1.empty() == s2.empty()) &&
                   (s1.size() == s2.size()) &&
                   (s1.top() == s2.top());
        if (!res) return false;
        s1.pop();
        s2.pop();
    }
    return true;
}

//*** vector_tests ***//

TEST(vector_constructor_test, empty_constructor) {
    s21::vector<int> v1;
    std::vector<int> v2;
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, param_constructor) {
    s21::vector<int> v1(5);
    std::vector<int> v2(5);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, param_constructor3) {
    ASSERT_NO_THROW(s21::vector<int> v1(0));
}

TEST(vector_constructor_test, initializer_list) {
    s21::vector<double> v1{ 2, 1, 3, 4, 5 };
    std::vector<double> v2{ 2, 1, 3, 4, 5 };
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, initializer_list2) {
    s21::vector<double> v1{};
    std::vector<double> v2{};
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, copy_constructor) {
    s21::vector<double> vSrc{ 2, 1, 3, 4, 5 };
    s21::vector<double> v1(vSrc);
    std::vector<double> v2{ 2, 1, 3, 4, 5 };
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, copy_constructor2) {
    s21::vector<double> vSrc{};
    s21::vector<double> v1(vSrc);
    std::vector<double> v2{};
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, move_constructor) {
    s21::vector<double> vSrc{ 2, 1, 3, 4, 5 };
    s21::vector<double> v1(std::move(vSrc));
    std::vector<double> v2{ 2, 1, 3, 4, 5 };
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, move_constructor2) {
    s21::vector<double> vSrc{};
    s21::vector<double> v1(std::move(vSrc));
    std::vector<double> v2{};
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, operatorMove) {
    s21::vector<double> vSrc{ 2, 1, 3, 4, 5 };
    s21::vector<double> v1;
    v1 = std::move(vSrc);
    std::vector<double> v2Src{ 2, 1, 3, 4, 5 };
    std::vector<double> v2;
    v2 = std::move(v2Src);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_constructor_test, operatorMove2) {
    s21::vector<double> v1;
    v1 = std::move(v1);
    std::vector<double> v2;
    v2 = std::move(v2);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_access_test, at) {
    s21::vector<double> v1{ 2, 1, 3, 4, 5 };
    std::vector<double> v2{ 2, 1, 3, 4, 5 };
    ASSERT_EQ(v1.at(v1.size() / 2), v2.at(v1.size() / 2));
}

TEST(vector_access_test, operatorBrace) {
    s21::vector<double> v1{ 2, 1, 3, 4, 5 };
    std::vector<double> v2{ 2, 1, 3, 4, 5 };
    ASSERT_EQ(v1[3], v2[3]);
}

TEST(vector_access_test, front) {
    double value = 13;
    s21::vector<double> v1{ value };
    std::vector<double> v2{ value };
    ASSERT_EQ(v1.front(), v2.front());
}

TEST(vector_access_test, front2) {
    s21::vector<double> v1{ 1, 2 };
    std::vector<double> v2{ 1, 2 };
    ASSERT_EQ(v1.front(), v2.front());
}

TEST(vector_access_test, back) {
    s21::vector<double> v1{ 2.3, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2.3, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(v1.back(), v2.back());
}

TEST(vector_access_test, back2) {
    s21::vector<double> v1{ 4.43 };
    std::vector<double> v2{ 4.43 };
    ASSERT_EQ(v1.back(), v2.back());
}

TEST(vector_access_test, data) {
    s21::vector<double> v1{ 2.3, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2.3, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(*v1.data(), *v2.data());
}

TEST(vector_iterators_test, begin) {
    s21::vector<double> v1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(*v1.begin(), *v2.begin());
}

TEST(vector_iterators_test, end) {
    s21::vector<double> v1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(*(v1.end() - 1), *(v2.end() - 1));
}

TEST(vector_iterators_test, end2) {
    s21::vector<double> v1{ 2 };
    std::vector<double> v2{ 2 };
    ASSERT_EQ(*(v1.end() - 1), *(v2.end() - 1));
}

TEST(vector_test, empty) {
    s21::vector<double> v1;
    std::vector<double> v2;
    ASSERT_EQ(v1.empty(), v2.empty());
}

TEST(vector_capacity_test, empty2) {
    s21::vector<double> v1(1);
    std::vector<double> v2(1);
    ASSERT_EQ(v1.empty(), v2.empty());
}

TEST(vector_capacity_test, size) {
    size_t n = 0;
    s21::vector<double> v1(n);
    std::vector<double> v2(n);
    ASSERT_EQ(v1.size(), v2.size());
}

TEST(vector_capacity_test, size2) {
    size_t n = 5;
    s21::vector<double> v1(n);
    std::vector<double> v2(n);
    ASSERT_EQ(v1.size(), v2.size());
}

TEST(vector_capacity_test, max_size) {
    size_t n = 5;
    s21::vector<double> v1(n);
    std::vector<double> v2(n);
    ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(vector_capacity_test, max_size2) {
    size_t n = 5;
    s21::vector<std::string> v1(n);
    std::vector<std::string> v2(n);
    ASSERT_EQ(v1.max_size(), v2.max_size());
}

TEST(vector_capacity_test, reserve) {
    size_t n = 5;
    s21::vector<double> v1;
    std::vector<double> v2;
    v1.reserve(n);
    v2.reserve(n);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_capacity_test, reserve2) {
    size_t n = 12;
    s21::vector<double> v1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2, 1.1, 3.23, 4.43, 5.32 };
    v1.reserve(n);
    v2.reserve(n);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_capacity_test, reserve3) {
    size_t n = 1;
    s21::vector<double> v1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2, 1.1, 3.23, 4.43, 5.32 };
    v1.reserve(n);
    v2.reserve(n);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_capacity_test, capacity) {
    s21::vector<double> v1;
    std::vector<double> v2;
    ASSERT_EQ(v1.capacity(), v2.capacity());
}

TEST(vector_capacity_test, capacity2) {
    s21::vector<double> v1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(v1.capacity(), v2.capacity());
}

TEST(vector_capacity_test, capacity3) {
    s21::vector<double> v1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2, 1.1, 3.23, 4.43, 5.32 };
    v1.push_back(33);
    v2.push_back(33);
    ASSERT_EQ(v1.capacity(), v2.capacity());
}

TEST(vector_capacity_test, shrink_to_fit) {
    s21::vector<double> v1(100);
    std::vector<double> v2(100);
    v1.push_back(33);
    v2.push_back(33);

    v1.shrink_to_fit();
    v2.shrink_to_fit();
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, clear) {
    s21::vector<double> v1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::vector<double> v2{ 2, 1.1, 3.23, 4.43, 5.32 };
    v1.clear();
    v2.clear();
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, insert) {
    s21::vector<double> v1{ 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<double> v2{ 8, 7, 6, 5, 4, 3, 2, 1 };
    v1.insert(v1.begin(), 33);
    v2.insert(v2.begin(), 33);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, insert2) {
    size_t shift = 2;
    s21::vector<double> v1{ 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<double> v2{ 8, 7, 6, 5, 4, 3, 2, 1 };
    s21::vector<double>::iterator it1;
    std::vector<double>::iterator it2;
    it1 = v1.insert(v1.begin() + shift, 34);
    it2 = v2.insert(v2.begin() + shift, 34);
    ASSERT_EQ(it1 - v1.begin(), it2 - v2.begin());
}

TEST(vector_modifiers, insert3) {
    size_t shift = 7;
    s21::vector<double> v1{ 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<double> v2{ 8, 7, 6, 5, 4, 3, 2, 1 };
    s21::vector<double>::iterator it1;
    std::vector<double>::iterator it2;
    it1 = v1.insert(v1.begin() + shift, 34);
    it2 = v2.insert(v2.begin() + shift, 34);
    ASSERT_EQ(*it1, *it2);
}

TEST(vector_modifiers, erase) {
    size_t shift = 0;
    s21::vector<double> v1{ 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<double> v2{ 8, 7, 6, 5, 4, 3, 2, 1 };
    v1.erase(v1.begin() + shift);
    v2.erase(v2.begin() + shift);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, erase2) {
    size_t shift = 2;
    s21::vector<double> v1{ 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<double> v2{ 8, 7, 6, 5, 4, 3, 2, 1 };
    v1.erase(v1.begin() + shift);
    v2.erase(v2.begin() + shift);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, push_back) {
    double value = 2.434;
    s21::vector<double> v1{};
    std::vector<double> v2{};
    v1.push_back(value);
    v2.push_back(value);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, push_back2) {
    double value = 1;
    s21::vector<double> v1{ 8, 7, 6, 5, 4, 3, 2 };
    std::vector<double> v2{ 8, 7, 6, 5, 4, 3, 2 };
    v1.push_back(value);
    v2.push_back(value);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, pop_back) {
    s21::vector<double> v1{ 8 };
    std::vector<double> v2{ 8 };
    v1.pop_back();
    v2.pop_back();
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, pop_back2) {
    s21::vector<double> v1{ 1, 2, 3 };
    std::vector<double> v2{ 1, 2, 3 };
    v1.pop_back();
    v1.pop_back();
    v2.pop_back();
    v2.pop_back();
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, swap) {
    s21::vector<double> v1{};
    s21::vector<double> v1_2{ 1, 2, 3 };
    std::vector<double> v2{};
    std::vector<double> v2_2{ 1, 2, 3 };
    v1.swap(v1_2);
    v2.swap(v2_2);
    ASSERT_TRUE(eq_container(v1, v2));
}

TEST(vector_modifiers, swap2) {
    s21::vector<double> v1{};
    s21::vector<double> v1_2{ 1, 2, 3 };
    std::vector<double> v2{};
    std::vector<double> v2_2{ 1, 2, 3 };
    v1.swap(v1_2);
    v2.swap(v2_2);
    ASSERT_TRUE(eq_container(v1_2, v2_2));
}

TEST(vector_modifiers, emplace) {
    s21::vector<double> v1{ 1, 5 };
    v1.emplace((v1.begin() + 1), 2.0, 3.0, 4.0);

    std::vector<double> v2{ 1, 5 };
    v2.emplace((v2.begin() + 1), 2.0);
    v2.emplace((v2.begin() + 2), 3.0);
    v2.emplace((v2.begin() + 3), 4.0);

    ASSERT_TRUE(eq_container(v1, v2));
    ASSERT_EQ(*(v1.data()), *(v2.data()));
}

TEST(vector_modifiers, emplace2) {
    s21::vector<double> v1{};
    v1.emplace((v1.begin()), 2.0, 3.0, 4.0);

    std::vector<double> v2{};
    v2.emplace((v2.begin()), 2.0);
    v2.emplace((v2.begin() + 1), 3.0);
    v2.emplace((v2.begin() + 2), 4.0);

    ASSERT_TRUE(eq_container(v1, v2));
    ASSERT_EQ(*(v1.data()), *(v2.data()));
}

TEST(vector_modifiers, emplace3) {
    s21::vector<double> v1{ 1, 2 };
    v1.emplace((v1.end()), 3.0, 4.0, 5.0);

    std::vector<double> v2{ 1, 2 };
    v2.emplace(v2.end(), 3.0);
    v2.emplace(v2.end(), 4.0);
    v2.emplace(v2.end(), 5.0);

    ASSERT_TRUE(eq_container(v1, v2));
    ASSERT_EQ(*(v1.data()), *(v2.data()));
}

TEST(vector_modifiers, emplace4) {
    s21::vector<double> v1{};
    v1.emplace((v1.end()), 1.0, 2.0, 3.0);

    std::vector<double> v2{};
    v2.emplace(v2.end(), 1.0);
    v2.emplace(v2.end(), 2.0);
    v2.emplace(v2.end(), 3.0);

    ASSERT_TRUE(eq_container(v1, v2));
    ASSERT_EQ(*(v1.data()), *(v2.data()));
}

TEST(vector_modifiers, emplace_back) {
    s21::vector<double> v1{};
    v1.emplace_back(1.0, 2.0, 3.0);

    std::vector<double> v2{};
    v2.emplace_back(1.0);
    v2.emplace_back(2.0);
    v2.emplace_back(3.0);

    ASSERT_TRUE(eq_container(v1, v2));
    ASSERT_EQ(*(v1.data()), *(v2.data()));
}

TEST(vector_modifiers, emplace_back2) {
    s21::vector<double> v1{ -1, 0 };
    v1.emplace_back(1.0, 2.0, 3.0);

    std::vector<double> v2{ -1, 0 };
    v2.emplace_back(1.0);
    v2.emplace_back(2.0);
    v2.emplace_back(3.0);

    ASSERT_TRUE(eq_container(v1, v2));
    ASSERT_EQ(*(v1.data()), *(v2.data()));
}

// *** array_tests ***//
TEST(array_constructor_test, empty_constructor) {
    s21::array<double, 1> arr1;
    std::array<double, 1> arr2;
    ASSERT_EQ(arr1.size(), arr2.size());
    ASSERT_EQ(arr1.empty(), arr2.empty());
}

TEST(array_constructor_test, initializer_list) {
    s21::array<double, 5> arr1{ 2, 1, 3, 4, 5 };
    std::array<double, 5> arr2{ 2, 1, 3, 4, 5 };
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_constructor_test, initializer_list2) {
    s21::array<double, 0> arr1{};
    std::array<double, 0> arr2{};
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_constructor_test, copy_constructor) {
    s21::array<double, 5> arrSrc{ 2, 1, 3, 4, 5 };
    s21::array<double, 5> arr1(arrSrc);
    std::array<double, 5> arr2{ 2, 1, 3, 4, 5 };
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_constructor_test, copy_constructor2) {
    s21::array<double, 5> arrSrc{};
    s21::array<double, 5> arr1(arrSrc);
    std::array<double, 5> arr2{};
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_constructor_test, move_constructor) {
    s21::array<double, 5> arrSrc{ 2, 1, 3, 4, 5 };
    s21::array<double, 5> arr1(std::move(arrSrc));
    std::array<double, 5> arr2{ 2, 1, 3, 4, 5 };
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_constructor_test, move_constructor2) {
    s21::array<double, 5> arrSrc{};
    s21::array<double, 5> arr1(std::move(arrSrc));
    std::array<double, 5> arr2{};
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_constructor_test, operatorMove) {
    s21::array<double, 5> arrSrc{ 2, 1, 3, 4, 5 };
    s21::array<double, 5> arr1;
    arr1 = std::move(arrSrc);
    std::array<double, 5> arr2Src{ 2, 1, 3, 4, 5 };
    std::array<double, 5> arr2;
    arr2 = std::move(arr2Src);
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_constructor_test, operatorMove2) {
    s21::array<double, 5> arr1 {1};
    arr1 = std::move(arr1);
    std::array<double, 5> arr2 {1};
    arr2 = std::move(arr2);
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_access_test, at) {
    s21::array<double, 5> arr1{ 2, 1, 3, 4, 5 };
    std::array<double, 5> arr2{ 2, 1, 3, 4, 5 };
    ASSERT_EQ(arr1.at(arr1.size() / 2), arr2.at(arr1.size() / 2));
}

TEST(array_access_test, operatorBrace) {
    s21::array<double, 5> arr1{ 2, 1, 3, 4, 5 };
    std::array<double, 5> arr2{ 2, 1, 3, 4, 5 };
    ASSERT_EQ(arr1[3], arr2[3]);
}

TEST(array_access_test, front) {
    double value = 13;
    s21::array<double, 5> arr1{ value };
    std::array<double, 5> arr2{ value };
    ASSERT_EQ(arr1.front(), arr2.front());
}

TEST(array_access_test, front2) {
    s21::array<double, 5> arr1{ 1, 2 };
    std::array<double, 5> arr2{ 1, 2 };
    ASSERT_EQ(arr1.front(), arr2.front());
}

TEST(array_access_test, back) {
    s21::array<double, 5> arr1{ 2.3, 1.1, 3.23, 4.43, 5.32 };
    std::array<double, 5> arr2{ 2.3, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(array_access_test, back2) {
    s21::array<double, 5> arr1{ 4.43 };
    std::array<double, 5> arr2{ 4.43 };
    ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(array_access_test, data) {
    s21::array<double, 5> arr1{ 2.3, 1.1, 3.23, 4.43, 5.32 };
    std::array<double, 5> arr2{ 2.3, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(*arr1.data(), *arr2.data());
}

TEST(array_iterators_test, begin) {
    s21::array<double, 5> arr1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::array<double, 5> arr2{ 2, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(*arr1.begin(), *arr2.begin());
}

TEST(array_iterators_test, end) {
    s21::array<double, 5> arr1{ 2, 1.1, 3.23, 4.43, 5.32 };
    std::array<double, 5> arr2{ 2, 1.1, 3.23, 4.43, 5.32 };
    ASSERT_EQ(*(arr1.end() - 1), *(arr2.end() - 1));
}

TEST(array_iterators_test, end2) {
    s21::array<double, 5> arr1{ 2 };
    std::array<double, 5> arr2{ 2 };
    ASSERT_EQ(*(arr1.end() - 1), *(arr2.end() - 1));
}

TEST(array_capacity_test, empty) {
    s21::array<double, 5> arr1;
    std::array<double, 5> arr2;
    ASSERT_EQ(arr1.empty(), arr2.empty());
}

TEST(array_capacity_test, size) {
    s21::array<double, 0> arr1;
    std::array<double, 0> arr2;
    ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(array_capacity_test, size2) {
    s21::array<double, 5> arr1{ 1, 2, 3 };
    std::array<double, 5> arr2{ 1, 2, 3 };
    ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(array_capacity_test, max_size) {
    s21::array<double, 5> arr1;
    std::array<double, 5> arr2;
    ASSERT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array_capacity_test, max_size2) {
    s21::array<std::string, 5> arr1;
    std::array<std::string, 5> arr2;
    ASSERT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array_modifiers, swap) {
    s21::array<double, 5> arr1{};
    s21::array<double, 5> arr1_2{ 1, 2, 3 };
    std::array<double, 5> arr2{};
    std::array<double, 5> arr2_2{ 1, 2, 3 };
    arr1.swap(arr1_2);
    arr2.swap(arr2_2);
    ASSERT_TRUE(eq_container(arr1, arr2));
}

TEST(array_modifiers, swap2) {
    s21::array<double, 5> arr1{};
    s21::array<double, 5> arr1_2{ 1, 2, 3 };
    std::array<double, 5> arr2{};
    std::array<double, 5> arr2_2{ 1, 2, 3 };
    arr1.swap(arr1_2);
    arr2.swap(arr2_2);
    ASSERT_TRUE(eq_container(arr1_2, arr2_2));
}

TEST(array_modifiers, fill) {
    const double value = 0.33;
    s21::array<double, 5> arr1{};
    std::array<double, 5> arr2{};
    arr1.fill(value);
    arr2.fill(value);
    ASSERT_TRUE(eq_container(arr1, arr2));
}

// *** THROW_TEST *** //
// TEST(vector_constructor_test, param_constructor2) {
//     ASSERT_ANY_THROW(s21::vector<int> v1(-1));
// }

// TEST(vector_access_test, at2) {
//     s21::vector<double> v1{ 2, 1, 3, 4, 5 };
//     ASSERT_ANY_THROW(v1.at(-1));
// }

// TEST(vector_access_test, at3) {
//     s21::vector<double> v1{ 2, 1, 3, 4, 5 };
//     ASSERT_ANY_THROW(v1.at(v1.size()));
// }

// TEST(vector_access_test, operatorBrace2) {
//     s21::vector<double> v1{ 2, 1, 3, 4, 5 };
//     ASSERT_ANY_THROW(v1[-1]);
// }

// TEST(vector_access_test, operatorBrace3) {
//     s21::vector<double> v1{ 2, 1, 3, 4, 5 };
//     ASSERT_ANY_THROW(v1[v1.size()]);
// }

// TEST(vector_access_test, front3) {
//     s21::vector<double> v1;
//     ASSERT_ANY_THROW(v1.front());
// }

// TEST(vector_access_test, back3) {
//     s21::vector<double> v1;
//     ASSERT_ANY_THROW(v1.back());
// }

// TEST(vector_capacity_test, reserve4) {
//     size_t n = UINT64_MAX;
//     s21::vector<double> v1{ 2, 1.1, 3.23, 4.43, 5.32 };
//     ASSERT_ANY_THROW(v1.reserve(n));
// }

// TEST(array_access_test, at2) {
//     s21::array<double, 5> arr1{ 2, 1, 3, 4, 5 };
//     ASSERT_ANY_THROW(arr1.at(-1));
// }

// TEST(array_access_test, at3) {
//     s21::array<double, 5> arr1{ 2, 1, 3, 4, 5 };
//     ASSERT_ANY_THROW(arr1.at(arr1.size()));
// }

// TEST(array_access_test, operatorBrace2) {
//     s21::array<double, 5> arr1{ 2, 1, 3, 4, 5 };
//     ASSERT_ANY_THROW(arr1[-1]);
// }

// TEST(array_access_test, operatorBrace3) {
//     s21::array<double, 5> arr1{ 2, 1, 3, 4, 5 };
//     ASSERT_ANY_THROW(arr1[arr1.size()]);
// }

// list test

TEST(list_ConstructorsTests, costr_default) {
  s21::list<int> sfleta_l1;
  ASSERT_EQ(sfleta_l1.size(), 0);

  s21::list<double> sfleta_l2;
  ASSERT_EQ(sfleta_l2.empty(), true);

  s21::list<char> sfleta_l3;
  ASSERT_EQ(sfleta_l3.empty(), true);

  s21::list<std::string> sfleta_l4;
  ASSERT_EQ(sfleta_l4.empty(), true);
}

TEST(list_ConstructorsTests, costr_parameterized) {
  s21::list<int> sfleta_l1(5);
  ASSERT_EQ(sfleta_l1.size(), 5);

  s21::list<double> sfleta_l2(5);
  ASSERT_EQ(sfleta_l2.size(), 5);

  s21::list<char> sfleta_l3(5);
  ASSERT_EQ(sfleta_l3.size(), 5);

  s21::list<char> sfleta_l4(5);
  ASSERT_EQ(sfleta_l4.size(), 5);
}

TEST(list_ConstructorsTests, costr_initializer) {
  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3{'1', '2', '3', '4'};
  s21::list<char> sfleta_l3{'1', '2', '3', '4'};
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ConstructorsTests, costr_copy) {
  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  s21::list<int> sfleta_cl1(sfleta_l1);
  ASSERT_TRUE(lists_eq(sfleta_cl1, std_l1));

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_cl2(sfleta_l2);
  ASSERT_TRUE(lists_eq(sfleta_cl2, std_l2));

  std::list<char> std_l3{'1', '2', '3', '4'};
  s21::list<char> sfleta_l3{'1', '2', '3', '4'};
  s21::list<char> sfleta_cl3(sfleta_l3);
  ASSERT_TRUE(lists_eq(sfleta_cl3, std_l3));

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_cl4(sfleta_l4);
  ASSERT_TRUE(lists_eq(sfleta_cl4, std_l4));
}

TEST(list_ConstructorsTests, costr_move) {
  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  s21::list<int> sfleta_ml1(std::move(sfleta_l1));
  ASSERT_TRUE(lists_eq(sfleta_ml1, std_l1));
  ASSERT_EQ(sfleta_l1.size(), 0);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_ml2(std::move(sfleta_l2));
  ASSERT_TRUE(lists_eq(sfleta_ml2, std_l2));
  ASSERT_EQ(sfleta_l2.size(), 0);

  std::list<char> std_l3{'1', '2', '3', '4'};
  s21::list<char> sfleta_l3{'1', '2', '3', '4'};
  s21::list<char> sfleta_ml3(std::move(sfleta_l3));
  ASSERT_TRUE(lists_eq(sfleta_ml3, std_l3));
  ASSERT_EQ(sfleta_l3.size(), 0);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_ml4(std::move(sfleta_l4));
  ASSERT_TRUE(lists_eq(sfleta_ml4, std_l4));
  ASSERT_EQ(sfleta_l3.size(), 0);
}

TEST(list_ElementAccessTests, front) {
  s21::list<int> sfleta_l0;
  s21::list<int>::const_reference f0 = sfleta_l0.front();
  ASSERT_EQ(f0, 0);

  s21::list<int> sfleta_l1{1, 2, 3, 4};
  s21::list<int>::const_reference f1 = sfleta_l1.front();
  ASSERT_EQ(f1, 1);

  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double>::const_reference f2 = sfleta_l2.front();
  ASSERT_EQ(f2, 1.1);

  s21::list<char> sfleta_l3{'1', '2', '3', '4'};
  s21::list<char>::const_reference f3 = sfleta_l3.front();
  ASSERT_EQ(f3, '1');

  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  s21::list<std::string>::const_reference f4 = sfleta_l4.front();
  ASSERT_EQ(f4, "one");
}

TEST(list_ElementAccessTests, back) {
  s21::list<int> sfleta_l0;
  s21::list<int>::const_reference f0 = sfleta_l0.back();
  ASSERT_EQ(f0, 0);

  s21::list<int> sfleta_l1{1, 2, 3, 4};
  s21::list<int>::const_reference f1 = sfleta_l1.back();
  ASSERT_EQ(f1, 4);

  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double>::const_reference f2 = sfleta_l2.back();
  ASSERT_EQ(f2, 4.4);

  s21::list<char> sfleta_l3{'1', '2', '3', '4'};
  s21::list<char>::const_reference f3 = sfleta_l3.back();
  ASSERT_EQ(f3, '4');

  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  s21::list<std::string>::const_reference f4 = sfleta_l4.back();
  ASSERT_EQ(f4, "four");
}

TEST(list_CapacityTests, size) {
  s21::list<int> sfleta_l0;
  ASSERT_EQ(sfleta_l0.size(), 0);

  s21::list<int> sfleta_l1{1, 2, 3, 4};
  ASSERT_EQ(sfleta_l1.size(), 4);
}

TEST(list_CapacityTests, max_size) {
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  ASSERT_EQ(sfleta_l1.max_size(), 384307168202282325);

  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  ASSERT_EQ(sfleta_l2.max_size(), 384307168202282325);

  s21::list<char> sfleta_l3{'1', '2', '3', '4'};
  ASSERT_EQ(sfleta_l3.max_size(), 384307168202282325);

  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  ASSERT_EQ(sfleta_l4.max_size(), 192153584101141162);
}

TEST(list_ModifiersTests, push_front) {
  std::list<int> std_l0{1};
  s21::list<int> sfleta_l0;
  sfleta_l0.push_front(1);
  ASSERT_TRUE(lists_eq(sfleta_l0, std_l0));

  std::list<int> std_l1{2, 1};
  s21::list<int> sfleta_l1{1};
  sfleta_l1.push_front(2);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2{2.2, 1.1};
  s21::list<double> sfleta_l2{1.1};
  sfleta_l2.push_front(2.2);
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3{'2', '1'};
  s21::list<char> sfleta_l3{'1'};
  sfleta_l3.push_front('2');
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4{"two", "one"};
  s21::list<std::string> sfleta_l4{"one"};
  sfleta_l4.push_front("two");
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ModifiersTests, push_back) {
  std::list<int> std_l0{1};
  s21::list<int> sfleta_l0;
  sfleta_l0.push_back(1);
  ASSERT_TRUE(lists_eq(sfleta_l0, std_l0));

  std::list<int> std_l1{2, 1, 3};
  s21::list<int> sfleta_l1{2, 1};
  sfleta_l1.push_back(3);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2{2.2, 1.1, 3.3};
  s21::list<double> sfleta_l2{2.2, 1.1};
  sfleta_l2.push_back(3.3);
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3{'2', '1', '3'};
  s21::list<char> sfleta_l3{'2', '1'};
  sfleta_l3.push_back('3');
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4{"two", "one", "three"};
  s21::list<std::string> sfleta_l4{"two", "one"};
  sfleta_l4.push_back("three");
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ModifiersTests, pop_front) {
  std::list<int> std_l0;
  s21::list<int> sfleta_l0{1};
  sfleta_l0.pop_front();
  ASSERT_TRUE(lists_eq(sfleta_l0, std_l0));

  std::list<int> std_l1{1, 3};
  s21::list<int> sfleta_l1{2, 1, 3};
  sfleta_l1.pop_front();
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2{1.1, 3.3};
  s21::list<double> sfleta_l2{2.2, 1.1, 3.3};
  sfleta_l2.pop_front();
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3{'1', '3'};
  s21::list<char> sfleta_l3{'2', '1', '3'};
  sfleta_l3.pop_front();
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4{"one", "three"};
  s21::list<std::string> sfleta_l4{"two", "one", "three"};
  sfleta_l4.pop_front();
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ModifiersTests, pop_back) {
  std::list<int> std_l0;
  s21::list<int> sfleta_l0{1};
  sfleta_l0.pop_back();
  ASSERT_TRUE(lists_eq(sfleta_l0, std_l0));

  std::list<int> std_l1{2, 1};
  s21::list<int> sfleta_l1{2, 1, 3};
  sfleta_l1.pop_back();
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2{2.2, 1.1};
  s21::list<double> sfleta_l2{2.2, 1.1, 3.3};
  sfleta_l2.pop_back();
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3{'2', '1'};
  s21::list<char> sfleta_l3{'2', '1', '3'};
  sfleta_l3.pop_back();
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4{"two", "one"};
  s21::list<std::string> sfleta_l4{"two", "one", "three"};
  sfleta_l4.pop_back();
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ModifiersTests, clear) {
  std::list<int> std_l1;
  s21::list<int> sfleta_l1{2, 1, 3};
  sfleta_l1.clear();
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2;
  s21::list<double> sfleta_l2{2.2, 1.1, 3.3};
  sfleta_l2.clear();
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3;
  s21::list<char> sfleta_l3{'2', '1', '3'};
  sfleta_l3.clear();
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4;
  s21::list<std::string> sfleta_l4{"two", "one", "three"};
  sfleta_l4.clear();
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ModifiersTests, swap) {
  std::list<int> std_l11;
  s21::list<int> sfleta_l11{2, 1, 3};
  std::list<int> std_l12{2, 1, 3};
  s21::list<int> sfleta_l12;
  sfleta_l12.swap(sfleta_l11);
  ASSERT_TRUE(lists_eq(sfleta_l11, std_l11));
  ASSERT_TRUE(lists_eq(sfleta_l12, std_l12));

  std::list<double> std_l21;
  s21::list<double> sfleta_l21{2.2, 1.1, 3.3};
  std::list<double> std_l22{2.2, 1.1, 3.3};
  s21::list<double> sfleta_l22;
  sfleta_l22.swap(sfleta_l21);
  ASSERT_TRUE(lists_eq(sfleta_l21, std_l21));
  ASSERT_TRUE(lists_eq(sfleta_l22, std_l22));

  std::list<char> std_l31;
  s21::list<char> sfleta_l31{'2', '1', '3'};
  std::list<char> std_l32{'2', '1', '3'};
  s21::list<char> sfleta_l32;
  sfleta_l32.swap(sfleta_l31);
  ASSERT_TRUE(lists_eq(sfleta_l31, std_l31));
  ASSERT_TRUE(lists_eq(sfleta_l32, std_l32));

  std::list<std::string> std_l41;
  s21::list<std::string> sfleta_l41{"two", "one", "three"};
  std::list<std::string> std_l42{"two", "one", "three"};
  s21::list<std::string> sfleta_l42;
  sfleta_l42.swap(sfleta_l41);
  ASSERT_TRUE(lists_eq(sfleta_l41, std_l41));
  ASSERT_TRUE(lists_eq(sfleta_l42, std_l42));
}

TEST(list_ModifiersTests, reverse) {
  std::list<int> std_l1{2, 1, 3};
  s21::list<int> sfleta_l1{2, 1, 3};
  sfleta_l1.reverse();
  sfleta_l1.reverse();
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2{2.2, 1.1, 3.3};
  s21::list<double> sfleta_l2{2.2, 1.1, 3.3};
  sfleta_l2.reverse();
  sfleta_l2.reverse();
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3{'2', '1', '3'};
  s21::list<char> sfleta_l3{'2', '1', '3'};
  sfleta_l3.reverse();
  sfleta_l3.reverse();
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4{"two", "one", "three"};
  s21::list<std::string> sfleta_l4{"two", "one", "three"};
  std_l4.reverse();
  sfleta_l4.reverse();
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));

  std::list<int> std_l5{5, 34, 56, 2, 3};
  s21::list<int> sfleta_l5{5, 34, 56, 2, 3};
  std_l5.reverse();
  sfleta_l5.reverse();
  ASSERT_TRUE(lists_eq(sfleta_l5, std_l5));

  std::list<int> std_l6{5, 34, 56, 2};
  s21::list<int> sfleta_l6{5, 34, 56, 2};
  std_l6.reverse();
  sfleta_l6.reverse();
  ASSERT_TRUE(lists_eq(sfleta_l6, std_l6));
}

TEST(list_ModifiersTests, operator_move) {
  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  s21::list<int> sfleta_ml1;
  sfleta_ml1 = std::move(sfleta_l1);
  ASSERT_TRUE(lists_eq(sfleta_ml1, std_l1));
  ASSERT_EQ(sfleta_l1.size(), 0);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_ml2;
  sfleta_ml2 = std::move(sfleta_l2);
  ASSERT_TRUE(lists_eq(sfleta_ml2, std_l2));
  ASSERT_EQ(sfleta_l2.size(), 0);

  std::list<char> std_l3{'1', '2', '3', '4'};
  s21::list<char> sfleta_l3{'1', '2', '3', '4'};
  s21::list<char> sfleta_ml3;
  sfleta_ml3 = std::move(sfleta_l3);
  ASSERT_TRUE(lists_eq(sfleta_ml3, std_l3));
  ASSERT_EQ(sfleta_l3.size(), 0);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_ml4;
  sfleta_ml4 = std::move(sfleta_l4);
  ASSERT_TRUE(lists_eq(sfleta_ml4, std_l4));
  ASSERT_EQ(sfleta_l3.size(), 0);
}

TEST(list_ModifiersTests, empty) {
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  ASSERT_FALSE(sfleta_l1.empty());
  sfleta_l1.clear();
  ASSERT_TRUE(sfleta_l1.empty());

  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  ASSERT_FALSE(sfleta_l2.empty());
  sfleta_l2.clear();
  ASSERT_TRUE(sfleta_l2.empty());

  s21::list<char> sfleta_l3{'1', '2', '3', '4'};
  ASSERT_FALSE(sfleta_l3.empty());
  sfleta_l3.clear();
  ASSERT_TRUE(sfleta_l3.empty());

  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  ASSERT_FALSE(sfleta_l4.empty());
  sfleta_l4.clear();
  ASSERT_TRUE(sfleta_l4.empty());
}

TEST(list_ModifiersTests, sort) {
  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{4, 2, 3, 1};
  sfleta_l1.sort();
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{4.4, 3.3, 2.2, 1.1};
  sfleta_l2.sort();
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3{'1', '3', '3', '4'};
  s21::list<char> sfleta_l3{'4', '1', '3', '3'};
  sfleta_l3.sort();
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4{"fourtt", "on", "three", "two"};
  s21::list<std::string> sfleta_l4{"on", "two", "three", "fourtt"};
  sfleta_l4.sort();
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ConstructorsIteratorTests, iterator) {
  s21::list<int>::iterator sfleta_it1;
  ASSERT_EQ(sfleta_it1.pNode_, nullptr);

  s21::Node<int> sfleta_n2(5);
  s21::list<int>::iterator sfleta_it2(&sfleta_n2);
  ASSERT_EQ(sfleta_it2.pNode_->data_, sfleta_n2.data_);

  s21::list<int> sfleta_l3{1, 2, 3, 4};
  s21::list<int>::iterator sfleta_it3(sfleta_l3);
  ASSERT_EQ(sfleta_it3.pNode_->data_, sfleta_l3.front());

  s21::list<int>::iterator sfleta_it4(sfleta_it3);
  ASSERT_EQ(sfleta_it3.pNode_->data_, sfleta_it4.pNode_->data_);
}

TEST(list_ConstructorsConstIteratorTests, const_iterator) {
  s21::list<int>::const_iterator sfleta_it1;
  ASSERT_EQ(sfleta_it1.pNode_, nullptr);

  s21::Node<int> sfleta_n2(5);
  s21::list<int>::const_iterator sfleta_it2(&sfleta_n2);
  ASSERT_EQ(sfleta_it2.pNode_->data_, sfleta_n2.data_);

  s21::list<int> sfleta_l3{1, 2, 3, 4};
  s21::list<int>::const_iterator sfleta_it3(sfleta_l3);
  ASSERT_EQ(sfleta_it3.pNode_->data_, sfleta_l3.front());

  s21::list<int>::const_iterator sfleta_it4(sfleta_it3);
  ASSERT_EQ(sfleta_it3.pNode_->data_, sfleta_it4.pNode_->data_);
}

TEST(list_OperatorsIteratorTests, operators_iterator) {
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  s21::list<int>::iterator sfleta_it1(sfleta_l1);
  ASSERT_EQ(*sfleta_it1, 1);
  ++sfleta_it1;
  ++sfleta_it1;
  ASSERT_EQ(*sfleta_it1, 3);
  --sfleta_it1;
  ASSERT_EQ(*sfleta_it1, 2);
  s21::list<int>::iterator sfleta_it2;
  sfleta_it2 = sfleta_it1;
  ASSERT_EQ(*sfleta_it1, *sfleta_it2);
  ASSERT_FALSE(sfleta_it1 != sfleta_it2);
  ++sfleta_it2;
  ASSERT_TRUE(sfleta_it1 != sfleta_it2);
  ASSERT_FALSE(sfleta_it1 == sfleta_it2);
  --sfleta_it2;
  ASSERT_TRUE(sfleta_it1 == sfleta_it2);

  s21::list<int>::const_iterator sfleta_it3(sfleta_l1);
  ASSERT_EQ(*sfleta_it3, 1);
}

TEST(list_ModifiersTests, begin) {
  std::list<int> std_l0;
  s21::list<int> sfleta_l0;
  std::list<int>::iterator std_it0 = std_l0.begin();
  s21::list<int>::iterator sfleta_it0 = sfleta_l0.begin();
  ASSERT_TRUE(*std_it0 == *sfleta_it0);

  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  std::list<int>::iterator std_it1 = std_l1.begin();
  s21::list<int>::iterator sfleta_it1 = sfleta_l1.begin();
  ASSERT_TRUE(*std_it1 == *sfleta_it1);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  std::list<double>::iterator std_it2 = std_l2.begin();
  s21::list<double>::iterator sfleta_it2 = sfleta_l2.begin();
  ASSERT_TRUE(*std_it2 == *sfleta_it2);

  std::list<char> std_l3{'1', '3', '3', '4'};
  s21::list<char> sfleta_l3{'1', '3', '3', '4'};
  std::list<char>::iterator std_it3 = std_l3.begin();
  s21::list<char>::iterator sfleta_it3 = sfleta_l3.begin();
  ASSERT_TRUE(*std_it3 == *sfleta_it3);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  std::list<std::string>::iterator std_it4 = std_l4.begin();
  s21::list<std::string>::iterator sfleta_it4 = sfleta_l4.begin();
  ASSERT_TRUE(*std_it4 == *sfleta_it4);
}

TEST(list_ModifiersTests, end) {
  std::list<int> std_l0;
  s21::list<int> sfleta_l0;
  std::list<int>::iterator std_it0 = std_l0.end();
  s21::list<int>::iterator sfleta_it0 = sfleta_l0.end();
  ASSERT_TRUE(*std_it0 == *sfleta_it0);

  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  std::list<int>::iterator std_it1 = ++std_l1.end();
  s21::list<int>::iterator sfleta_it1 = ++sfleta_l1.end();
  ASSERT_TRUE(*std_it1 == *sfleta_it1);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  std::list<double>::iterator std_it2 = --std_l2.end();
  s21::list<double>::iterator sfleta_it2 = --sfleta_l2.end();
  ASSERT_TRUE(*std_it2 == *sfleta_it2);

  std::list<char> std_l3{'1', '3', '3', '4'};
  s21::list<char> sfleta_l3{'1', '3', '3', '4'};
  std::list<char>::iterator std_it3 = ++std_l3.end();
  s21::list<char>::iterator sfleta_it3 = ++sfleta_l3.end();
  ASSERT_TRUE(*std_it3 == *sfleta_it3);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  std::list<std::string>::iterator std_it4 = --std_l4.end();
  s21::list<std::string>::iterator sfleta_it4 = --sfleta_l4.end();
  ASSERT_TRUE(*std_it4 == *sfleta_it4);
}

TEST(list_ModifiersTests, cbegin) {
  std::list<int> std_l0;
  s21::list<int> sfleta_l0;
  std::list<int>::const_iterator std_it0 = std_l0.cbegin();
  s21::list<int>::const_iterator sfleta_it0 = sfleta_l0.cbegin();
  ASSERT_TRUE(*std_it0 == *sfleta_it0);

  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  ASSERT_TRUE(*std_it1 == *sfleta_it1);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  std::list<double>::const_iterator std_it2 = std_l2.cbegin();
  s21::list<double>::const_iterator sfleta_it2 = sfleta_l2.cbegin();
  ASSERT_TRUE(*std_it2 == *sfleta_it2);

  std::list<char> std_l3{'1', '3', '3', '4'};
  s21::list<char> sfleta_l3{'1', '3', '3', '4'};
  std::list<char>::const_iterator std_it3 = std_l3.cbegin();
  s21::list<char>::const_iterator sfleta_it3 = sfleta_l3.cbegin();
  ASSERT_TRUE(*std_it3 == *sfleta_it3);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  std::list<std::string>::const_iterator std_it4 = std_l4.cbegin();
  s21::list<std::string>::const_iterator sfleta_it4 = sfleta_l4.cbegin();
  ASSERT_TRUE(*std_it4 == *sfleta_it4);
}

TEST(list_ModifiersTests, cend) {
  std::list<int> std_l0;
  s21::list<int> sfleta_l0;
  std::list<int>::const_iterator std_it0 = std_l0.cend();
  s21::list<int>::const_iterator sfleta_it0 = sfleta_l0.cend();
  ASSERT_TRUE(*std_it0 == *sfleta_it0);

  std::list<int> std_l1{1, 2, 3, 4};
  s21::list<int> sfleta_l1{1, 2, 3, 4};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cend();
  ++std_it1;
  ++sfleta_it1;
  ASSERT_TRUE(*std_it1 == *sfleta_it1);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4};
  std::list<double>::const_iterator std_it2 = std_l2.cend();
  s21::list<double>::const_iterator sfleta_it2 = sfleta_l2.cend();
  --std_it2;
  --sfleta_it2;
  ASSERT_TRUE(*std_it2 == *sfleta_it2);

  std::list<char> std_l3{'1', '3', '3', '4'};
  s21::list<char> sfleta_l3{'1', '3', '3', '4'};
  std::list<char>::const_iterator std_it3 = std_l3.cend();
  s21::list<char>::const_iterator sfleta_it3 = sfleta_l3.cend();
  ++std_it3;
  ++sfleta_it3;
  ASSERT_TRUE(*std_it3 == *sfleta_it3);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four"};
  std::list<std::string>::const_iterator std_it4 = std_l4.cend();
  s21::list<std::string>::const_iterator sfleta_it4 = sfleta_l4.cend();
  --std_it4;
  --sfleta_it4;
  ASSERT_TRUE(*std_it4 == *sfleta_it4);
}

TEST(list_ModifiersTests, erase) {
  std::list<int> std_l1{1, 2, 3, 4, 5};
  s21::list<int> sfleta_l1{1, 2, 3, 4, 5};
  std::list<int>::iterator std_it1 = --std_l1.end();
  s21::list<int>::iterator sfleta_it1 = --sfleta_l1.end();
  std_l1.erase(std_it1);
  sfleta_l1.erase(sfleta_it1);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  std_it1 = std_l1.begin();
  sfleta_it1 = sfleta_l1.begin();
  std_l1.erase(std_it1);
  sfleta_l1.erase(sfleta_it1);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  std_it1 = std_l1.begin();
  sfleta_it1 = sfleta_l1.begin();
  ++std_it1;
  ++sfleta_it1;
  std_l1.erase(std_it1);
  sfleta_l1.erase(sfleta_it1);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4, 5.5};
  s21::list<double> sfleta_l2{1.1, 2.2, 3.3, 4.4, 5.5};
  std::list<double>::iterator std_it2 = --std_l2.end();
  s21::list<double>::iterator sfleta_it2 = --sfleta_l2.end();
  std_l2.erase(std_it2);
  sfleta_l2.erase(sfleta_it2);
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));
  std_it2 = std_l2.begin();
  sfleta_it2 = sfleta_l2.begin();
  std_l2.erase(std_it2);
  sfleta_l2.erase(sfleta_it2);
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));
  std_it2 = std_l2.begin();
  sfleta_it2 = sfleta_l2.begin();
  ++std_it2;
  ++sfleta_it2;
  std_l2.erase(std_it2);
  sfleta_l2.erase(sfleta_it2);
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));

  std::list<char> std_l3{'1', '3', '3', '4', '5'};
  s21::list<char> sfleta_l3{'1', '3', '3', '4', '5'};
  std::list<char>::iterator std_it3 = --std_l3.end();
  s21::list<char>::iterator sfleta_it3 = --sfleta_l3.end();
  std_l3.erase(std_it3);
  sfleta_l3.erase(sfleta_it3);
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));
  std_it3 = std_l3.begin();
  sfleta_it3 = sfleta_l3.begin();
  std_l3.erase(std_it3);
  sfleta_l3.erase(sfleta_it3);
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));
  std_it3 = std_l3.begin();
  sfleta_it3 = sfleta_l3.begin();
  ++std_it3;
  ++sfleta_it3;
  std_l3.erase(std_it3);
  sfleta_l3.erase(sfleta_it3);
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));

  std::list<std::string> std_l4{"one", "two", "three", "four", "five"};
  s21::list<std::string> sfleta_l4{"one", "two", "three", "four", "five"};
  std::list<std::string>::iterator std_it4 = --std_l4.end();
  s21::list<std::string>::iterator sfleta_it4 = --sfleta_l4.end();
  std_l4.erase(std_it4);
  sfleta_l4.erase(sfleta_it4);
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
  std_it4 = std_l4.begin();
  sfleta_it4 = sfleta_l4.begin();
  std_l4.erase(std_it4);
  sfleta_l4.erase(sfleta_it4);
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
  std_it4 = std_l4.begin();
  sfleta_it4 = sfleta_l4.begin();
  ++std_it4;
  ++sfleta_it4;
  std_l4.erase(std_it4);
  sfleta_l4.erase(sfleta_it4);
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ModifiersTests, unique_1) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> sfleta_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std_l1.unique();
  sfleta_l1.unique();
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, unique_2) {
  std::list<int> std_l2{0, 0, 1, 2, 2, 3, 3};
  s21::list<int> sfleta_l2{0, 0, 1, 2, 2, 3, 3};
  std_l2.unique();
  sfleta_l2.unique();
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));
}

TEST(list_ModifiersTests, unique_3) {
  std::list<int> std_l3{0, 0, 1, 2, 2, 3, 3, 0};
  s21::list<int> sfleta_l3{0, 0, 1, 2, 2, 3, 3, 0};
  std_l3.unique();
  sfleta_l3.unique();
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));
}

TEST(list_ModifiersTests, unique_4) {
  std::list<int> std_l4{0, 0, 1, 2, 2, 3, 3, 2, 0};
  s21::list<int> sfleta_l4{0, 0, 1, 2, 2, 3, 3, 2, 0};
  std_l4.unique();
  sfleta_l4.unique();
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ModifiersTests, unique_5) {
  std::list<int> std_l5{0, 0, 1, 2, 2, 3, 3, 2, 0, 5, 5};
  s21::list<int> sfleta_l5{0, 0, 1, 2, 2, 3, 3, 2, 0, 5, 5};
  std_l5.unique();
  sfleta_l5.unique();
  ASSERT_TRUE(lists_eq(sfleta_l5, std_l5));
}

TEST(list_ModifiersTests, insert) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> sfleta_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int>::iterator std_it1 = std_l1.begin();
  s21::list<int>::iterator sfleta_it1 = sfleta_l1.begin();

  std_l1.insert(std_it1, 100);
  sfleta_l1.insert(sfleta_it1, 100);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  ++std_it1;
  ++sfleta_it1;
  std_l1.insert(std_it1, 99);
  sfleta_l1.insert(sfleta_it1, 99);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  ++std_it1;
  ++sfleta_it1;
  std_l1.insert(std_it1, 89);
  sfleta_l1.insert(sfleta_it1, 89);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std_it1 = std_l1.end();
  sfleta_it1 = sfleta_l1.end();
  std_l1.insert(std_it1, 79);
  sfleta_l1.insert(sfleta_it1, 79);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  ++std_it1;
  ++sfleta_it1;
  std_l1.insert(std_it1, 44);
  sfleta_l1.insert(sfleta_it1, 44);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  ++std_it1;
  ++sfleta_it1;
  std_l1.insert(std_it1, 34);
  sfleta_l1.insert(sfleta_it1, 34);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  --std_it1;
  --sfleta_it1;
  --std_it1;
  --sfleta_it1;
  --std_it1;
  --sfleta_it1;
  std_l1.insert(std_it1, -26);
  sfleta_l1.insert(sfleta_it1, -26);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  --std_it1;
  --sfleta_it1;
  std_l1.insert(std_it1, -16);
  sfleta_l1.insert(sfleta_it1, -16);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  --std_it1;
  --sfleta_it1;
  std_l1.insert(std_it1, -13);
  sfleta_l1.insert(sfleta_it1, -13);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  --std_it1;
  --sfleta_it1;
  --std_it1;
  --sfleta_it1;
  --std_it1;
  --sfleta_it1;
  std_l1.insert(std_it1, -3);
  sfleta_l1.insert(sfleta_it1, -3);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  --std_it1;
  --sfleta_it1;
  --std_it1;
  --sfleta_it1;
  --std_it1;
  --sfleta_it1;
  std_l1.insert(std_it1, 0);
  sfleta_l1.insert(sfleta_it1, 0);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std_l1.clear();
  sfleta_l1.clear();
  std_it1 = std_l1.begin();
  sfleta_it1 = sfleta_l1.begin();

  std_l1.insert(std_it1, 56);
  sfleta_l1.insert(sfleta_it1, 56);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  std_l1.clear();
  sfleta_l1.clear();
  std_it1 = std_l1.end();
  sfleta_it1 = sfleta_l1.end();

  std_l1.insert(std_it1, 70);
  sfleta_l1.insert(sfleta_it1, 70);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));

  --std_it1;
  --sfleta_it1;
  std_l1.insert(std_it1, -22);
  sfleta_l1.insert(sfleta_it1, -22);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, merge_1) {
  std::list<int> std_l1{6, 3, 9};
  std::list<int> std_l2;
  s21::list<int> sfleta_l1{6, 3, 9};
  s21::list<int> sfleta_l2;
  std_l2.merge(std_l1);
  sfleta_l2.merge(sfleta_l1);
  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(lists_eq(sfleta_l2, std_l2));
}

TEST(list_ModifiersTests, merge_2) {
  std::list<int> std_l3{6, 3, 9};
  std::list<int> std_l4;
  s21::list<int> sfleta_l3{6, 3, 9};
  s21::list<int> sfleta_l4;
  std_l3.sort();
  sfleta_l3.sort();
  std_l4.merge(std_l3);
  sfleta_l4.merge(sfleta_l3);
  ASSERT_TRUE(lists_eq(sfleta_l3, std_l3));
  ASSERT_TRUE(lists_eq(sfleta_l4, std_l4));
}

TEST(list_ModifiersTests, merge_3) {
  std::list<int> std_l5;
  std::list<int> std_l6{4, 2};
  s21::list<int> sfleta_l5;
  s21::list<int> sfleta_l6{4, 2};
  std_l6.merge(std_l5);
  sfleta_l6.merge(sfleta_l5);
  ASSERT_TRUE(lists_eq(sfleta_l5, std_l5));
  ASSERT_TRUE(lists_eq(sfleta_l6, std_l6));
}

TEST(list_ModifiersTests, merge_4) {
  std::list<int> std_l7;
  std::list<int> std_l8{4, 2};
  s21::list<int> sfleta_l7;
  s21::list<int> sfleta_l8{4, 2};
  std_l8.sort();
  sfleta_l8.sort();
  std_l8.merge(std_l7);
  sfleta_l8.merge(sfleta_l7);
  ASSERT_TRUE(lists_eq(sfleta_l7, std_l7));
  ASSERT_TRUE(lists_eq(sfleta_l8, std_l8));
}

TEST(list_ModifiersTests, merge_5) {
  std::list<int> std_l9{9, 6, 3};
  std::list<int> std_l10{4, 2, 7};
  s21::list<int> sfleta_l9{9, 6, 3};
  s21::list<int> sfleta_l10{4, 2, 7};
  std_l10.merge(std_l9);
  sfleta_l10.merge(sfleta_l9);
  ASSERT_TRUE(lists_eq(sfleta_l9, std_l9));
  ASSERT_TRUE(lists_eq(sfleta_l10, std_l10));
}

TEST(list_ModifiersTests, merge_6) {
  std::list<int> std_l11{9, 6, 3};
  std::list<int> std_l12{4, 2, 7};
  s21::list<int> sfleta_l11{9, 6, 3};
  s21::list<int> sfleta_l12{4, 2, 7};
  std_l11.sort();
  sfleta_l11.sort();
  std_l12.sort();
  sfleta_l12.sort();
  std_l12.merge(std_l11);
  sfleta_l12.merge(sfleta_l11);
  ASSERT_TRUE(lists_eq(sfleta_l11, std_l11));
  ASSERT_TRUE(lists_eq(sfleta_l12, std_l12));
}

TEST(list_ModifiersTests, merge_7) {
  std::list<int> std_l13{-9, -6, -3};
  std::list<int> std_l14{-4, -2, -7};
  s21::list<int> sfleta_l13{-9, -6, -3};
  s21::list<int> sfleta_l14{-4, -2, -7};
  std_l14.merge(std_l13);
  sfleta_l14.merge(sfleta_l13);
  ASSERT_TRUE(lists_eq(sfleta_l13, std_l13));
  ASSERT_TRUE(lists_eq(sfleta_l14, std_l14));
}

TEST(list_ModifiersTests, splice_1) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std_l1.splice(std_it1, std_l2);

  s21::list<int> sfleta_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> sfleta_l2{9, 6, 3};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  sfleta_l1.splice(sfleta_it1, sfleta_l2);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, splice_2) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  std_l1.splice(std_it1, std_l2);

  s21::list<int> sfleta_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> sfleta_l2{9, 6, 3};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cend();
  sfleta_l1.splice(sfleta_it1, sfleta_l2);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, splice_3) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  --std_it1;
  std_l1.splice(std_it1, std_l2);

  s21::list<int> sfleta_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> sfleta_l2{9, 6, 3};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cend();
  --sfleta_it1;
  sfleta_l1.splice(sfleta_it1, sfleta_l2);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, splice_4) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std_l1.splice(std_it1, std_l2);

  s21::list<int> sfleta_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> sfleta_l2{9, 6, 3};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  ++sfleta_it1;
  sfleta_l1.splice(sfleta_it1, sfleta_l2);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, splice_5) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2;
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std_l1.splice(std_it1, std_l2);

  s21::list<int> sfleta_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> sfleta_l2;
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  ++sfleta_it1;
  sfleta_l1.splice(sfleta_it1, sfleta_l2);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, splice_6) {
  std::list<int> std_l1;
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std_l1.splice(std_it1, std_l2);

  s21::list<int> sfleta_l1;
  s21::list<int> sfleta_l2{9, 6, 3};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  ++sfleta_it1;
  sfleta_l1.splice(sfleta_it1, sfleta_l2);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, emplace_1) {
  std::list<int> std_l1;
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std_l1.emplace(std_it1);

  s21::list<int> sfleta_l1;
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  sfleta_l1.emplace(sfleta_it1);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
}

TEST(list_ModifiersTests, emplace_2) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std::list<int>::iterator std_r1 = std_l1.emplace(std_it1);

  s21::list<int> sfleta_l1{9, 6, 3, 7};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_3) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std::list<int>::iterator std_r1 = std_l1.emplace(std_it1);

  s21::list<int> sfleta_l1{9, 6, 3, 7};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  ++sfleta_it1;
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_4) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  --std_it1;
  std::list<int>::iterator std_r1 = std_l1.emplace(std_it1);

  s21::list<int> sfleta_l1{9, 6, 3, 7};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cend();
  --sfleta_it1;
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_5) {
  std::list<int> std_l1;
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  s21::list<int> sfleta_l1;
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1, 5, 10);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_6) {
  std::list<int> std_l1;
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  s21::list<int> sfleta_l1;
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cend();
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1, 5, 10);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_7) {
  std::list<int> std_l1;
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  --std_it1;
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  s21::list<int> sfleta_l1;
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cend();
  --sfleta_it1;
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1, 5, 10);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_8) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  s21::list<int> sfleta_l1{9, 6, 3, 7};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1, 5, 10);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_9) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  s21::list<int> sfleta_l1{9, 6, 3, 7};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  ++sfleta_it1;
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1, 5, 10);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_10) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_l1.emplace(std_it1, 10);
  std_r1 = std_l1.emplace(std_it1, 15);

  s21::list<int> sfleta_l1{9, 6, 3, 7};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cbegin();
  ++sfleta_it1;
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1, 5, 10, 15);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_11) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_l1.emplace(std_it1, 10);
  std_r1 = std_l1.emplace(std_it1, 15);

  s21::list<int> sfleta_l1{9, 6, 3, 7};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cend();
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1, 5, 10, 15);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_12) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  --std_it1;
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_l1.emplace(std_it1, 10);
  std_r1 = std_l1.emplace(std_it1, 15);

  s21::list<int> sfleta_l1{9, 6, 3, 7};
  s21::list<int>::const_iterator sfleta_it1 = sfleta_l1.cend();
  --sfleta_it1;
  s21::list<int>::iterator sfleta_r1 = sfleta_l1.emplace(sfleta_it1, 5, 10, 15);

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *sfleta_r1);
}

TEST(list_ModifiersTests, emplace_back_1) {
  std::list<int> std_l1;
  std_l1.emplace_back();
  std_l1.emplace_back();
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1;
  sfleta_l1.emplace_back();
  sfleta_l1.emplace_back();
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_back_2) {
  std::list<int> std_l1;
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1;
  sfleta_l1.emplace_back(5);
  sfleta_l1.emplace_back(10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_back_3) {
  std::list<int> std_l1;
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1;
  sfleta_l1.emplace_back(5, 10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_back_4) {
  std::list<int> std_l1;
  std_l1.emplace_back();
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1;
  sfleta_l1.emplace_back();
  sfleta_l1.emplace_back(10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_back_5) {
  std::list<int> std_l1;
  std_l1.emplace_back();
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1;
  sfleta_l1.emplace_back();
  sfleta_l1.emplace_back(5, 10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_back_6) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_back();
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1{99, 100};
  sfleta_l1.emplace_back();
  sfleta_l1.emplace_back(5);
  sfleta_l1.emplace_back(10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_back_7) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_back();
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1{99, 100};
  sfleta_l1.emplace_back();
  sfleta_l1.emplace_back(5, 10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_back_8) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1{99, 100};
  sfleta_l1.emplace_back(5, 10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_back_9) {
  std::list<std::string> std_l1;
  std_l1.emplace_back();
  std_l1.emplace_back();
  size_t std_size = std_l1.size();

  s21::list<std::string> sfleta_l1;
  sfleta_l1.emplace_back();
  sfleta_l1.emplace_back();
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_front_1) {
  std::list<int> std_l1;
  std_l1.emplace_front();
  std_l1.emplace_front();
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1;
  sfleta_l1.emplace_front();
  sfleta_l1.emplace_front();
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_front_2) {
  std::list<std::string> std_l1;
  std_l1.emplace_front();
  std_l1.emplace_front();
  size_t std_size = std_l1.size();

  s21::list<std::string> sfleta_l1;
  sfleta_l1.emplace_front();
  sfleta_l1.emplace_front();
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_front_3) {
  std::list<int> std_l1;
  std_l1.emplace_front(5);
  std_l1.emplace_front(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1;
  sfleta_l1.emplace_front(5);
  sfleta_l1.emplace_front(10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_front_4) {
  std::list<int> std_l1;
  std_l1.emplace_front();
  std_l1.emplace_front(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1;
  sfleta_l1.emplace_front();
  sfleta_l1.emplace_front(10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_front_5) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_front();
  std_l1.emplace_front(5);
  std_l1.emplace_front(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1{99, 100};
  sfleta_l1.emplace_front();
  sfleta_l1.emplace_front(5);
  sfleta_l1.emplace_front(10);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}

TEST(list_ModifiersTests, emplace_front_6) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_front(5);
  std_l1.emplace_front(10);
  size_t std_size = std_l1.size();

  s21::list<int> sfleta_l1{99, 100};
  sfleta_l1.emplace_front(10, 5);
  s21::list<int>::size_type sfleta_size = std_l1.size();

  ASSERT_TRUE(lists_eq(sfleta_l1, std_l1));
  ASSERT_TRUE(std_size == sfleta_size);
}
/* Test throw */
/*
TEST(list_ThrowTests, throw_1) {
  s21::list<int>::iterator sfleta_it1;
  EXPECT_THROW(*sfleta_it1, std::exception);
}

TEST(list_ThrowTests, throw_2) {
  s21::list<int>::const_iterator sfleta_it1;
  EXPECT_THROW(*sfleta_it1, std::exception);
}

TEST(list_ThrowTests, throw_3) {
  EXPECT_THROW(s21::list<int> sfleta_l1(384307168202282325), std::exception);
}

TEST(list_ThrowTests, throw_4) {
  s21::list<int> sfleta_l1;
  EXPECT_THROW(sfleta_l1.pop_front(), std::exception);
}

TEST(list_ThrowTests, throw_5) {
  s21::list<int> sfleta_l1;
  EXPECT_THROW(sfleta_l1.pop_back(), std::exception);
}

TEST(list_ThrowTests, throw_6) {
  s21::list<int> sfleta_l1{5, 6};
  EXPECT_THROW(sfleta_l1 = std::move(sfleta_l1), std::exception);
}

TEST(list_ThrowTests, throw_7) {
  s21::list<int> sfleta_l1{5, 6};
  s21::list<int>::iterator sfleta_it1 = sfleta_l1.end();
  EXPECT_THROW(sfleta_l1.erase(sfleta_it1), std::exception);
}

TEST(list_ThrowTests, throw_8) {
  s21::list<int> sfleta_l1{5, 6};
  s21::list<int>::iterator sfleta_it1;
  EXPECT_THROW(sfleta_l1.erase(sfleta_it1), std::exception);
}
 */
//  Set tests

TEST(set_member_functions, default_constructor) {
    s21::set<int> s1;
    std::set<int> s2;
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_member_functions, initializer_list) {
    s21::set<int> s1 {42, 241, 86, 43, 90, 66, 34};
    std::set<int> s2 {42, 241, 86, 43, 90, 66, 34};
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_member_functions, move_constructor) {
    s21::set<int> s1 {42, 241, 86, 43, 90, 66, 34};
    std::set<int> s2 {42, 241, 86, 43, 90, 66, 34};
    s21::set<int> res1(std::move(s1));
    std::set<int> res2(std::move(s2));
    ASSERT_TRUE(eq_set(res1, res2));
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(set_member_functions, copy_constructor) {
    s21::set<int> s1 {42, 241, 86, 43, 90, 66, 34};
    std::set<int> s2 {42, 241, 86, 43, 90, 66, 34};
    s21::set<int> res1(s1);
    std::set<int> res2(s2);
    ASSERT_TRUE(eq_set(res1, res2));
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(set, insert3) {
    s21::set<int> s1 {1, 2, 3, 4};
    std::set<int> s2 {1, 2, 3, 4};
    auto res1 = s1.insert(1);
    auto res2 = s2.insert(1);
    ASSERT_EQ(res1.second, res2.second);
    ASSERT_EQ(*(res1.first), *(res2.first));
    res1 = s1.insert(2);
    res2 = s2.insert(2);
    ASSERT_EQ(res1.second, res2.second);
    ASSERT_EQ(*(res1.first), *(res2.first));
    res1 = s1.insert(3);
    res2 = s2.insert(3);
    ASSERT_EQ(res1.second, res2.second);
    ASSERT_EQ(*(res1.first), *(res2.first));
    res1 = s1.insert(5);
    res2 = s2.insert(5);
    ASSERT_EQ(res1.second, res2.second);
    ASSERT_EQ(*(res1.first), *(res2.first));
}

TEST(set, iterator1) {
    s21::set<int> s1{42, 241, 86, 43, 90, 66, 34};
    s21::set<int>::iterator it1 = s1.begin();
    --it1;
    --it1;
    ASSERT_EQ(241, *it1);
    --it1;
    ASSERT_EQ(90, *it1);
    --it1;
    ASSERT_EQ(86, *it1);
    --it1;
    ASSERT_EQ(66, *it1);
    --it1;
    ASSERT_EQ(43, *it1);
    --it1;
    ASSERT_EQ(42, *it1);
    --it1;
    ASSERT_EQ(34, *it1);
    --it1;
    --it1;
    ASSERT_EQ(241, *it1);
}

TEST(set_iterators_test, end2) {
    s21::set<int> s1 {2};
    std::set<int> s2 {2};
    s21::set<int>::iterator it1 = s1.end();
    --it1;
    ASSERT_EQ(*it1, *(--(s2.end())));
}

TEST(set_capacity_test, empty) {
    s21::set<int> s1;
    std::set<int> s2;
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(set_capacity_test, empty2) {
    s21::set<int> s1 {2, 1, 3, 4, 5};
    std::set<int> s2 {2, 1, 3, 4, 5};
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(set_capacity_test, size) {
    s21::set<int> s1 {};
    std::set<int> s2 {};
    ASSERT_EQ(s1.size(), s2.size());
}

TEST(set_capacity_test, size2) {
    s21::set<int> s1 {2, 1, 3, 4, 5};
    std::set<int> s2 {2, 1, 3, 4, 5};
    ASSERT_EQ(s1.size(), s2.size());
}

TEST(set_capacity_test, max_size) {
    s21::set<double> s1 {2, 1, 3, 4, 5};
    std::set<double> s2 {2, 1, 3, 4, 5};
    ASSERT_EQ(s1.max_size(), s2.max_size());
}

TEST(set_modifiers, clear) {
    s21::set<int> s1 {2, 1, 3, 4, 5};
    std::set<int> s2 {2, 1, 3, 4, 5};
    s1.clear();
    s2.clear();
    ASSERT_TRUE(eq_set(s1, s2));
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(set_modifiers, insert) {
    s21::set<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::set<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    auto p1 = s1.insert(33);
    auto p2 = s2.insert(33);
    ASSERT_TRUE(*(p1.first) == *(p2.first));
    ASSERT_TRUE(p1.second == p2.second);
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, insert2) {
    s21::set<int> s1 {};
    std::set<int> s2 {};
    auto p1 = s1.insert(2);
    auto p2 = s2.insert(2);
    ASSERT_TRUE(*(p1.first) == *(p2.first));
    ASSERT_TRUE(p1.second == p2.second);
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, insert3) {
    s21::set<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::set<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    auto p1 = s1.insert(5);
    auto p2 = s2.insert(5);
    ASSERT_TRUE(*(p1.first) == *(p2.first));
    ASSERT_TRUE(p1.second == p2.second);
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, emplace) {
    s21::set<int> s1 {};
    std::set<int> s2 {8, 2, 3, 5, 6};
    s1.emplace(8, 2, 3, 5, 6);
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, erase) {
    int value = 5;
    s21::set<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::set<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    s1.erase(s1.find(value));
    s2.erase(s2.find(value));
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, erase2) {
    int value = 2;
    s21::set<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::set<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    s1.erase(s1.find(value));
    s2.erase(s2.find(value));
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, erase3) {
    s21::set<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::set<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    std::set<int> s3 {8, 7, 6, 5, 4, 3, 2, 1};
    for (auto value : s3) {
        s1.erase(s1.find(value));
        s2.erase(s2.find(value));
        ASSERT_TRUE(eq_set(s1, s2));
    }
}

TEST(set_modifiers, erase4) {
    s21::set<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::set<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    std::set<int> s3 {8, 7, 6, 5, 4, 3, 2, 1};
    auto it = s3.end();
    --it;
    while (it != s3.end()) {
        s1.erase(s1.find(*it));
        s2.erase(s2.find(*it));
        ASSERT_TRUE(eq_set(s1, s2));
        --it;
    }
}

TEST(set_modifiers, operator_move) {
    s21::set<int> s1 {2};
    s1 = std::move(s1);
    std::set<int> s2 {2};
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, swap) {
    s21::set<int> s1 {2};
    s21::set<int> s1_2 {1, 2, 3};
    s1.swap(s1_2);
    std::set<int> s2 {};
    std::set<int> s2_2 {1, 2, 3};
    s2.swap(s2_2);
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, swap2) {
    s21::set<int> s1 {};
    s21::set<int> s1_2 {1, 2, 3};
    s1.swap(s1_2);
    std::set<int> s2 {};
    std::set<int> s2_2 {1, 2, 3};
    s2.swap(s2_2);
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_modifiers, merge) {
    s21::set<int> s1 {4, 6, 7};
    s21::set<int> s1_2 {1, 2, 3};
    s1.merge(s1_2);
    std::set<int> s2 {4, 6, 7};
    std::set<int> s2_2 {1, 2, 3};
    s2.merge(s2_2);
    ASSERT_TRUE(eq_set(s1, s2));
    ASSERT_TRUE(eq_set(s1_2, s2_2));
}

TEST(set_modifiers, merge2) {
    s21::set<int> s1 {1, 4, 3};
    s21::set<int> s1_2 {1, 2, 3};
    s1.merge(s1_2);
    std::set<int> s2 {1, 4, 3};
    std::set<int> s2_2 {1, 2, 3};
    s2.merge(s2_2);
    ASSERT_TRUE(eq_set(s1, s2));
    ASSERT_TRUE(eq_set(s1_2, s2_2));
}

TEST(set_lookup, find) {
    s21::set<int> s1 {1, 4, 3};
    s1.find(4);
    std::set<int> s2 {1, 4, 3};
    s2.find(4);
    ASSERT_EQ(*(s1.find(4)), (*s2.find(4)));
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_lookup, find2) {
    s21::set<int> s1 {1, 4, 3};
    s1.find(44);
    std::set<int> s2 {1, 4, 3};
    s2.find(44);
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_lookup, contains) {
    s21::set<int> s1 {1, 4, 3};
    std::set<int> s2 {1, 4, 3};
    ASSERT_EQ(s1.contains(4), s2.count(4));
    ASSERT_TRUE(eq_set(s1, s2));
}

TEST(set_lookup, contains2) {
    s21::set<int> s1 {1, 4, 3};
    std::set<int> s2 {1, 4, 3};
    ASSERT_EQ(s1.contains(44), s2.count(44));
    ASSERT_TRUE(eq_set(s1, s2));
}

//  multiset tests

TEST(multiset_member_functions, default_constructor) {
    s21::multiset<int> s1;
    std::multiset<int> s2;
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_member_functions, initializer_list) {
    s21::multiset<int> s1 {42, 241, 86, 43, 90, 66, 34};
    std::multiset<int> s2 {42, 241, 86, 43, 90, 66, 34};
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_member_functions, copy_constructor) {
    s21::multiset<int> s1 {42, 241, 86, 43, 90, 66, 34};
    s21::multiset<int> res1(s1);
    std::multiset<int> s2 {42, 241, 86, 43, 90, 66, 34};
    std::multiset<int> res2(s2);
    ASSERT_TRUE(eq_multiset(res1, res2));
}

TEST(multiset, insert3) {
    s21::multiset<int> s1 {1, 2, 3, 4};
    std::multiset<int> s2 {1, 2, 3, 4};
    auto res1 = s1.insert(1);
    auto res2 = s2.insert(1);
    ASSERT_EQ(*res1, *res2);
    res1 = s1.insert(2);
    res2 = s2.insert(2);
    ASSERT_EQ(*res1, *res2);
    res1 = s1.insert(3);
    res2 = s2.insert(3);
    ASSERT_EQ(*res1, *res2);
    res1 = s1.insert(5);
    res2 = s2.insert(5);
    ASSERT_EQ(*res1, *res2);
}

TEST(multiset, iterator1) {
    s21::multiset<int> s1{42, 241, 86, 43, 90, 66, 34};
    s21::multiset<int>::iterator it1 = s1.begin();
    --it1;
    --it1;
    ASSERT_EQ(241, *it1);
    --it1;
    ASSERT_EQ(90, *it1);
    --it1;
    ASSERT_EQ(86, *it1);
    --it1;
    ASSERT_EQ(66, *it1);
    --it1;
    ASSERT_EQ(43, *it1);
    --it1;
    ASSERT_EQ(42, *it1);
    --it1;
    ASSERT_EQ(34, *it1);
    --it1;
    --it1;
    ASSERT_EQ(241, *it1);
}

TEST(multiset_iterators_test, end2) {
    s21::multiset<int> s1 {2};
    std::multiset<int> s2 {2};
    s21::multiset<int>::iterator it1 = s1.end();
    --it1;
    ASSERT_EQ(*it1, *(--(s2.end())));
}

TEST(multiset_capacity_test, empty) {
    s21::multiset<int> s1;
    std::multiset<int> s2;
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(multiset_capacity_test, empty2) {
    s21::multiset<int> s1 {2, 1, 3, 4, 5};
    std::multiset<int> s2 {2, 1, 3, 4, 5};
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(multiset_capacity_test, size) {
    s21::multiset<int> s1 {};
    std::multiset<int> s2 {};
    ASSERT_EQ(s1.size(), s2.size());
}

TEST(multiset_capacity_test, size2) {
    s21::multiset<int> s1 {2, 1, 3, 4, 5};
    std::multiset<int> s2 {2, 1, 3, 4, 5};
    ASSERT_EQ(s1.size(), s2.size());
}

TEST(multiset_capacity_test, max_size) {
    s21::multiset<double> s1 {2, 1, 3, 4, 5};
    std::multiset<double> s2 {2, 1, 3, 4, 5};
    ASSERT_EQ(s1.max_size(), s2.max_size());
}

TEST(multiset_modifiers, clear) {
    s21::multiset<int> s1 {2, 1, 3, 4, 5};
    std::multiset<int> s2 {2, 1, 3, 4, 5};
    s1.clear();
    s2.clear();
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_modifiers, insert) {
    s21::multiset<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    auto p1 = s1.insert(33);
    auto p2 = s2.insert(33);
    ASSERT_TRUE(*p1 == *p2);
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_modifiers, insert2) {
    s21::multiset<int> s1 {};
    std::multiset<int> s2 {};
    auto p1 = s1.insert(2);
    auto p2 = s2.insert(2);
    ASSERT_TRUE(*p1 == *p2);
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_modifiers, insert3) {
    s21::multiset<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    auto p1 = s1.insert(5);
    auto p2 = s2.insert(5);
    ASSERT_TRUE(*p1 == *p2);
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_modifiers, emplace) {
    s21::multiset<int> s1 {};
    std::multiset<int> s2 {8, 2, 3, 5, 6, 6, 7, 7, 8};
    s1.emplace(8, 2, 3, 5, 6, 6, 7, 7, 8);
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_modifiers, erase) {
    int value = 5;
    s21::multiset<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    s1.erase(s1.find(value));
    s2.erase(s2.find(value));
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_modifiers, erase2) {
    s21::multiset<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> s3 {8, 7, 6, 5, 4, 3, 2, 1};
    for (auto value : s3) {
        s1.erase(s1.find(value));
        s2.erase(s2.find(value));
        ASSERT_TRUE(eq_multiset(s1, s2));
    }
}

TEST(multiset_modifiers, erase3) {
    s21::multiset<int> s1 {8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> s2 {8, 7, 6, 5, 4, 3, 2, 1};
    std::multiset<int> s3 {8, 7, 6, 5, 4, 3, 2, 1};
    auto it = s3.end();
    --it;
    while (it != s3.end()) {
        s1.erase(s1.find(*it));
        s2.erase(s2.find(*it));
        ASSERT_TRUE(eq_multiset(s1, s2));
        --it;
    }
}

TEST(multiset_modifiers, operator_move) {
    s21::multiset<int> s1 {2};
    s1 = std::move(s1);
    std::multiset<int> s2 {2};
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_modifiers, swap) {
    s21::multiset<int> s1 {2};
    s21::multiset<int> s1_2 {1, 2, 3};
    s1.swap(s1_2);
    std::multiset<int> s2 {};
    std::multiset<int> s2_2 {1, 2, 3};
    s2.swap(s2_2);
    ASSERT_TRUE(eq_multiset(s1, s2));
    ASSERT_TRUE(s1_2.empty() != s2_2.empty());
}

TEST(multiset_modifiers, swap2) {
    s21::multiset<int> s1 {};
    s21::multiset<int> s1_2 {1, 2, 3};
    s1.swap(s1_2);
    std::multiset<int> s2 {};
    std::multiset<int> s2_2 {1, 2, 3};
    s2.swap(s2_2);
    ASSERT_TRUE(eq_multiset(s1, s2));
    ASSERT_TRUE(s1_2.empty() == s2_2.empty());
}

TEST(multiset_modifiers, merge) {
    s21::multiset<int> s1 {4, 6, 7};
    s21::multiset<int> s1_2 {1, 2, 3};
    s1.merge(s1_2);
    std::multiset<int> s2 {4, 6, 7};
    std::multiset<int> s2_2 {1, 2, 3};
    s2.merge(s2_2);
    ASSERT_TRUE(eq_multiset(s1, s2));
    ASSERT_TRUE(eq_multiset(s1_2, s2_2));
}

TEST(multiset_modifiers, merge2) {
    s21::multiset<int> s1 {1, 4, 3};
    s21::multiset<int> s1_2 {1, 2, 3};
    s1.merge(s1_2);
    std::multiset<int> s2 {1, 4, 3};
    std::multiset<int> s2_2 {1, 2, 3};
    s2.merge(s2_2);
    ASSERT_TRUE(eq_multiset(s1, s2));
    ASSERT_TRUE(eq_multiset(s1_2, s2_2));
}

TEST(multiset_lookup, find) {
    s21::multiset<int> s1 {1, 4, 3};
    s1.find(4);
    std::multiset<int> s2 {1, 4, 3};
    s2.find(4);
    ASSERT_EQ(*(s1.find(4)), (*s2.find(4)));
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_lookup, find2) {
    s21::multiset<int> s1 {1, 4, 3};
    s1.find(44);
    std::multiset<int> s2 {1, 4, 3};
    s2.find(44);
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_lookup, contains) {
    s21::multiset<int> s1 {1, 4, 3};
    std::multiset<int> s2 {1, 4, 3};
    ASSERT_EQ(s1.contains(4), s2.count(4));
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_lookup, contains2) {
    s21::multiset<int> s1 {1, 4, 3};
    std::multiset<int> s2 {1, 4, 3};
    ASSERT_EQ(s1.contains(44), s2.count(44));
    ASSERT_TRUE(eq_multiset(s1, s2));
}

TEST(multiset_lookup, count1) {
    s21::multiset<int> s1 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    std::multiset<int> s2 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    ASSERT_EQ(s1.count(4), s2.count(4));
}

TEST(multiset_lookup, count2) {
    s21::multiset<int> s1 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    std::multiset<int> s2 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    ASSERT_EQ(s1.count(44), s2.count(44));
}

TEST(multiset_lookup, equal_range) {
    s21::multiset<int> s1 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    std::multiset<int> s2 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    auto it1 = s1.equal_range(4);
    auto it2 = s2.equal_range(4);
    ASSERT_EQ(*it1.first, *it2.first);
    ASSERT_EQ(*it1.second, *it2.second);
}

TEST(multiset_lookup, lower_bound) {
    s21::multiset<int> s1 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    std::multiset<int> s2 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    auto it1 = s1.lower_bound(4);
    auto it2 = s2.lower_bound(4);
    ASSERT_EQ(*it1, *it2);
    --it1;
    --it2;
    ASSERT_EQ(*it1, *it2);
}
TEST(multiset_lookup, upper_bound) {
    s21::multiset<int> s1 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    std::multiset<int> s2 {1, 4, 3, 4, 4, 2, 1, 4, 32, 4};
    auto it1 = s1.upper_bound(4);
    auto it2 = s2.upper_bound(4);
    ASSERT_EQ(*it1, *it2);
    --it1;
    --it2;
    ASSERT_EQ(*it1, *it2);
}

TEST(multiset_member_functions, move_constructor) {
    s21::multiset<int> s1 {42, 241, 86, 43, 90, 66, 34};
    std::multiset<int> s2 {42, 241, 86, 43, 90, 66, 34};
    s21::multiset<int> res1(std::move(s1));
    std::multiset<int> res2(std::move(s2));
    ASSERT_TRUE(eq_multiset(res1, res2));
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(map_initialization, default_costruct) {
    s21::Map<int, double> s1;
    std::map<int, double> s2;
    ASSERT_EQ(s1.empty(), s2.empty());
}

TEST(map_initialization, initializer_list_constructor) {
    s21::Map<int, double> s1 { {1, -1.1}, {3, -3.3}, {4, -4.34}, {-12, 42.21} };
    std::map<int, double> s2 { {1, -1.1}, {3, -3.3}, {4, -4.34}, {-12, 42.21} };
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_initialization, copy_costructor) {
    s21::Map<int, double> temp1{ {41, -1.14}, {-33, -7.3}, {42, -14.354}, {-512, 542.21} };
    std::map<int, double> temp2{ {41, -1.14}, {-33, -7.3}, {42, -14.354}, {-512, 542.21} };
    s21::Map<int, double> s1(temp1);
    std::map<int, double> s2(temp2);
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_initialization, copy_costructor2) {
    s21::Map<std::string, double> temp1 { {"fdg", -1.14}, {"-33", -7.3},
                                          {"lkyu", -14.354}, {"4etre", 542.21} };
    std::map<std::string, double> temp2 { {"fdg", -1.14}, {"-33", -7.3},
                                          {"lkyu", -14.354}, {"4etre", 542.21} };
    s21::Map<std::string, double> s1(temp1);
    std::map<std::string, double> s2(temp2);
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_initialization, move_costructor) {
    s21::Map<std::string, double> temp1 { {"fdg", -1.14}, {"-33", -7.3},
                                          {"lkyu", -14.354}, {"4etre", 542.21} };
    std::map<std::string, double> temp2 { {"fdg", -1.14}, {"-33", -7.3},
                                          {"lkyu", -14.354}, {"4etre", 542.21} };
    s21::Map<std::string, double> s1(std::move(temp1));
    std::map<std::string, double> s2(std::move(temp2));
    ASSERT_TRUE(temp1.empty() == temp2.empty());
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_element_access, at_func) {
    s21::Map<std::string, double> s1{ {"fdg", -1.14}, {"-33", -7.3}, {"lkyu", -14.354}, {"4etre", 542.21} };
    std::map<std::string, double> s2{ {"fdg", -1.14}, {"-33", -7.3}, {"lkyu", -14.354}, {"4etre", 542.21} };
    ASSERT_EQ(s1.at("-33"), s2.at("-33"));
    ASSERT_EQ(s1.at("fdg"), s2.at("fdg"));
    ASSERT_EQ(s1.at("lkyu"), s2.at("lkyu"));
    ASSERT_EQ(s1.at("4etre"), s2.at("4etre"));
}

TEST(map_element_access, _func_) {
    s21::Map<double, std::vector<int>> s1 { { 7.35, {23, -1, 875} }, { 1.91, {-35, -7, 4}  },
                                            { 5.17, {5, 17, 47}   }, { 71.74, {65, 22, 46} }
                                          };
    std::map<double, std::vector<int>> s2 { { 7.35, {23, -1, 875} }, { 1.91, {-35, -7, 4}  },
                                            { 5.17, {5, 17, 47}   }, { 71.74, {65, 22, 46} }
                                          };
    ASSERT_EQ(s1[7.35], s2[7.35]);
    ASSERT_EQ(s1[1.91], s2[1.91]);
    ASSERT_EQ(s1[5.17], s2[5.17]);
}

TEST(map_modifiers, clear) {
    s21::Map<std::string, double> s1{ {"fdg", -1.14}, {"-33", -7.3}, {"lkyu", -14.354}, {"4etre", 542.21} };
    std::map<std::string, double> s2{ {"fdg", -1.14}, {"-33", -7.3}, {"lkyu", -14.354}, {"4etre", 542.21} };
    s1.clear();
    s2.clear();
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_modifiers, clear2) {
    s21::Map<std::string, char> s1{ {"ttry", 'A'}, {"prtmq", 'B'}, {"mnqrt", 'C'}, {"hello", 'D'} };
    std::map<std::string, char> s2{ {"ttry", 'A'}, {"prtmq", 'B'}, {"mnqrt", 'C'}, {"hello", 'D'} };
    s1.clear();
    s2.clear();
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_modifiers, insert) {
    s21::Map<std::string, char> s1;
    std::map<std::string, char> s2{ {"ttry", 'A'}, {"prtmq", 'B'}, {"mnqrt", 'C'}, {"hello", 'D'} };
    s1.insert("ttry", 'A');
    s1.insert("prtmq", 'B');
    s1.insert("mnqrt", 'C');
    s1.insert("hello", 'D');
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_modifiers, insert2) {
    s21::Map<double, char> s1;
    std::map<double, char> s2{ {1234.3145, 'A'}, {123.1, 'B'}, {-34., 'C'}, {0.421, 'D'} };
    s1.insert(1234.3145, 'A');
    s1.insert(123.1, 'B');
    s1.insert(-34., 'C');
    s1.insert(0.421, 'D');
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_modifiers, insert3) {
    std::pair<double, std::string> pair1 {1234.3145, "Hi"};
    std::pair<double, std::string> pair2 {123.1, "Aloha"};
    std::pair<double, std::string> pair3 {-34., "Hello"};
    std::pair<double, std::string> pair4 {0.421, "Hooo"};
    s21::Map<double, std::string> s1;
    std::map<double, std::string> s2{ {1234.3145, "Hi"}, {123.1, "Aloha"}, {-34., "Hello"}, {0.421, "Hooo"} };
    s1.insert(pair1);
    s1.insert(pair2);
    s1.insert(pair3);
    s1.insert(pair4);
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_modifiers, insert4) {
    std::pair<std::string, unsigned int> pair1 {"Hi", 94856};
    std::pair<std::string, unsigned int> pair2 {"Aloha", 2365};
    std::pair<std::string, unsigned int> pair3 {"Hello", 9047};
    std::pair<std::string, unsigned int> pair4 {"Hooo", 2344};
    s21::Map<std::string, unsigned int> s1;
    std::map<std::string, unsigned int> s2{ {"Hi", 94856}, {"Aloha", 2365}, {"Hello", 9047}, {"Hooo", 2344} };
    s1.insert(pair1);
    s1.insert(pair2);
    s1.insert(pair3);
    s1.insert(pair4);
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_modifiers, insert_or_assign) {
    s21::Map<std::string, float> s1;
    std::map<std::string, float> s2{ {"Hi", 948.56}, {"Aloha", 2.365}, {"Hello", 904.7}, {"Hooo", 234.4} };
    s1.insert_or_assign("Hi", 948.56);
    s1.insert_or_assign("Aloha", -5);
    s1.insert_or_assign("Hello", 0);
    s1.insert_or_assign("Hooo", 234.4);

    s1.insert_or_assign("Aloha", 2.365);
    s1.insert_or_assign("Hello", 904.7);
    ASSERT_TRUE(eq_map(s1, s2));
}

TEST(map_modifiers, erase) {
    s21::Map<std::string, unsigned int> s1{ {"Hi", 94856}, {"Aloha", 2365}, {"Hello", 9047}, {"Hooo", 2344} };
    std::map<std::string, unsigned int> s2{ {"Hi", 94856}, {"Hello", 9047}, {"Hooo", 2344} };
    s1.erase(s1.find("Aloha"));
    ASSERT_TRUE(eq_map(s1, s2));
    s1.erase(s1.find("Hi"));
    s2.erase(s2.find("Hi"));
    ASSERT_TRUE(eq_map(s1, s2));
    s1.erase(s1.find("Hooo"));
    s2.erase(s2.find("Hooo"));
    ASSERT_TRUE(eq_map(s1, s2));
    s1.erase(s1.find("Hello"));
    s2.erase(s2.find("Hello"));
    ASSERT_TRUE(eq_map(s1, s2));
    ASSERT_TRUE(s1.empty() == s2.empty());
}

TEST(map_modifiers, swap) {
    s21::Map<float, double> s1;
    s21::Map<float, double> s2 { {2.365, 948.56}, {-345.1, 2.365}, {3464, 904.7}, {995, 234.4} };
    s1.swap(s2);
    ASSERT_EQ(s1[2.365], 948.56);
    ASSERT_EQ(s1[-345.1], 2.365);
    ASSERT_EQ(s1[3464], 904.7);
    ASSERT_EQ(s1[995], 234.4);
    ASSERT_TRUE(s2.empty());
}

TEST(map_modifiers, merge) {
    s21::Map<float, double> s1 { {45.1, 5.} };
    s21::Map<float, double> s2 { {2.365, 948.56}, {-345.1, 2.365}, {3464, 904.7}, {995, 234.4} };
    s1.merge(s2);
    ASSERT_EQ(s1[2.365], 948.56);
    ASSERT_EQ(s1[-345.1], 2.365);
    ASSERT_EQ(s1[3464], 904.7);
    ASSERT_EQ(s1[995], 234.4);
    ASSERT_EQ(s1[45.1], 5.);
    ASSERT_TRUE(s2.empty());
}

TEST(map_capacity, merge2) {
    s21::Map<float, double> s1 { {45.1, 5.}, {-345.1, 2.365}, {3464, 904.7} };
    s21::Map<float, double> s2 { {2.365, 948.56}, {-345.1, 2.365}, {3464, 904.7}, {995, 234.4} };
    s1.merge(s2);
    ASSERT_EQ(s1[2.365], 948.56);
    ASSERT_EQ(s1[-345.1], 2.365);
    ASSERT_EQ(s1[3464], 904.7);
    ASSERT_EQ(s1[995], 234.4);
    ASSERT_EQ(s1[45.1], 5.);
    ASSERT_EQ(s2[-345.1], 2.365);
    ASSERT_EQ(s2[3464], 904.7);
}

TEST(map_capacity, size) {
    s21::Map<char, double> s1 { {'E', 948.56}, {'B', 2.365}, {'O', 904.7}, {'Y', 234.4} };
    std::map<char, double> s2 { {'E', 948.56}, {'B', 2.365}, {'O', 904.7}, {'Y', 234.4} };
    ASSERT_TRUE(s1.size() == s2.size());
}

TEST(map_capacity, size2) {
    s21::Map<char, double> s1;
    std::map<char, double> s2;
    ASSERT_TRUE(s1.size() == s2.size());
}

TEST(map_capacity, size3) {
    s21::Map<int, double> s1 { {948, 948.56}, {948, 2.365}, {-948, 904.7}, {234, 234.4} };
    std::map<int, double> s2 { {948, 948.56}, {948, 2.365}, {-948, 904.7}, {234, 234.4} };
    ASSERT_TRUE(s1.size() == s2.size());
}

TEST(map_capacity, empty) {
    s21::Map<int, double> s1 { {948, 948.56}, {948, 2.365} };
    s21::Map<int, double> s2;
    ASSERT_FALSE(s1.empty());
    ASSERT_TRUE(s2.empty());
}

TEST(map_lookup, contains) {
    s21::Map<std::string, double> s1 { {"Hello", 948.56}, {"World", 2.365} };
    ASSERT_TRUE(s1.contains("Hello"));
    ASSERT_TRUE(s1.contains("World"));
    ASSERT_FALSE(s1.contains("Contains"));
}

TEST(map_iterators, iterator) {
    s21::Map<double, std::string> s1{ {1234.3145, "Hi"}, {123.1, "Aloha"}, {-34., "Hello"}, {0.421, "Hooo"} };
    s21::Map<double, std::string> s2(s1);
    s21::Map<double, std::string>::Mapiterator it = s1.begin();
    for (auto&& value : s1) {
        ASSERT_EQ(value.first, (*it).first);
        ASSERT_EQ(value.second, (*it).second);
        ++it;
    }
    ASSERT_EQ(*s1.end(), *s2.end());
}

TEST(map_iterators, iterator2) {
    s21::Map<std::string, std::string> s1{ {"Press_F", "Hi"}, {"Good", "Aloha"},
                                           {"Duck", "Hello"}, {"KFC", "Hooo"} };
    s21::Map<std::string, std::string> s2(s1);
    s21::Map<std::string, std::string>::Mapiterator it = s1.begin();
    for (auto&& value : s1) {
        ASSERT_EQ(value.first, (*it).first);
        ASSERT_EQ(value.second, (*it).second);
        ++it;
    }
    ASSERT_EQ(*s1.end(), *s2.end());
}

TEST(map_iterators, iterator3) {
    s21::Map<std::string, int> s1{ {"Dog", 241}, {"Fox", 43}, {"Pig", 66}, {"Cat", 56} };
    s21::Map<std::string, int>::Mapiterator it = s1.begin();
    ASSERT_EQ((*it).first, "Cat");
    ASSERT_EQ((*it).second, 56);
    ++it;
    ASSERT_EQ((*it).first, "Dog");
    ASSERT_EQ((*it).second, 241);
    ++it;
    ASSERT_EQ((*it).first, "Fox");
    ASSERT_EQ((*it).second, 43);
    ++it;
    ASSERT_EQ((*it).first, "Pig");
    ASSERT_EQ((*it).second, 66);
}

TEST(map_iterators, emplace) {
    s21::Map<double, double> s1;
    s1.emplace(17.3, 5.5, 41.5, -3.8, 94., 13.7, -124.3, 9.1);
    ASSERT_EQ(s1[17.3], 5.5);
    ASSERT_EQ(s1[41.5], -3.8);
    ASSERT_EQ(s1[94.], 13.7);
    ASSERT_EQ(s1[-124.3], 9.1);
    ASSERT_EQ(s1.size(), 4);
}

TEST(queue_constructor, default_constr) {
    s21::Queue<double> q1;
    ASSERT_EQ(q1.size(), 0);
    ASSERT_TRUE(q1.empty());
}

TEST(queue_constructor, initializer) {
    s21::Queue<double> q1 {5.5, 4.3, 2.2, 7.1};
    ASSERT_EQ(q1.size(), 4);
    ASSERT_EQ(q1.front(), 5.5);
    ASSERT_EQ(q1.back(), 7.1);
}

TEST(queue_constructor, initializer2) {
    s21::Queue<std::string> q1 {"WouWouWou", "BlaBla", "Ololo", "Aaaaaaaar", "Fuuuu"};
    ASSERT_EQ(q1.size(), 5);
    ASSERT_EQ(q1.front(), "WouWouWou");
    ASSERT_EQ(q1.back(), "Fuuuu");
}

TEST(queue_constructor, copy) {
    s21::Queue<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    s21::Queue<char> q2(q1);
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_constructor, move) {
    s21::Queue<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    s21::Queue<char> q2 { 'S', 'c', 'h', 'o', 'o', 'l' };
    s21::Queue<char> q3(std::move(q1));
    ASSERT_TRUE(q1.empty());
    ASSERT_TRUE(eq_queue(q2, q3));
}

TEST(queue_func, eq) {
    s21::Queue<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    s21::Queue<char> q2 = q1;
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_func, push) {
    s21::Queue<std::string> q1;
    std::queue<std::string> q2;
    q1.push("Jooooo");
    q1.push("Byy");
    q1.push("Wow");
    q2.push("Jooooo");
    q2.push("Byy");
    q2.push("Wow");
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_func, push2) {
    s21::Queue<std::vector<double>> q1;
    std::queue<std::vector<double>> q2;
    q1.push({2.7, 7.2, -34.1});
    q1.push({12.47, -57.2, 94.1});
    q1.push({7.5, -95.2, -374.1});
    q2.push({2.7, 7.2, -34.1});
    q2.push({12.47, -57.2, 94.1});
    q2.push({7.5, -95.2, -374.1});
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_func, push3) {
    s21::Queue<std::pair<std::string, std::map<char, float>>> q1;
    std::queue<std::pair<std::string, std::map<char, float>>> q2;
    q1.push({"Test", { {'T', -43.123}, {'E', 13.43}, {'S', 3.13}, {'F', 43.4} } });
    q1.push({"Map", { {'M', 3.1263}, {'A', 3.43}, {'P', 3.}, {'1', 5.4} } });
    q1.push({"Queue", { {'Q', 63.}, {'u', 3.43}, {'e', -53.}, {'U', 545.5}, {'E', -0.4} } });
    q2.push({"Test", { {'T', -43.123}, {'E', 13.43}, {'S', 3.13}, {'F', 43.4} } });
    q2.push({"Map", { {'M', 3.1263}, {'A', 3.43}, {'P', 3.}, {'1', 5.4} } });
    q2.push({"Queue", { {'Q', 63.}, {'u', 3.43}, {'e', -53.}, {'U', 545.5}, {'E', -0.4} } });
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_func, swap) {
    s21::Queue<std::vector<double>> q1;
    std::queue<std::vector<double>> q2;
    q1.push({2.7, 7.2, -34.1});
    q1.push({12.47, -57.2, 94.1});
    q1.push({7.5, -95.2, -374.1});
    q2.push({2.7, 7.2, -34.1});
    q2.push({12.47, -57.2, 94.1});
    q2.push({7.5, -95.2, -374.1});
    s21::Queue<std::vector<double>> q3;
    q3.swap(q1);
    ASSERT_TRUE(eq_queue(q3, q2));
}

TEST(stack_constructor, default_constr) {
    s21::Stack<double> q1;
    ASSERT_EQ(q1.size(), 0);
    ASSERT_TRUE(q1.empty());
}

TEST(stack_constructor, initializer) {
    s21::Stack<double> q1 {5.5, 4.3, 2.2, 7.1};
    ASSERT_EQ(q1.size(), 4);
    ASSERT_EQ(q1.top(), 7.1);
}

TEST(stack_constructor, initializer2) {
    s21::Stack<std::string> q1 {"WouWouWou", "BlaBla", "Ololo", "Aaaaaaaar", "Fuuuu"};
    ASSERT_EQ(q1.size(), 5);
    ASSERT_EQ(q1.top(), "Fuuuu");
}

TEST(stack_constructor, copy) {
    s21::Stack<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    s21::Stack<char> q2(q1);
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_constructor, move) {
    s21::Stack<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    s21::Stack<char> q2 { 'S', 'c', 'h', 'o', 'o', 'l' };
    s21::Stack<char> q3(std::move(q1));
    ASSERT_TRUE(q1.empty());
    ASSERT_TRUE(eq_stack(q2, q3));
}

TEST(stack_func, eq) {
    s21::Stack<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    s21::Stack<char> q2 = q1;
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_func, push) {
    s21::Stack<std::string> q1;
    std::stack<std::string> q2;
    q1.push("Jooooo");
    q1.push("Byy");
    q1.push("Wow");
    q2.push("Jooooo");
    q2.push("Byy");
    q2.push("Wow");
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_func, push2) {
    s21::Stack<std::vector<double>> q1;
    std::stack<std::vector<double>> q2;
    q1.push({2.7, 7.2, -34.1});
    q1.push({12.47, -57.2, 94.1});
    q1.push({7.5, -95.2, -374.1});
    q2.push({2.7, 7.2, -34.1});
    q2.push({12.47, -57.2, 94.1});
    q2.push({7.5, -95.2, -374.1});
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_func, push3) {
    s21::Stack<std::pair<std::string, std::map<char, float>>> q1;
    std::stack<std::pair<std::string, std::map<char, float>>> q2;
    q1.push({"Test", { {'T', -43.123}, {'E', 13.43}, {'S', 3.13}, {'F', 43.4} } });
    q1.push({"Map", { {'M', 3.1263}, {'A', 3.43}, {'P', 3.}, {'1', 5.4} } });
    q1.push({"Queue", { {'Q', 63.}, {'u', 3.43}, {'e', -53.}, {'U', 545.5}, {'E', -0.4} } });
    q2.push({"Test", { {'T', -43.123}, {'E', 13.43}, {'S', 3.13}, {'F', 43.4} } });
    q2.push({"Map", { {'M', 3.1263}, {'A', 3.43}, {'P', 3.}, {'1', 5.4} } });
    q2.push({"Queue", { {'Q', 63.}, {'u', 3.43}, {'e', -53.}, {'U', 545.5}, {'E', -0.4} } });
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_func, swap) {
    s21::Stack<std::vector<double>> q1;
    std::stack<std::vector<double>> q2;
    q1.push({2.7, 7.2, -34.1});
    q1.push({12.47, -57.2, 94.1});
    q1.push({7.5, -95.2, -374.1});
    q2.push({2.7, 7.2, -34.1});
    q2.push({12.47, -57.2, 94.1});
    q2.push({7.5, -95.2, -374.1});
    s21::Stack<std::vector<double>> q3;
    q3.swap(q1);
    ASSERT_TRUE(eq_stack(q3, q2));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
