// tuple example
#include <iostream>     // std::cout
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore
#include <unordered_map>

class A {
public:
};

class B {
public:

};

int main ()
{
  std::tuple<int,char> foo (10,'x');
  auto bar = std::make_tuple ("test", 3.1, 14, 'y');

  std::get<2>(bar) = 100;                                    // access element

  int myint; char mychar;

  std::tie (myint, mychar) = foo;                            // unpack elements
  std::tie (std::ignore, std::ignore, myint, mychar) = bar;  // unpack (with ignore)

  mychar = std::get<3>(bar);

  std::get<0>(foo) = std::get<2>(bar);
  std::get<1>(foo) = mychar;

  std::cout << "foo contains: ";
  std::cout << std::get<0>(foo) << ' ';
  std::cout << std::get<1>(foo) << '\n';


  // ----------------------------------------
  // can be value, can't be key ?
  // std::unordered_map<std::tuple<int,char>, int> tuple_map;
  // tuple_map[std::make_tuple(12, 'x')] = 1;

  std::unordered_map<int, std::tuple<int,char>> tuple_map;
  tuple_map[1] = std::make_tuple(12, 'x');

  // --------------
  std::tuple<A, B> tuple_class(A(), B());

  // -------------- compare ----- works -------
  std::tuple<int,char> a(1, 'a'), b(1, 'a'), c(1, 'b');
  if (a == b) {
    std::cout << "a === b" << std::endl;
  } else {
    std::cout << "a != b" << std::endl;
  }

  if (a == c) {
    std::cout << "a === c" << std::endl;
  } else {
    std::cout << "a != c" << std::endl;
  }

  return 0;
}