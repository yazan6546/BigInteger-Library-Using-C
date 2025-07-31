#include <gtest/gtest.h>
extern "C" {
    #include "utils/LinkedList.h"
}

class LinkedListTest : public ::testing::Test {
protected:
    struct node* list;

    void SetUp() override {
        list = nullptr;
    }

    void TearDown() override {
        if (list != nullptr) {
            deleteList(list);
        }
    }
};

// Test list creation and initialization
TEST_F(LinkedListTest, CreateEmptyList) {
    list = makeEmpty(list);
    std::cout << getSize(list) << std::endl;

    ASSERT_NE(list, nullptr);
    EXPECT_TRUE(isEmpty(list));
    EXPECT_EQ(getSize(list), 0);

}

TEST_F(LinkedListTest, CreateZeroList) {
    list = createZero();
    ASSERT_NE(list, nullptr);
    EXPECT_FALSE(isEmpty(list));
    EXPECT_EQ(getSize(list), 1);
}

// Test adding elements
TEST_F(LinkedListTest, AddFirst) {
    list = makeEmpty(list);

    addFirst(list, 5);
    EXPECT_FALSE(isEmpty(list));
    EXPECT_EQ(getSize(list), 1);

    addFirst(list, 3);
    EXPECT_EQ(getSize(list), 2);

    addFirst(list, 1);
    EXPECT_EQ(getSize(list), 3);
}

TEST_F(LinkedListTest, AddLast) {
    list = makeEmpty(list);

    addLast(list, 1);
    EXPECT_FALSE(isEmpty(list));
    EXPECT_EQ(getSize(list), 1);

    addLast(list, 3);
    EXPECT_EQ(getSize(list), 2);

    addLast(list, 5);
    EXPECT_EQ(getSize(list), 3);
}

TEST_F(LinkedListTest, AddMixed) {
    list = makeEmpty(list);

    addFirst(list, 2);
    addLast(list, 4);
    addFirst(list, 1);
    addLast(list, 5);

    EXPECT_EQ(getSize(list), 4);
}

// Test removing elements
TEST_F(LinkedListTest, RemoveFirst) {
    list = makeEmpty(list);

    addFirst(list, 1);
    addFirst(list, 2);
    addFirst(list, 3);

    int removed = removeFirst(list);
    EXPECT_EQ(removed, 3);
    EXPECT_EQ(getSize(list), 2);

    removed = removeFirst(list);
    EXPECT_EQ(removed, 2);
    EXPECT_EQ(getSize(list), 1);

    removed = removeFirst(list);
    EXPECT_EQ(removed, 1);
    EXPECT_EQ(getSize(list), 0);
    EXPECT_TRUE(isEmpty(list));
}

TEST_F(LinkedListTest, RemoveLast) {
    list = makeEmpty(list);

    addLast(list, 1);
    addLast(list, 2);
    addLast(list, 3);

    int removed = removeLast(list);
    EXPECT_EQ(removed, 3);
    EXPECT_EQ(getSize(list), 2);

    removed = removeLast(list);
    EXPECT_EQ(removed, 2);
    EXPECT_EQ(getSize(list), 1);

    removed = removeLast(list);
    EXPECT_EQ(removed, 1);
    EXPECT_EQ(getSize(list), 0);
    EXPECT_TRUE(isEmpty(list));
}

TEST_F(LinkedListTest, RemoveFromEmptyList) {
    list = makeEmpty(list);

    // Removing from empty list should handle gracefully
    // This might return a special value or handle error internally
    int result = removeFirst(list);
    EXPECT_TRUE(isEmpty(list));

    result = removeLast(list);
    EXPECT_TRUE(isEmpty(list));
}

// Test list copying
TEST_F(LinkedListTest, CopyList) {
    list = makeEmpty(list);
    struct node* copy_list = makeEmpty(nullptr);

    // Add some elements to original list
    addLast(list, 1);
    addLast(list, 2);
    addLast(list, 3);
    addLast(list, 4);

    // Copy the list
    copyList(list, copy_list);

    // Verify both lists have same size
    EXPECT_EQ(getSize(list), getSize(copy_list));

    // Verify elements are the same by removing and comparing
    while (!isEmpty(list) && !isEmpty(copy_list)) {
        int orig = removeFirst(list);
        int copy = removeFirst(copy_list);
        EXPECT_EQ(orig, copy);
    }

    EXPECT_TRUE(isEmpty(list));
    EXPECT_TRUE(isEmpty(copy_list));

    deleteList(copy_list);
}

TEST_F(LinkedListTest, CopyEmptyList) {
    list = makeEmpty(list);
    struct node* copy_list = makeEmpty(nullptr);

    copyList(list, copy_list);

    EXPECT_TRUE(isEmpty(copy_list));
    EXPECT_EQ(getSize(copy_list), 0);

    deleteList(copy_list);
}

// Test emptying list
TEST_F(LinkedListTest, EmptyList) {
    list = makeEmpty(list);

    addLast(list, 1);
    addLast(list, 2);
    addLast(list, 3);

    EXPECT_FALSE(isEmpty(list));
    EXPECT_EQ(getSize(list), 3);

    emptyList(list);

    EXPECT_TRUE(isEmpty(list));
    EXPECT_EQ(getSize(list), 0);
}

// Test list size and emptiness
TEST_F(LinkedListTest, SizeTracking) {
    list = makeEmpty(list);

    EXPECT_EQ(getSize(list), 0);

    for (int i = 1; i <= 10; i++) {
        addLast(list, i);
        EXPECT_EQ(getSize(list), i);
    }

    for (int i = 9; i >= 0; i--) {
        removeFirst(list);
        EXPECT_EQ(getSize(list), i);
    }
}

// Test mixed operations
TEST_F(LinkedListTest, MixedOperations) {
    list = makeEmpty(list);

    // Add some elements
    addFirst(list, 2);
    addLast(list, 4);
    addFirst(list, 1);
    addLast(list, 5);
    addFirst(list, 0);

    EXPECT_EQ(getSize(list), 5);

    // Remove some elements
    int first = removeFirst(list);
    EXPECT_EQ(first, 0);

    int last = removeLast(list);
    EXPECT_EQ(last, 5);

    EXPECT_EQ(getSize(list), 3);

    // Add more elements
    addLast(list, 6);
    addFirst(list, -1);

    EXPECT_EQ(getSize(list), 5);
}

// Test doubly linked list properties (if applicable)
TEST_F(LinkedListTest, DoublyLinkedProperties) {
    list = makeEmpty(list);

    addLast(list, 1);
    addLast(list, 2);
    addLast(list, 3);

    // Walk through the list and verify previous/next pointers
    struct node* current = list->next; // Skip head node
    int expected_data = 1;

    while (current != nullptr && current->data != 0) { // Assuming 0 or special value marks end
        EXPECT_EQ(current->data, expected_data);

        // Test that previous pointer works (if it's truly doubly linked)
        if (current->previous != nullptr && current->previous != list) {
            EXPECT_EQ(current->previous->data, expected_data - 1);
        }

        current = current->next;
        expected_data++;
    }
}

// Test head node properties
TEST_F(LinkedListTest, HeadNodeProperties) {
    list = makeEmpty(list);

    // Head node should be marked as head
    EXPECT_TRUE(list->isHead);

    addFirst(list, 1);

    // First data node should not be marked as head
    if (list->next != nullptr) {
        EXPECT_FALSE(list->next->isHead);
    }
}

// Performance test for large lists
TEST_F(LinkedListTest, LargeListOperations) {
    list = makeEmpty(list);

    const int LARGE_SIZE = 1000;

    // Add many elements
    for (int i = 0; i < LARGE_SIZE; i++) {
        addLast(list, i);
    }

    EXPECT_EQ(getSize(list), LARGE_SIZE);

    // Remove all elements
    for (int i = 0; i < LARGE_SIZE; i++) {
        int removed = removeFirst(list);
        EXPECT_EQ(removed, i);
    }

    EXPECT_TRUE(isEmpty(list));
    EXPECT_EQ(getSize(list), 0);
}
