#include <iostream>
#include <string>
#include <algorithm>  // for_each loop
#include <random>     // random library
#include <array>

using namespace std;

string displayFullName(const string &first, const string &last);

void displayArray(const array<string, 3> &items);

// C++14 return type deduction
auto getArrayOfInts() -> array<int, 5>;

// C++11 Type aliases for increased readability (use over typedef)
using rng = default_random_engine;

// C++14 return type deduction
auto getRng() -> rng &;

// c++17 Template argument deduction
template<typename T = int>
class Adder {
public:
    Adder() : result{} {};

    Adder(const T &item1, const T &item2) : result{item1 + item2} {};

    T get_result() { return result; };
private:
    T result;
};

// c++17 folding expressions with templates
template<typename... Args>
auto calcSum(Args... args) {
  return (... + args);
}

// c++11 feature that returns the declared type deduced
template<typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y) {
  return x + y;
}

int main() {
  // c++17 Template argument deduction
  array super_heroes{"The Flash"s, "Super Man"s, "Iron Man"s};
  displayArray(super_heroes);

  // c++11 lambdas
  auto print = [](const auto &value) { cout << " " << value; };

  // c++98 found in the algorithms library and fits well with lambdas
  for_each(super_heroes.rbegin(), super_heroes.rend(), print);
  cout << endl;

  string first{"Bob"}, last{"Danger"};
  cout << displayFullName(first, last) << endl;
  cout << displayFullName("Barry", "Allen") << endl;

  array numbers = getArrayOfInts();

  // c++11 Range-based for loops
  for (const auto &number : numbers) {
    print(number);
  }
  cout << endl;

  // c++98 found in the algorithms library and fits well with lambdas
  for_each(rbegin(numbers), rend(numbers), print);
  cout << endl;

  // c++17 string_view
  char letters[]{'a', 'b', 'c'};
  string_view letter_view(letters, size(letters));
  cout << letter_view << endl;

  // c++17 Template argument deduction
  Adder integerSum {2, 4};
  cout << integerSum.get_result() << endl;

  // c++17 Template argument deduction
  Adder stringCat {"Barry"s, " Allen"s};
  cout << stringCat.get_result() << endl;

  return 0;
}

string displayFullName(const string &first, const string &last) {
  return first + " " + last;
}

void displayArray(const array<string, 3> &items) {
  string last_item{items[items.size() - 1]};
  auto is_at_last_name = [&](const string &name) { return name == last_item; };

  cout << "{";
  for (const auto &name : items) {
    cout << name;
    if (!is_at_last_name(name))
      cout << ", ";
  }
  cout << "}" << endl;
}

auto getArrayOfInts() -> array<int, 5> {
  array<int, 5> list{};
  uniform_int_distribution<int> distribution{0, 9};
  auto roll = [&]() -> int { return distribution(getRng()); };

  for (auto &number : list) {
    number = roll();
  }

  return list;
}

auto getRng() -> rng & {
  static rng engine{random_device{}()};
  return engine;
}