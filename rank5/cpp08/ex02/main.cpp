#include "MutantStack.hpp"

#include <cstddef>
#include <iostream>
#include <list>
#include <stack>
#include <string>
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

static void checkEqual(std::size_t actual, std::size_t expected, const char *label)
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

int main()
{
    std::cout << "--- Subject example ---" << std::endl;
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl;

    mstack.pop();

    std::cout << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);

    checkEqual(s.size(), 5, "convertible to std::stack");
    checkEqual(s.top(), 0, "converted stack keeps its top");

    std::cout << "--- Iteration ---" << std::endl;
    std::vector<int> expected;
    expected.push_back(5);
    expected.push_back(3);
    expected.push_back(5);
    expected.push_back(737);
    expected.push_back(0);

    std::vector<int> stackValues(mstack.begin(), mstack.end());
    check(stackValues == expected,
          "iterators run from bottom to top");

    std::list<int> asList;
    asList.push_back(5);
    asList.push_back(3);
    asList.push_back(5);
    asList.push_back(737);
    asList.push_back(0);
    std::vector<int> listValues(asList.begin(), asList.end());
    check(stackValues == listValues,
          "MutantStack output matches std::list output");

    std::vector<int> reversed(mstack.rbegin(), mstack.rend());
    std::vector<int> expectedReverse(expected.rbegin(), expected.rend());
    check(reversed == expectedReverse,
          "reverse iterators run from top to bottom");

    std::cout << "--- Const iteration ---" << std::endl;
    const MutantStack<int> &constStack = mstack;
    std::vector<int> constValues(constStack.begin(), constStack.end());
    check(constValues == expected, "const iterators return the same values");

    std::vector<int> constReverse(constStack.rbegin(), constStack.rend());
    check(constReverse == expectedReverse,
          "const reverse iterators return the same values");

    MutantStack<int>::const_iterator constIt = constStack.begin();
    MutantStack<int>::const_reverse_iterator constRit = constStack.rbegin();
    check(*constIt == 5, "const_iterator points to the bottom");
    check(*constRit == 0, "const_reverse_iterator points to the top");

    std::cout << "--- Copies, assignment and empty stacks ---" << std::endl;
    MutantStack<int> copy(mstack);
    copy.push(99);
    checkEqual(copy.size(), 6, "copy constructor copies the contents");
    checkEqual(mstack.size(), 5, "copy is independent from the original");
    copy.pop();
    check(std::vector<int>(copy.begin(), copy.end()) == expected,
          "copy has the same values after removing the extra element");

    MutantStack<int> assigned;
    assigned.push(1234);
    assigned = mstack;
    checkEqual(assigned.size(), 5, "assignment copies the contents");
    check(std::vector<int>(assigned.begin(), assigned.end()) == expected,
          "assigned stack has the same values");
    assigned.pop();
    checkEqual(mstack.size(), 5, "assignment is independent from the original");

    MutantStack<int> emptyStack;
    check(emptyStack.begin() == emptyStack.end(), "empty stack begin == end");
    check(emptyStack.rbegin() == emptyStack.rend(),
          "empty stack rbegin == rend");

    std::cout << "--- Custom underlying container ---" << std::endl;
    MutantStack<std::string, std::vector<std::string> > words;
    words.push("first");
    words.push("second");
    words.push("third");
    std::vector<std::string> wordValues(words.begin(), words.end());
    checkEqual(wordValues.size(), 3, "works with std::vector as container");
    check(wordValues[0] == "first" && wordValues[2] == "third",
          "custom container iteration order");

    if (failures == 0)
        std::cout << "All MutantStack tests passed." << std::endl;
    else
        std::cout << failures << " MutantStack test(s) failed." << std::endl;
    return failures == 0 ? 0 : 1;
}
