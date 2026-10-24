#include "Span.hpp"

#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>

static int failures = 0;

static void check(bool condition, const char *label)
{
    if (condition)
        std::cout << "[OK]   " << label << std::endl;
    else
    {
        std::cout << "[FAIL] " << label << std::endl;
        ++failures;
    }
}

static void checkEqual(unsigned int actual, unsigned int expected, const char *label)
{
    if (actual == expected)
        std::cout << "[OK]   " << label << " (" << actual << ")" << std::endl;
    else
    {
        std::cout << "[FAIL] " << label << " (expected " << expected
                  << ", got " << actual << ")" << std::endl;
        ++failures;
    }
}

static unsigned int distanceOf(int a, int b)
{
    if (a >= b)
        return static_cast<unsigned int>(a) - static_cast<unsigned int>(b);
    return static_cast<unsigned int>(b) - static_cast<unsigned int>(a);
}

static unsigned int expectedShortest(std::vector<int> values)
{
    std::sort(values.begin(), values.end());

    unsigned int shortest = static_cast<unsigned int>(-1);
    for (std::size_t i = 1; i < values.size(); ++i)
        shortest = std::min(shortest, distanceOf(values[i], values[i - 1]));
    return shortest;
}

static bool shortestThrows(const Span &span)
{
    try
    {
        span.shortestSpan();
    }
    catch (const Span::NoSpanException &)
    {
        return true;
    }
    catch (...)
    {
    }
    return false;
}

static bool longestThrows(const Span &span)
{
    try
    {
        span.longestSpan();
    }
    catch (const Span::NoSpanException &)
    {
        return true;
    }
    catch (...)
    {
    }
    return false;
}

int main()
{
    std::cout << "--- Subject example ---" << std::endl;
    Span subject(5);
    subject.addNumber(6);
    subject.addNumber(3);
    subject.addNumber(17);
    subject.addNumber(9);
    subject.addNumber(11);
    std::cout << subject.shortestSpan() << std::endl;
    std::cout << subject.longestSpan() << std::endl;
    checkEqual(subject.shortestSpan(), 2, "subject example shortest span");
    checkEqual(subject.longestSpan(), 14, "subject example longest span");

    std::cout << "--- Exceptions ---" << std::endl;
    Span empty(4);
    check(shortestThrows(empty), "shortestSpan throws with no numbers");
    check(longestThrows(empty), "longestSpan throws with no numbers");

    Span single(2);
    single.addNumber(42);
    check(shortestThrows(single), "shortestSpan throws with one number");
    check(longestThrows(single), "longestSpan throws with one number");

    Span full(2);
    full.addNumber(1);
    full.addNumber(2);
    bool caught = false;
    try
    {
        full.addNumber(3);
    }
    catch (const Span::FullException &)
    {
        caught = true;
    }
    check(caught, "addNumber throws when the span is full");
    checkEqual(full.size(), 2, "failed addNumber leaves the span unchanged");

    Span defaultSpan;
    caught = false;
    try
    {
        defaultSpan.addNumber(1);
    }
    catch (const Span::FullException &)
    {
        caught = true;
    }
    check(caught, "a default span has a capacity of zero");

    std::cout << "--- 10,000 numbers ---" << std::endl;
    std::vector<int> tenThousand;
    tenThousand.reserve(10000);
    for (int i = 0; i < 10000; ++i)
        tenThousand.push_back(i);

    Span big(10000);
    big.addNumbers(tenThousand.begin(), tenThousand.end());
    checkEqual(big.size(), 10000, "10,000 numbers inserted in one call");
    checkEqual(big.shortestSpan(), 1, "shortest span of 0..9999");
    checkEqual(big.longestSpan(), 9999, "longest span of 0..9999");

    std::vector<int> oneMore(1, 42);
    caught = false;
    try
    {
        big.addNumbers(oneMore.begin(), oneMore.end());
    }
    catch (const Span::FullException &)
    {
        caught = true;
    }
    check(caught, "addNumbers throws when the range does not fit");
    checkEqual(big.size(), 10000, "failed addNumbers leaves the span unchanged");

    std::vector<int> emptyRange;
    caught = false;
    try
    {
        big.addNumbers(emptyRange.begin(), emptyRange.end());
    }
    catch (...)
    {
        caught = true;
    }
    check(!caught, "an empty range fits even in a full span");

    Span partial(5);
    partial.addNumber(1);
    partial.addNumber(2);
    partial.addNumber(3);
    std::vector<int> four(4, 7);
    caught = false;
    try
    {
        partial.addNumbers(four.begin(), four.end());
    }
    catch (const Span::FullException &)
    {
        caught = true;
    }
    check(caught, "a bulk insert larger than the remaining space throws");
    checkEqual(partial.size(), 3, "no partial insertion on failure");

    std::cout << "--- 100,000 numbers, including negatives ---" << std::endl;
    std::vector<int> many;
    many.reserve(100000);
    for (int i = 0; i < 100000; ++i)
        many.push_back((i * 7919) % 200003 - 100000);

    Span huge(100000);
    huge.addNumbers(many.begin(), many.end());
    checkEqual(huge.size(), 100000, "100,000 numbers inserted in one call");
    checkEqual(huge.shortestSpan(), expectedShortest(many),
               "shortest span matches a reference computation");

    std::vector<int> sortedMany(many);
    std::sort(sortedMany.begin(), sortedMany.end());
    checkEqual(huge.longestSpan(),
               distanceOf(sortedMany.front(), sortedMany.back()),
               "longest span matches a reference computation");

    std::cout << "--- Edge cases ---" << std::endl;
    Span duplicates(4);
    duplicates.addNumber(5);
    duplicates.addNumber(5);
    duplicates.addNumber(9);
    duplicates.addNumber(9);
    checkEqual(duplicates.shortestSpan(), 0, "duplicates give a shortest span of zero");
    checkEqual(duplicates.longestSpan(), 4, "longest span with duplicates");

    Span extremes(2);
    extremes.addNumber(INT_MIN);
    extremes.addNumber(INT_MAX);
    checkEqual(extremes.shortestSpan(), 4294967295u, "shortest span over the int range");
    checkEqual(extremes.longestSpan(), 4294967295u, "longest span over the int range");

    std::list<int> listValues;
    for (int i = 0; i < 5; ++i)
        listValues.push_back(i * 10);
    Span fromList(5);
    fromList.addNumbers(listValues.begin(), listValues.end());
    checkEqual(fromList.shortestSpan(), 10, "addNumbers accepts list iterators");
    checkEqual(fromList.longestSpan(), 40, "longest span from list iterators");

    std::cout << "--- Input iterators ---" << std::endl;
    std::istringstream input("4 8 15 16 23 42");
    std::istream_iterator<int> inputBegin(input);
    std::istream_iterator<int> inputEnd;
    Span fromInput(6);
    fromInput.addNumbers(inputBegin, inputEnd);
    checkEqual(fromInput.size(), 6, "input iterators are consumed exactly once");
    checkEqual(fromInput.shortestSpan(), 1, "shortest span from input iterators");
    checkEqual(fromInput.longestSpan(), 38, "longest span from input iterators");

    std::istringstream tooMany("1 2 3");
    Span smallInput(2);
    caught = false;
    try
    {
        smallInput.addNumbers(std::istream_iterator<int>(tooMany),
                              std::istream_iterator<int>());
    }
    catch (const Span::FullException &)
    {
        caught = true;
    }
    check(caught, "input iterator range larger than capacity throws");
    checkEqual(smallInput.size(), 0, "no partial insertion for input iterators");

    std::cout << "--- Copies and assignment ---" << std::endl;
    Span copy(partial);
    checkEqual(copy.size(), 3, "copy constructor keeps the size");
    checkEqual(copy.shortestSpan(), 1, "copy constructor keeps the numbers");
    copy.addNumber(100);
    checkEqual(partial.size(), 3, "copy is independent from the original");
    checkEqual(copy.size(), 4, "copy keeps the original capacity");

    Span assigned;
    assigned = partial;
    checkEqual(assigned.size(), 3, "assignment keeps the size");
    checkEqual(assigned.longestSpan(), 2, "assignment keeps the numbers");
    assigned.addNumber(100);
    checkEqual(partial.size(), 3, "assignment is independent from the original");
    checkEqual(assigned.size(), 4, "assignment keeps the original capacity");

    if (failures == 0)
        std::cout << "All Span tests passed." << std::endl;
    else
        std::cout << failures << " Span test(s) failed." << std::endl;
    return failures == 0 ? 0 : 1;
}
