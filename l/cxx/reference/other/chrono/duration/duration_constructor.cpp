

/*

(1) duration() = default;
(2) duration (const duration& dtn);
(3) template<class Rep2, class Period2>
    constexpr duration (const duration<Rep2,Period2>& dtn);
(4) template<class Rep2>
    constexpr explicit duration (const Rep2& n);

Construct duration object
Constructs a duration object:
default constructor (1)
    Constructs an object, with a default-initialized count value.
from duration object (2), (3)
    Initializes the object to a duration of dtn.
from representation (4)
    Initializes the object to a duration whose count is n.

The initialization constructors (3) and (4) are only called when the Rep2 type is not wider than the
rep type used in the newly constructed duration object (and cannot cause implicit truncation errors).

In this regard, if the treat_as_floating_point value for rep is true, Rep2 is never considered wider.

In order to force a conversion between duration types no matter their precisions, 
even if this can cause a truncation, you can use duration_cast.
                                                  ^^^^^^^^^^

Parameters
dtn
    Another duration object.
    duration<Rep2,Period2> is a type that cannot cause an implicit truncation error when converted.
n
    The count value.
    Rep2 is an arithmetic type (or a class emulating an arithmetic type).


*/


// duration constructor
#include <iostream>
#include <ratio>
#include <chrono>

int main ()
{
  typedef std::chrono::duration<int> seconds_type;
  typedef std::chrono::duration<int,std::milli> milliseconds_type;
  typedef std::chrono::duration<int,std::ratio<60*60>> hours_type;

  hours_type h_oneday (24);                  // 24h
  seconds_type s_oneday (60*60*24);          // 86400s
  milliseconds_type ms_oneday (s_oneday);    // 86400000ms

  seconds_type s_onehour (60*60 + 1);            // 3600s
//hours_type h_onehour (s_onehour);          // NOT VALID (type truncates), use:
  hours_type h_onehour (std::chrono::duration_cast<hours_type>(s_onehour));
  std::cout << "h_onehour is :" << h_onehour.count() << " hour" << std::endl;
  milliseconds_type ms_onehour (s_onehour);  // 3600000ms (ok, no type truncation)

  std::cout << "ms_onehour has " <<  ms_onehour.count() << " ms" << std::endl;

  // create a day type
  typedef std::chrono::duration<int, std::ratio<60*60*24, 1> day_type;
  day_type day = std::chrono::duration_cast<day_type>(ms_onehour);
  std::cout << ""


  return 0;
}