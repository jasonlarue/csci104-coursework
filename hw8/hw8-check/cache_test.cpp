#include "../cacheLRU.h"
#include "gtest/gtest.h"
#include <cassert>

/**
 * README.md:
 * Place this cpp inside the "hw8-check" folder.  replace the Makefile with the one
 * I sent you. "make test" will run the splayTree test and the cache test.
 * "make cache_test" and run ./cache_test to just run the cache test
 *
 * In the functions in InheritedCache, replace "mCapacity" and "mCurrentSize"
 * with your member functions of the same function.  Also make sure those variables
 * are protected or public, not private.
 *
 */

template <typename Key, typename Value>
class InheritedCache : public cacheLRU<Key, Value>
{
public:
    InheritedCache(int capacity) : cacheLRU<Key, Value>(capacity)
    {

    }
    Node<Key, Value>* getRoot()
    {
        return this->mRoot;
    }
    int getCapacity()
    {
        return this->_capacity;
    }
    int getCurrentSize()
    {
        return this->_capacity_used;
    }
};

class CacheTest : public testing::Test
{

};

// Tests constructor
TEST_F(CacheTest, Test1_Construction)
{
    InheritedCache<int, int> cache(16);

    EXPECT_EQ(16, cache.getCapacity());
    EXPECT_EQ(0, cache.getCurrentSize());

}

// Puts 1 item in cache
TEST_F(CacheTest, Test2_Put)
{
    InheritedCache<int, int> cache(16);
    cache.put(std::pair<int, int>(1, 1));

    EXPECT_EQ(1, cache.getRoot()->getKey());
    EXPECT_EQ(16, cache.getCapacity());
    EXPECT_EQ(1, cache.getCurrentSize());
}

// Puts and gets 1 item
TEST_F(CacheTest, Test3_Get1)
{
    InheritedCache<int, int> cache(16);
    cache.put(std::pair<int, int>(1, 1));

    EXPECT_EQ(1, cache.getRoot()->getKey());
    EXPECT_EQ(16, cache.getCapacity());
    EXPECT_EQ(1, cache.getCurrentSize());

    EXPECT_EQ(1, cache.get(1).first);

}

// Fills a cache to its capacity
TEST_F(CacheTest, Test4_FillCapacity)
{
    InheritedCache<int, int> cache(3);
    cache.put(std::pair<int, int>(1, 1));
    cache.put(std::pair<int, int>(2, 2));
    cache.put(std::pair<int, int>(3, 3));

    EXPECT_EQ(2, cache.getCurrentSize());
    EXPECT_EQ(2, cache.get(2).first);
    EXPECT_EQ(3, cache.get(3).first);

}

// Tries to get a key that isn't there
TEST_F(CacheTest, Test5_BadGet)
{
    InheritedCache<int, int> cache(3);
    cache.put(std::pair<int, int>(1, 1));

    bool caught = false;

    // next section causes segfault if your program doesn't
    // throw an exception appropriately, otherwise its fine
    try
    {
        cache.get(2);
    }
    catch (std::logic_error)
    {
        caught = true;
    }

    EXPECT_EQ(true, caught);

}

// Puts in an item that already exists, splaying it instead
TEST_F(CacheTest, Test6_PutExists)
{
    InheritedCache<int, int> cache(3);
    cache.put(std::pair<int, int>(1, 1));
    cache.put(std::pair<int, int>(2, 2));
    cache.put(std::pair<int, int>(1, 1));

    EXPECT_EQ(2, cache.getCurrentSize());
    EXPECT_EQ(1, cache.getRoot()->getKey());
}
