#include <array>
#include <chrono>
#include <deque>
#include <forward_list>
#include <list>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <range/v3/all.hpp>
namespace views = ranges::views;
namespace Ranges = ranges;
using namespace std;

void range_test_01() {
    // https://zh.cppreference.com/w/cpp/ranges
    std::vector<int> ints{ 0,1,2,3,4,5 };
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    for (int i : ints | views::filter(even) | views::transform(square)) {
        std::cout << i << ' ';
    }
    cout << "\n";
}

// https://github.com/ericniebler/range-v3/blob/master/example/accumulate_ints.cpp
void range_test_02() {
    int sum = Ranges::accumulate(views::ints(1, Ranges::unreachable) | views::transform([](int i) {
    return i * i;
        }) | views::take(10),
            0);
    // prints: 385
    cout << sum << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/any_all_none_of.cpp
void range_test_03() {
    auto is_six = [](int i) { return i == 6; };
    std::vector<int> v{ 6, 2, 3, 4, 5, 6 };
    cout << std::boolalpha;
    cout << "vector: " << Ranges::views::all(v) << '\n';

    cout << "vector any_of is_six: " << Ranges::any_of(v, is_six) << '\n';
    cout << "vector all_of is_six: " << Ranges::all_of(v, is_six) << '\n';
    cout << "vector none_of is_six: " << Ranges::none_of(v, is_six) << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/comprehension_conversion.cpp
void range_test_04() {
    using namespace Ranges;
    auto vi = views::for_each(views::ints(1, 6),
        [](int i) { return yield_from(views::repeat_n(i, i)); }) |
        to<std::vector>();
    // prints: [1,2,2,3,3,3,4,4,4,4,5,5,5,5,5]
    cout << views::all(vi) << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/comprehensions.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Benchmark Code
////////////////////////////////////////////////////////////////////////////////////////////////////
class timer
{
private:
    std::chrono::high_resolution_clock::time_point start_;

public:
    timer()
    {
        reset();
    }
    void reset()
    {
        start_ = std::chrono::high_resolution_clock::now();
    }
    std::chrono::milliseconds elapsed() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start_);
    }
    friend std::ostream& operator<<(std::ostream& sout, timer const& t)
    {
        return sout << t.elapsed().count() << "ms";
    }
};

void benchmark()
{
    // Define an infinite range containing all the Pythagorean triples:
    auto triples = views::for_each(views::iota(1), [](int z) {
        return views::for_each(views::iota(1, z + 1), [=](int x) {
            return views::for_each(views::iota(x, z + 1), [=](int y) {
                return Ranges::yield_if(x * x + y * y == z * z,
                    std::make_tuple(x, y, z));
                });
            });
        });

    static constexpr int max_triples = 3000;

    timer t;
    int result = 0;
    RANGES_FOR(auto triple, triples | views::take(max_triples))
    {
        int i, j, k;
        std::tie(i, j, k) = triple;
        result += (i + j + k);
    }
    std::cout << t << '\n';
    std::cout << result << '\n';

    result = 0;
    int found = 0;
    t.reset();
    for (int z = 1;; ++z)
    {
        for (int x = 1; x <= z; ++x)
        {
            for (int y = x; y <= z; ++y)
            {
                if (x * x + y * y == z * z)
                {
                    result += (x + y + z);
                    ++found;
                    if (found == max_triples)
                        goto done;
                }
            }
        }
    }
done:
    std::cout << t << '\n';
    std::cout << result << '\n';
}

void range_test_05() {
    // Define an infinite range containing all the Pythagorean triples:
    auto triples = views::for_each(views::iota(1), [](int z) {
        return views::for_each(views::iota(1, z + 1), [=](int x) {
            return views::for_each(views::iota(x, z + 1), [=](int y) {
                return Ranges::yield_if(x * x + y * y == z * z,
                    std::make_tuple(x, y, z));
                });
            });
        });

    //// This alternate syntax also works:
    // auto triples = iota(1)      >>= [] (int z) { return
    //                iota(1, z+1) >>= [=](int x) { return
    //                iota(x, z+1) >>= [=](int y) { return
    //    yield_if(x*x + y*y == z*z,
    //        std::make_tuple(x, y, z)); };}; };

    // Display the first 100 triples
    RANGES_FOR(auto triple, triples | views::take(100))
    {
        std::cout << '(' << std::get<0>(triple) << ',' << std::get<1>(triple)
            << ',' << std::get<2>(triple) << ')' << '\n';
    }
}

// https://github.com/ericniebler/range-v3/blob/master/example/count.cpp
void range_test_06() {
    std::vector<int> v{ 6, 2, 3, 4, 5, 6 };
    // note the count return is a numeric type
    // like int or long -- auto below make sure
    // it matches the implementation
    auto c = Ranges::count(v, 6);
    cout << "vector:   " << c << '\n';

    std::array<int, 6> a{ 6, 2, 3, 4, 5, 6 };
    c = Ranges::count(a, 6);
    cout << "array:    " << c << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/count_if.cpp
void range_test_07() {
    auto is_six = [](int i) -> bool { return i == 6; };

    std::vector<int> v{ 6, 2, 3, 4, 5, 6 };
    auto c = Ranges::count_if(v, is_six);
    cout << "vector:   " << c << '\n'; // 2

    std::array<int, 6> a{ 6, 2, 3, 4, 5, 6 };
    c = Ranges::count_if(a, is_six);
    cout << "array:    " << c << '\n'; // 2
}

// https://github.com/ericniebler/range-v3/blob/master/example/filter_transform.cpp
void range_test_08() {
    std::vector<int> const vi{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto rng = vi | views::filter([](int i) { return i % 2 == 0; }) |
        views::transform([](int i) { return std::to_string(i); });
    // prints: [2,4,6,8,10]
    cout << rng << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/find.cpp
void range_test_09() {

    auto is_six = [](int i) -> bool { return i == 6; };

    cout << "vector:   ";

    std::vector<int> v{ 6, 2, 6, 4, 6, 1 };
    {
        auto i = Ranges::find(v, 6); // 1 2 3 4 5 6
        cout << "*i: " << *i << '\n';
    }
    {
        auto i = Ranges::find(v, 10); // 1 2 3 4 5 6
        if (i == Ranges::end(v))
        {
            cout << "didn't find 10\n";
        }
    }
    {
        auto i = Ranges::find_if(v, is_six);
        if (i != Ranges::end(v))
        {
            cout << "*i: " << *i << '\n';
        }
    }
    {
        auto i = Ranges::find_if_not(v, is_six);
        if (i != Ranges::end(v))
        {
            cout << "*i: " << *i << '\n';
        }
    }
    {
        auto i = Ranges::find(v, 6);
        i++;
        if (i != Ranges::end(v))
        {
            cout << "*i after ++ (2 expected): " << *i;
        }
    }

    cout << "\narray:    ";

    std::array<int, 6> a{ 6, 2, 3, 4, 5, 1 };
    {
        auto i = Ranges::find(a, 6);
        if (i != Ranges::end(a))
        {
            cout << "*i: " << *i;
        }
    }
    cout << "\nlist:     ";

    std::list<int> li{ 6, 2, 3, 4, 5, 1 };
    {
        auto i = Ranges::find(li, 6);
        if (i != Ranges::end(li))
        {
            cout << "*i: " << *i;
        }
    }

    cout << "\nfwd_list: ";
    
    std::forward_list<int> fl{ 6, 2, 3, 4, 5, 1 };
    {
        auto i = Ranges::find(fl, 4);
        if (i != Ranges::end(fl))
        {
            cout << "*i: " << *i;
        }
    }
    cout << "\ndeque:    ";

    std::deque<int> d{ 6, 2, 3, 4, 5, 1 };
    {
        auto i = Ranges::find(d, 6);
        if (i != Ranges::end(d))
        {
            cout << "*i: " << *i;
        }
    }
    cout << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/for_each_assoc.cpp
auto print = [](int i) { cout << i << ' '; };
// must take a pair for map types
auto printm = [](std::pair<string, int> p) {
    cout << p.first << ":" << p.second << ' ';
};
void range_test_10() {
    cout << "set:           ";
    std::set<int> si{ 1, 2, 3, 4, 5, 6 };
    Ranges::for_each(si, print);

    cout << "\nmap:           ";
    std::map<string, int> msi{ {"one", 1}, {"two", 2}, {"three", 3} };
    Ranges::for_each(msi, printm);

    cout << "\nunordered map: ";
    std::unordered_map<string, int> umsi{ {"one", 1}, {"two", 2}, {"three", 3} };
    Ranges::for_each(umsi, printm);

    cout << "\nunordered set: ";
    std::unordered_set<int> usi{ 1, 2, 3, 4, 5, 6 };
    Ranges::for_each(usi, print);
    cout << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/for_each_sequence.cpp
void range_test_11() {
    cout << "vector:   ";
    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
    Ranges::for_each(v, print); // 1 2 3 4 5 6

    cout << "\narray:    ";
    std::array<int, 6> a{ 1, 2, 3, 4, 5, 6 };
    Ranges::for_each(a, print);

    cout << "\nlist:     ";
    std::list<int> ll{ 1, 2, 3, 4, 5, 6 };
    Ranges::for_each(ll, print);

    cout << "\nfwd_list: ";
    std::forward_list<int> fl{ 1, 2, 3, 4, 5, 6 };
    Ranges::for_each(fl, print);

    cout << "\ndeque:    ";
    std::deque<int> d{ 1, 2, 3, 4, 5, 6 };
    Ranges::for_each(d, print);
    cout << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/hello.cpp
void range_test_12() {
    std::string s{ "hello" };

    // output: h e l l o
    Ranges::for_each(s, [](char c) { cout << c << ' '; });
    cout << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/is_sorted.cpp
void range_test_13() {
    cout << std::boolalpha;
    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
    cout << "vector:   " << Ranges::is_sorted(v) << '\n';

    std::array<int, 6> a{ 6, 2, 3, 4, 5, 6 };
    cout << "array:    " << Ranges::is_sorted(a) << '\n';
}

// https://github.com/ericniebler/range-v3/blob/master/example/sort_unique.cpp
void range_test_14() {
    std::vector<int> vi{ 9, 4, 5, 2, 9, 1, 0, 2, 6, 7, 4, 5, 6, 5, 9, 2, 7,
                    1, 4, 5, 3, 8, 5, 0, 2, 9, 3, 7, 5, 7, 5, 5, 6, 1,
                    4, 3, 1, 8, 4, 0, 7, 8, 8, 2, 6, 5, 3, 4, 5 };
    vi |= Ranges::actions::sort | Ranges::actions::unique;
    // prints: [0,1,2,3,4,5,6,7,8,9]
    cout << views::all(vi) << '\n';
}

void range_test_15() {
    std::vector vec{ 1,2,3,4,5,6 };
    auto v = vec | views::reverse | views::drop(2);
    std::cout << *v.begin() << '\n';
    *v.begin() = 42;
    cout << v << '\n';
    for (auto i : vec) {
        cout << i << ' ';
    }
    cout << '\n';
}

// https://segmentfault.com/a/1190000017818111
void cpp_11() {
    std::vector<int> v{ 1, 2, 3, 4, 5 };

    std::vector<int> even;
    std::copy_if(v.begin(), v.end(), std::back_inserter(even),
        [](int i) { return i % 2 == 0; });

    std::vector<int> results;
    std::transform(even.begin(), even.end(),
        std::back_inserter(results),
        [](int i) { return i * 2; });

    for (int n : results) std::cout << n << ' ';
    std::cout << '\n';
}
void cpp_20() {
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    auto v1 = v | views::filter([](int i) { return 0 == i % 2; })
        | views::transform([](int i) { return i * 2; });
    for (auto i : v1) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main()
{
    range_test_01();
    range_test_02();
    range_test_03();
    range_test_04();
    range_test_05();
    range_test_06();
    range_test_07();
    range_test_08();
    range_test_09();
    range_test_10();
    range_test_11();
    range_test_12();
    range_test_13();
    range_test_14();
    range_test_15();

    cpp_11();
    cpp_20();
    return 0;
}
