// forward_as_tuple example
#include <iostream>     // std::cout
#include <tuple>        // std::tuple, std::get, std::forward_as_tuple
#include <string>       // std::string


/*
template<class... Types>
  tuple<Types&&...> forward_as_tuple (Types&&... args) noexcept;


Forward as tuple
Constructs a tuple object with rvalue references to the elements in args suitable to be forwarded as argument to a function.
                                ^^^^^^^^

This function is designed to forward arguments, not to store its result in a named variable, 
                    ^^^^     ^^^^^^^              ^^^^^^^
since the returned object may contain references to temporary variables.
                                            ^^^^^^^^^^^^^^

It is equivalent to:

    template<class... Types>
      tuple<Types&&...> forward_as_tuple (Types&&... args) noexcept
    {
      return tuple<Types&&...>(std::forward<Types>(args)...);
    }


*/


void print_pack (std::tuple<std::string&&,int&&> pack) {
  std::cout << std::get<0>(pack) << ", " << std::get<1>(pack) << '\n';
}

int main() {
  std::string str ("John");
  print_pack (std::forward_as_tuple(str+" Smith",25));
  print_pack (std::forward_as_tuple(str+" Daniels",22));
  return 0;
}