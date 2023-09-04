// https://www.slamecka.cz/posts/2021-03-17-cpp-metaprogramming-exercises-1/
//
// This is a set of exercises for type level programming in C++, suitable for
// beginners or as a refresher for intermediate programmers.
//
// Scope:
// - Most exercises in this set are confined to vectors of integers for simplicity.
// - Exercises are centered around basic functional techniques since they are easy to express with template metaprogramming.
//
// How to solve it:
// - You should be able to compile with gcc version 10.2, g++ --std=c++20 typelevel_set1.cpp
// - You should understand the requested behaviours from static_assert-s,
//   except for print, which comes with a test in main().
// - Tests are commented-out and you should uncomment them as you go.
// - You might want to read some introductory material before attempting these:
//
//   https://en.cppreference.com/w/cpp/language/templates
//
//   https://en.cppreference.com/w/cpp/language/parameter_pack
//
//   https://en.cppreference.com/w/cpp/language/template_parameters
//      in this set we'll only see non-type template parameters and type template parameters
//
//   https://en.cppreference.com/w/cpp/header/type_traits
//
//   https://en.cppreference.com/w/cpp/language/partial_specialization
//      also see https://stackoverflow.com/questions/17005985/what-is-the-partial-ordering-procedure-in-template-deduction
//

#include <iostream>
#include <algorithm>
#include <type_traits>

namespace {

/**
 * 1. Define Vector, a template level list of integers.
 * Hint: Use non-type template parameter pack.
 */

// Your code goes here:
template<int ...>
struct Vector{
};
// ^ Your code goes here
static_assert(std::is_same_v<Vector<1,2>, Vector<1,2>>);


/**
 * 2. Define function print() that prints Vector-s.
 * Example: print(Vector<1,2,3>{}); // prints "1 2 3" (newline)
 * See main() below.
 */

// Your code goes here:
template<int N, int ... Rest>
void print(Vector<N, Rest ...>)
{
  std::cout << N << " ";
  print(Vector<Rest ...>{});
}

template<int N>
void print(Vector<N>)
{
  std::cout << N << std::endl;
}

template<int ... Rest>
void print(Vector<Rest ...>)
{
  std::cout << std::endl;
}
// ^ Your code goes here

/**
 * 3. Define Prepend.
 * Hint: Use `using type = ...` inside a struct that has both non-type and type template parameters.
 */

// Your code goes here:
template<int N, typename T>
struct Prepend;

template<int N, int ...Rest>
struct Prepend<N, Vector<Rest...>> {
  using type = Vector<N, Rest...>;
};
// ^ Your code goes here

static_assert(std::is_same_v<Prepend<1, Vector<2,3>>::type, Vector<1,2,3>>);


/**
 * 4. Define PrependT that can be used without ::type.
 * Hint: See how enable_if_t is defined in terms of enable_if.
 *
 * This technique is not used further to reduce boilerplate.
 */

// Your code goes here:
template<int N, typename T>
using PrependT = Prepend<N, T>::type;
// ^ Your code goes here

static_assert(std::is_same_v<PrependT<1, Vector<2,3>>, Vector<1,2,3>>);


/**
 * 5. Define Append.
 */

// Your code goes here:
template<int N, typename T>
struct Append;

template<int N>
struct Append<N, Vector<>> {
  using type = Vector<N>;
};

template<int N, int H, int ... Rest>
struct Append<N, Vector<H, Rest ...>> {
  using type = typename Prepend<H, typename Append<N, Vector<Rest ...>>::type>::type;
};
// ^ Your code goes here

static_assert(std::is_same_v< Append<4, Vector<1,2,3>>::type , Vector<1,2,3,4> >);

/**
 * 6. Define PopBack.
 */

// Your code goes here:
template<typename T>
struct PopBack;

template<int H>
struct PopBack<Vector<H>> {
  using type = Vector<>;
};

template<int H, int ... T>
struct PopBack<Vector<H, T ...>> {
  using type = typename Prepend<H, typename PopBack<Vector<T ...>>::type>::type;
};
// ^ Your code goes here

static_assert(std::is_same_v< PopBack<Vector<1,2,3,4>>::type , Vector<1,2,3> >);


/**
 * 7. Define RemoveFirst, that removes the first occurence of element R from vector V.
 */

// Your code goes here:
template<int N, typename T>
struct RemoveFirst;

template<int N>
struct RemoveFirst<N, Vector<>> {
  using type = Vector<>;
};

template<int N, int H, int ... T>
struct RemoveFirst<N, Vector<H, T ...>> {
  using type = typename std::conditional_t<N == H, Vector<T...>, typename Prepend<H, typename RemoveFirst<N, Vector<T...>>::type>::type>;
};
// ^ Your code goes here

static_assert(std::is_same_v<RemoveFirst<1, Vector<1,1,2>>::type, Vector<1,2>>);


/**
 * 8. Define RemoveAll, that removes all occurences of element R from vector V.
 */

// Your code goes here:
template<int N, typename T>
struct RemoveAll;

template<int N>
struct RemoveAll<N, Vector<>> {
  using type = Vector<>;
};

template<int N, int H, int ... T>
struct RemoveAll<N, Vector<H, T ...>> {
  using type = typename std::conditional_t<N == H, typename RemoveAll<N, Vector<T ...>>::type, typename Prepend<H, typename RemoveAll<N, Vector<T...>>::type>::type>;
};
// ^ Your code goes here

static_assert(std::is_same_v<RemoveAll<9, Vector<1,9,2,9,3,9>>::type, Vector<1,2,3>>);


/**
 * 9. Define Length.
 * Hint: Use `static constexpr int value = ...` inside the struct.
 */

// Your code goes here:
template<typename T>
struct Length;

template<int ... T>
struct Length<Vector<T...>> {
  static constexpr int value = sizeof...(T);
};
// ^ Your code goes here

static_assert(Length<Vector<1,2,3>>::value == 3);


/**
 * 10. Define length, which works like Length<V>::value.
 * Hint: See how is_same_v is defined in terms of is_same.
 */

// Your code goes here:
template<typename T>
constexpr int length = Length<T>::value;
// ^ Your code goes here

static_assert(length<Vector<>> == 0);
static_assert(length<Vector<1,2,3>> == 3);


/**
 * 11. Define Min, that stores the minimum of a vector in its property `value`.
 */

// Your code goes here:
template<typename T>
struct Min;

template<int ... T>
struct Min<Vector<T...>> {
  static constexpr int value = std::min(std::initializer_list<int>{T...});
};
// ^ Your code goes here

static_assert(Min<Vector<3,1,2>>::value == 1);
static_assert(Min<Vector<1,2,3>>::value == 1);
static_assert(Min<Vector<3,2,1>>::value == 1);


/**
 * 12. Define Sort.
 */

// Your code goes here:
template<typename T>
struct Sort;

template<>
struct Sort<Vector<>> {
    using type = Vector<>;
};

template<int ... T>
struct Sort<Vector<T...>> {
  static constexpr int min_value = Min<Vector<T...>>::value;
  using tail = RemoveFirst<min_value, Vector<T...>>::type;

  using type = Prepend<min_value, typename Sort<tail>::type>::type;
};
// ^ Your code goes here

static_assert(std::is_same_v<Sort<Vector<4,1,2,5,6,3>>::type, Vector<1,2,3,4,5,6>>);
static_assert(std::is_same_v<Sort<Vector<3,3,1,1,2,2>>::type, Vector<1,1,2,2,3,3>>);
static_assert(std::is_same_v<Sort<Vector<2,2,1,1,3,3>>::type, Vector<1,1,2,2,3,3>>);


/**
 * 13. Define Uniq.
 */

// Your code goes here:
// ^ Your code goes here

// static_assert(std::is_same_v<Uniq<Vector<1,1,2,2,1,1>>::type, Vector<1,2,1>>);


/**
 * 14. Define type Set.
 */

// Your code goes here:
// ^ Your code goes here

// static_assert(std::is_same_v<Set<2,1,3,1,2,3>::type, Set<1,2,3>::type>);


/**
 * 15. Define SetFrom.
 */

// Your code goes here:
// ^ Your code goes here

// static_assert(std::is_same_v<SetFrom<Vector<2,1,3,1,2,3>>::type, Set<1,2,3>::type>);


/**
 * 16. Define Get for Vector.
 * Provide an improved error message when accessing outside of Vector bounds.
 */

// Your code goes here:
// ^ Your code goes here

// static_assert(Get<0, Vector<0,1,2>>::value == 0);
// static_assert(Get<1, Vector<0,1,2>>::value == 1);
// static_assert(Get<2, Vector<0,1,2>>::value == 2);
// static_assert(Get<9, Vector<0,1,2>>::value == 2); // How good is your error message?


/**
 * 17. Define BisectLeft for Vector.
 * Given n and arr, return the first index i such that arr[i] >= n.
 * If it doesn't exist, return the length of the array.
 *
 * Don't worry about complexity but aim for the binary search pattern.
 *
 * Hint: You might find it convenient to define a constexpr helper function.
 */

// Your code goes here:
// ^ Your code goes here

// static_assert(BisectLeft<  3, Vector<0,1,2,3,4>>::value == 3);
// static_assert(BisectLeft<  3, Vector<0,1,2,4,5>>::value == 3);
// static_assert(BisectLeft<  9, Vector<0,1,2,4,5>>::value == 5);
// static_assert(BisectLeft< -1, Vector<0,1,2,4,5>>::value == 0);
// static_assert(BisectLeft<  2, Vector<0,2,2,2,2,2>>::value == 1);


/**
 * 18. Define Insert for Vector, it should take position, value and vector.
 * Don't worry about bounds.
 * Hint: use the enable_if trick, e.g.
 *   template<typename X, typename Enable = void> struct Foo;
 *   template<typename X> struct<std::enable_if_t<..something      about X..>> Foo {...};
 *   template<typename X> struct<std::enable_if_t<..something else about X..>> Foo {...};
 */

// Your code goes here:
// ^ Your code goes here

// static_assert(std::is_same_v<Insert<0, 3, Vector<4,5,6>>::type, Vector<3,4,5,6>>);
// static_assert(std::is_same_v<Insert<1, 3, Vector<4,5,6>>::type, Vector<4,3,5,6>>);
// static_assert(std::is_same_v<Insert<2, 3, Vector<4,5,6>>::type, Vector<4,5,3,6>>);
// static_assert(std::is_same_v<Insert<3, 3, Vector<4,5,6>>::type, Vector<4,5,6,3>>);

}

int main()
{
  print(Vector<>{});
  print(Vector<1>{});
  print(Vector<1,2,3,4,5,6>{});
  std::cout << typeid(Vector<1,2,3,4,5,6>{}).name() << '\n';
  std::cout << "done" << std::endl;
}
