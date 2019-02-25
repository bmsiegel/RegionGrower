#define CATCH_CONFIG_MAIN

#include "Stack.hpp"
#include "catch.hpp"
#include "Node.hpp"

TEST_CASE("Tests Push")
{
  Stack<int> L;
  REQUIRE(L.push(10));
  REQUIRE(L.push(12));
  REQUIRE(L.size() == 2);
}
TEST_CASE("Tests Peek and clear")
{
  Stack<int> L;
  L.push(10);
  L.push(12);
  REQUIRE(L.size() == 2);
  REQUIRE(L.peek() == 12);
  REQUIRE(L.size() == 2);
  L.clear();
  REQUIRE_THROWS(L.peek());
}
TEST_CASE("Tests Pop and isEmpty")
{
  Stack<int> L;
  L.push(10);
  L.push(12);
  REQUIRE(L.size() == 2);
  REQUIRE(L.pop());
  REQUIRE(L.pop());
  REQUIRE(L.isEmpty());
  REQUIRE_FALSE(L.pop());
}
TEST_CASE("Tests Copy Constructor and Clear")
{
  Stack<int> L;
  for (int c = 10; c < 100; c++)
  {
    L.push(c);
  }
  Stack<int> copy = L;
  for (int c = 10; c < 100; c++)
  {
    REQUIRE(L.peek() == copy.peek());
    REQUIRE(L.pop());
    REQUIRE(copy.pop());
  }
  L.clear();
  REQUIRE_FALSE(L.pop());
  REQUIRE(L.size() == 0);
}
TEST_CASE("Tests Equals Operator")
{
  Stack<int> L;
  for (int c = 10; c < 100; c++)
  {
    L.push(c);
  }
  Stack<int> copy;
  for (int c = 1000; c < 1100; c++)
  {
    copy.push(c);
  }
  copy = L;
  for (int c = 10; c < 100; c++)
  {
    REQUIRE(copy.peek() == L.peek());
    REQUIRE(L.pop());
    REQUIRE(copy.pop());
  }
  REQUIRE(L.size() == copy.size());
}
