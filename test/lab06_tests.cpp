#include "gtest/gtest.h"
#include "doubly_linked_list.h"
#include <algorithm>

class DoublyLinkedListTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        doublyLinkedListUT = new lab6::doubly_linked_list();
    }

    virtual void TearDown() {
        delete doublyLinkedListUT;
    }

public:
    lab6::doubly_linked_list *doublyLinkedListUT;
};

TEST(CrashTest, doublyLinkedList_crashTest) {
    std::vector<int> number_list;
    lab6::doubly_linked_list *list;

    for (int i = 0; i < 20; i++) {
        number_list.push_back(i);
    }

    list = new lab6::doubly_linked_list();
    delete list;
    list = new lab6::doubly_linked_list(73);
    delete list;
    list = new lab6::doubly_linked_list(number_list);
}

TEST_F(DoublyLinkedListTest, append_get_data_get_set_test) {
    std::vector<int> expected_set;
    EXPECT_TRUE(doublyLinkedListUT->is_empty());
    for (int i = 1; i < 200; ++i) {
        doublyLinkedListUT->append(i);
        ASSERT_EQ(i, doublyLinkedListUT->size());
        expected_set.push_back(i);
        for (int j = 0; j < i; ++j) {
            ASSERT_EQ(expected_set[j], doublyLinkedListUT->get_data(j)) << "Iteration: i= " << i << " j= " << j;
        }
    }

    ASSERT_EQ(expected_set, doublyLinkedListUT->get_set(0, doublyLinkedListUT->size() - 1));
    ASSERT_EQ(std::vector<int>(expected_set.begin(), expected_set.begin() + expected_set.size() / 2),
              doublyLinkedListUT->get_set(0, doublyLinkedListUT->size() / 2 - 1));//first half of data
    ASSERT_EQ(std::vector<int>(expected_set.begin() + expected_set.size() / 2 + 1, expected_set.end()),
              doublyLinkedListUT->get_set(doublyLinkedListUT->size() / 2 + 1, doublyLinkedListUT->size() - 1));//second half of data
}

TEST_F(DoublyLinkedListTest, insert_remove_test) {
    EXPECT_NO_THROW(doublyLinkedListUT->insert(3, 0));
    EXPECT_NO_THROW(doublyLinkedListUT->insert(6, 0));
    EXPECT_NO_THROW(doublyLinkedListUT->insert(4, 1));

    EXPECT_EQ(6, doublyLinkedListUT->get_data(0));
    EXPECT_EQ(4, doublyLinkedListUT->get_data(1));
    EXPECT_EQ(3, doublyLinkedListUT->get_data(2));

    doublyLinkedListUT->remove(0);
    doublyLinkedListUT->remove(0);
    doublyLinkedListUT->remove(0); // make sure both head and tail are set to nullptr when the last node is removed

    doublyLinkedListUT->append(16);
    EXPECT_EQ(16, doublyLinkedListUT->get_data(0));

}

TEST_F(DoublyLinkedListTest, opEq_insert_append_value_test) {
    auto dll_UT_copy = new lab6::doubly_linked_list;

    for (int i = 0; i < 200; ++i) {
        EXPECT_NO_THROW(doublyLinkedListUT->insert(i)) << "failed on iteration: " << i << "\n";
        EXPECT_EQ(i, doublyLinkedListUT->get_data(0)) << "failed on iteration: " << i << "\n";
    }
    dll_UT_copy->operator=(*doublyLinkedListUT);
    EXPECT_EQ(dll_UT_copy->size(), doublyLinkedListUT->size());

    for (int i = 0; i < 200; ++i) {//ensure full copy
        EXPECT_EQ(199 - i, dll_UT_copy->get_data(i)) << "failed on iteration: " << i << "\n";
    }

    for (int i = 0; i < 300; i += 2) {//alter copy
        EXPECT_NO_THROW(dll_UT_copy->insert(i * 2, i)) << "failed on iteration: " << i << "\n";
    }

    for (int i = 0; i < 200; ++i) {//check values of original after altering copy to ensure mutual exclusive nodes
        EXPECT_EQ(199 - i, doublyLinkedListUT->get_data(i)) << "failed on iteration: " << i << "\n";
    }
}

TEST_F(DoublyLinkedListTest, split_split_set_test) {
    for (int i = 0; i < 100; ++i) {
        doublyLinkedListUT->append(i);
    }

    lab6::doubly_linked_list *split_list = new lab6::doubly_linked_list;
    *split_list = doublyLinkedListUT->split(50); //50 should be the head value of the returned list
    EXPECT_EQ(49, doublyLinkedListUT->get_data(doublyLinkedListUT->size() - 1));//49 should be the tail value of  the original list

    for (int i = 0; i < split_list->size(); ++i) {
        ASSERT_EQ(i + 50, split_list->get_data(i)) << "failed on iteration: " << i << "\n";;
    }

    for (int i = 0; i < doublyLinkedListUT->size(); ++i) {
        ASSERT_EQ(i, doublyLinkedListUT->get_data(i)) << "failed on iteration: " << i << "\n";;
    }

    EXPECT_EQ(0, doublyLinkedListUT->split(0).get_data(0)); //edge case, be careful
    EXPECT_TRUE(doublyLinkedListUT->is_empty());

    delete doublyLinkedListUT;
    delete split_list;
    doublyLinkedListUT = new lab6::doubly_linked_list;
    split_list = new lab6::doubly_linked_list;

    for (int i = 0; i < 100; ++i) {
        doublyLinkedListUT->append(i);
    }

    *split_list = doublyLinkedListUT->split_set(25, 74);
    EXPECT_EQ(50, doublyLinkedListUT->size());
    EXPECT_EQ(50, split_list->size());

    for (int i = 0; i < 50; ++i) {
        ASSERT_EQ(i + 25, split_list->get_data(i)) << "failed on iteration: " << i << "\n";
    }
    for (int i = 0; i < 50; ++i) {
        if (i < 25)
            ASSERT_EQ(i, doublyLinkedListUT->get_data(i)) << "failed on iteration: " << i << "\n";
        else
            ASSERT_EQ(i + 50, doublyLinkedListUT->get_data(i)) << "failed on iteration: " << i << "\n";
    }
}

TEST_F(DoublyLinkedListTest, swap_swap_set_test) {
    for (int i = 0; i < 100; ++i) {
        doublyLinkedListUT->append(i);
    }
    for (unsigned i = 0; i < 50; ++i) {
        doublyLinkedListUT->swap(i, 99 - i);
        for (int j = 0; j < 100; ++j) {
            if (j <= i || j >= 99 - i) {
                ASSERT_EQ(99 - j, doublyLinkedListUT->get_data(j)) << "failed on iteration: i = " << i << " j = " << j << "\n";
            } else {
                ASSERT_EQ(j, doublyLinkedListUT->get_data(j)) << "failed on iteration: i = " << i << " j = " << "\n";
            }
        }
    }

    for (unsigned i = 0; i < 50; ++i) {
        doublyLinkedListUT->swap_set(i, i, 99 - i, 99 - i);//should perform single swap
        for (int j = 0; j < 100; ++j) {
            if (j <= i || j >= 99 - i) {
                ASSERT_EQ(j, doublyLinkedListUT->get_data(j)) << "failed on iteration: i = " << i << " j = " << "\n";
            } else {
                ASSERT_EQ(99 - j, doublyLinkedListUT->get_data(j)) << "failed on iteration: i = " << i << " j = " << j << "\n";
            }
        }
    }

    doublyLinkedListUT->swap_set(0, 49, 50, 99);

    for (unsigned i = 0; i < 100; ++i) {
        if (i < 50)
            ASSERT_EQ(i + 50, doublyLinkedListUT->get_data(i)) << "failed on iteration: " << i << "\n";
        else
            ASSERT_EQ(i - 50, doublyLinkedListUT->get_data(i)) << "failed on iteration: " << i << "\n";
    }
}

TEST_F(DoublyLinkedListTest, op_plus_op_plus_eq_test) {
    lab6::doubly_linked_list *dll_UT_2 = new lab6::doubly_linked_list;
    lab6::doubly_linked_list *merged_list = new lab6::doubly_linked_list;

    for (unsigned i = 0; i < 50; ++i) {
        doublyLinkedListUT->append(i);
        dll_UT_2->append(i + 50);
    }

    *merged_list = *doublyLinkedListUT + *dll_UT_2;

    *doublyLinkedListUT += *dll_UT_2;
    delete dll_UT_2; // make sure a copy is appended in +=

    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(i, doublyLinkedListUT->get_data(i)) << "failed on iteration: " << i << "\n";
    }

    delete doublyLinkedListUT; // make sure a copy is returned in +
    doublyLinkedListUT = nullptr;//avoid deleting a bad address is tear down

    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(i, merged_list->get_data(i)) << "failed on iteration: " << i << "\n";
    }
}

TEST_F(DoublyLinkedListTest, compare_op_test) {
    for (int i = 0; i < 100; ++i) {
        doublyLinkedListUT->append(i);
    }
    EXPECT_TRUE(*doublyLinkedListUT == *doublyLinkedListUT);

    lab6::doubly_linked_list *comp_list = new lab6::doubly_linked_list;

    for (int i = 0; i < 100; ++i) {
        comp_list->append(doublyLinkedListUT->get_data(i));
    }
    EXPECT_TRUE(*doublyLinkedListUT == *comp_list);
    delete comp_list;
    comp_list = new lab6::doubly_linked_list;


    for (int i = 0; i < 100; ++i) {
        comp_list->append(doublyLinkedListUT->get_data(99 - i));
    }
    EXPECT_FALSE(*doublyLinkedListUT == *comp_list);

    delete comp_list;
    comp_list = new lab6::doubly_linked_list;


    for (int i = 0; i < 50; ++i) {
        comp_list->append(doublyLinkedListUT->get_data(i));
    }
    EXPECT_FALSE(*doublyLinkedListUT == *comp_list);

    delete comp_list;
    comp_list = new lab6::doubly_linked_list;


    for (int i = 0; i < 100; ++i) {
        comp_list->append(doublyLinkedListUT->get_data(99 - i));
    }
    for (int i = 100; i < 150; ++i) {
        comp_list->append(i);
    }
    EXPECT_FALSE(*doublyLinkedListUT == *comp_list);
}

TEST_F(DoublyLinkedListTest, insertion_extraction_op_test) {
    std::string expected_output;
    std::string input("50");
    std::stringstream stream(input);

    stream >> *doublyLinkedListUT;
    EXPECT_EQ(stoi(input), doublyLinkedListUT->get_data(0));
    expected_output = input + " -> ";

    for (int i = 1; i < 49; ++i) {
        input = std::to_string(i);
        expected_output = input + " <-> " + expected_output;
        EXPECT_NO_THROW(doublyLinkedListUT->insert(i)) << "failed on iteration: " << i << "\n";
    }
    expected_output = "NULL <- " + expected_output;
    expected_output += "NULL";

    testing::internal::CaptureStdout();
    std::cout << *doublyLinkedListUT;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(expected_output, output);
}

TEST_F(DoublyLinkedListTest, sort_test) {
    unsigned const list_length_count = 100;
    auto container1 = new std::vector<int>;
    container1->reserve(30);
    //srand((unsigned )time(NULL)); //Used to randomize test, seed with constant to make test repeatable
    srand(0);

    for (int i = 0; i < list_length_count; ++i) {
        int input = rand() % 200;
        container1->emplace_back(input);
        doublyLinkedListUT->append(input);
    }

    std::sort(container1->begin(), container1->end());
    doublyLinkedListUT->sort();

    for (int i = 0; i < list_length_count; ++i) {
        EXPECT_EQ((*container1)[i], doublyLinkedListUT->get_data(i));
    }

}