#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector> // to test std::ranges based members

#include "singly_list.hpp"


/* -------------------------------------------Definitions---------------------------------------------------- */
using value_type = int;

/* --------------------------------Constant Iterator Constructors Tests-------------------------------------- */
TEST(singly_list__const_iterator__constructors, default_constructor) {
	adt::singly_list<int>::const_iterator cit;

	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__const_iterator__constructors, nullptr_constructor) {
	adt::singly_list<int>::const_iterator cit(nullptr);

	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

/* ----------------------------Constant Iterator Overloaded Operators Tests---------------------------------- */
TEST(singly_list__const_iterator__operators, addition_operator__filled_list) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int>::const_iterator cit = list.cbegin();
	adt::singly_list<int>::value_type value;

	EXPECT_NE(cit, nullptr);

	EXPECT_NO_THROW(value = *(cit + 0));
	EXPECT_EQ(value, 1);
	
	EXPECT_NO_THROW(value = *(cit + 1));
	EXPECT_EQ(value, 2);
	
	EXPECT_NO_THROW(value = *(cit + 2));
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(value = *(cit + 3));
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(value = *(cit + 4));
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(value = *(cit + 5));
	EXPECT_EQ(value, 6);

	EXPECT_THROW(value = *(cit + 6), std::runtime_error);
}

TEST(singly_list__const_iterator__operators, addition_operator__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator cit = list.cbegin();

	EXPECT_EQ(cit, nullptr);

	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__const_iterator__operators, addition_assignment_operator__filled_list) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int>::const_iterator start = list.cbegin(),
										  cit = list.cbegin();
	adt::singly_list<int>::value_type value;

	EXPECT_NE(cit, nullptr);

	EXPECT_NO_THROW(cit += 0);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);
	
	EXPECT_NO_THROW(cit = start);
	EXPECT_NO_THROW(cit += 1);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);
	
	EXPECT_NO_THROW(cit = start);
	EXPECT_NO_THROW(cit += 2);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit = start);
	EXPECT_NO_THROW(cit += 3);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit = start);
	EXPECT_NO_THROW(cit += 4);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit = start);
	EXPECT_NO_THROW(cit += 5);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 6);

	EXPECT_NO_THROW(cit = start);
	EXPECT_NO_THROW(cit += 6);
	EXPECT_EQ(cit, nullptr);

	EXPECT_THROW(cit += 7, std::runtime_error);
}

TEST(singly_list__const_iterator__operators, addition_assignment_operator__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator cit = list.cbegin();

	EXPECT_EQ(cit, nullptr);

	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__const_iterator__operators, assignment_operator__nullptr) {
	adt::singly_list<int>::const_iterator cit;

	cit = nullptr;

	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

/* -------------------------------------Iterator Constructors Tests------------------------------------------ */
TEST(singly_list__iterator__constructors, default_constructor) {
	adt::singly_list<int> list;
	adt::singly_list<int>::iterator it;

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(singly_list__iterator__constructors, nullptr_constructor) {
	adt::singly_list<int>::iterator it(nullptr);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

/* ---------------------------------Iterator Overloaded Operators Tests-------------------------------------- */
TEST(singly_list__iterator__operators, addition_operator__filled_list) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int>::iterator it = list.begin();
	adt::singly_list<int>::value_type value;

	EXPECT_NE(it, nullptr);

	EXPECT_NO_THROW(value = *(it + 0));
	EXPECT_EQ(value, 1);
	
	EXPECT_NO_THROW(value = *(it + 1));
	EXPECT_EQ(value, 2);
	
	EXPECT_NO_THROW(value = *(it + 2));
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(value = *(it + 3));
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(value = *(it + 4));
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(value = *(it + 5));
	EXPECT_EQ(value, 6);

	EXPECT_THROW(value = *(it + 6), std::runtime_error);
}

TEST(singly_list__iterator__operators, addition_operator__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::iterator it = list.begin();

	EXPECT_EQ(it, nullptr);

	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(singly_list__iterator__operators, addition_assignment_operator__filled_list) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int>::iterator start = list.begin(),
									it = list.begin();
	adt::singly_list<int>::value_type value;

	EXPECT_NE(it, nullptr);

	EXPECT_NO_THROW(it += 0);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 1);
	
	EXPECT_NO_THROW(it = start);
	EXPECT_NO_THROW(it += 1);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 2);
	
	EXPECT_NO_THROW(it = start);
	EXPECT_NO_THROW(it += 2);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(it = start);
	EXPECT_NO_THROW(it += 3);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(it = start);
	EXPECT_NO_THROW(it += 4);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(it = start);
	EXPECT_NO_THROW(it += 5);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 6);

	EXPECT_NO_THROW(it = start);
	EXPECT_NO_THROW(it += 6);
	EXPECT_EQ(it, nullptr);

	EXPECT_THROW(it += 7, std::runtime_error);
}

TEST(singly_list__iterator__operators, addition_assignment_operator__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::iterator it = list.begin();

	EXPECT_EQ(it, nullptr);

	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(singly_list__iterator__operators, assignment_operator__nullptr) {
	adt::singly_list<int>::iterator it;

	it = nullptr;

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

/* ------------------------------------Node Type Constructors Tests----------------------------------------- */
TEST(singly_list__node_type__constructors, default_constructor) {
	adt::singly_list<int>::node_type node;

	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(node.value(), std::runtime_error);
}

TEST(singly_list__node_type__constructors, nullptr_constructor) {
	adt::singly_list<int>::node_type node(nullptr);

	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(node.value(), std::runtime_error);
}

TEST(singly_list__node_type__constructors, iterator_constructor__filled_list) {
	adt::singly_list<int> list = {1};
	adt::singly_list<int>::const_iterator cit = list.cbegin();
	adt::singly_list<int>::node_type node(cit);
	adt::singly_list<int>::value_type value;
	
	EXPECT_NO_THROW(value = node.value());
	EXPECT_EQ(value, 1);
}

TEST(singly_list__node_type__constructors, iterator_constructor__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator cit = list.cbegin();
	adt::singly_list<int>::node_type node(cit);
	
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(node.value(), std::runtime_error);
}

TEST(singly_list__node_type__constructors, copy_constructor__empty_list) {
	adt::singly_list<int> src, dst(src);
	adt::singly_list<int>::iterator it = dst.begin();
	adt::singly_list<int>::node_type node(it);
	
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(node.value(), std::runtime_error);
}

TEST(singly_list__node_type__constructors, copy_constructor__filled_list) {
	adt::singly_list<int> src = {1}, 
						  dst(src);
	adt::singly_list<int>::iterator it = dst.begin();
	adt::singly_list<int>::node_type node(it);
	
	EXPECT_NE(node, nullptr);
	EXPECT_EQ(node.value(), 1);
}

TEST(singly_list__node_type__constructors, move_constructor__empty_list) {
	adt::singly_list<int> src, 
						  dst = std::move(src);
	adt::singly_list<int>::iterator src_it = src.begin(),
									dst_it = dst.begin();
	adt::singly_list<int>::node_type src_node(src_it),
								     dst_node(dst_it);

	EXPECT_EQ(src_node, nullptr);
	EXPECT_THROW(src_node.value(), std::runtime_error);

	EXPECT_EQ(dst_node, nullptr);
	EXPECT_THROW(dst_node.value(), std::runtime_error);
}

TEST(singly_list__node_type__constructors, move_constructor__filled_list) {
	adt::singly_list<int> src = {1}, 
						  dst = std::move(src);
	adt::singly_list<int>::iterator src_it = src.begin(),
									dst_it = dst.begin();
	adt::singly_list<int>::node_type src_node(src_it),
								     dst_node(dst_it);
	adt::singly_list<int>::value_type value;

	EXPECT_EQ(src_node, nullptr);
	EXPECT_THROW(src_node.value(), std::runtime_error);

	EXPECT_NE(dst_node, nullptr);
	EXPECT_NO_THROW(value = dst_node.value());
	EXPECT_EQ(value, 1);
}

/* ---------------------------------------Node Type Destructor Tests----------------------------------------- */
TEST(singly_list__node_type__destructor, destructor) {
	adt::singly_list<int> list = {1};
	adt::singly_list<int>::iterator it = list.begin();
	adt::singly_list<int>::node_type node(it);

	node.~node_type();

	EXPECT_EQ(node, nullptr);

	list.~singly_list();

	EXPECT_EQ(list.cbegin(), nullptr);
}

/* ----------------------------------Node Type Overloaded Operators Tests------------------------------------ */
TEST(singly_list__node_type__operators, copy_assignment_operator__empty_list_to_empty_list) {
	adt::singly_list<int> src, dst;

	adt::singly_list<int>::iterator src_it = src.begin(), 
									dst_it = dst.begin();

	adt::singly_list<int>::node_type src_node(src_it),
									 dst_node(dst_it);
	
	EXPECT_NO_THROW(dst_node = src_node);
						
	EXPECT_EQ(src_node, nullptr);
	EXPECT_EQ(dst_node, nullptr);

	EXPECT_THROW(src_node.value(), std::runtime_error);
	EXPECT_THROW(dst_node.value(), std::runtime_error);
}

TEST(singly_list__node_type__operators, copy_assignment_operator__empty_list_to_filled_list) {
	adt::singly_list<int> src, dst = {1};

	adt::singly_list<int>::iterator src_it = src.begin(), 
									dst_it = dst.begin();
	adt::singly_list<int>::node_type src_node(src_it),
									 dst_node(dst_it);
	
	EXPECT_NO_THROW(dst_node = src_node);
	EXPECT_EQ(src_node, nullptr);
	EXPECT_EQ(dst_node, nullptr);

	EXPECT_THROW(src_node.value(), std::runtime_error);
	EXPECT_THROW(dst_node.value(), std::runtime_error);
}

TEST(singly_list__node_type__operators, copy_assignment_operator__filled_list_to_empty_list) {
	adt::singly_list<int> src = {1}, dst;

	adt::singly_list<int>::iterator src_it = src.begin(), 
									dst_it = dst.begin();
	adt::singly_list<int>::node_type src_node(src_it),
									 dst_node(dst_it);
	adt::singly_list<int>::value_type value;
	
	EXPECT_NO_THROW(dst_node = src_node);

	EXPECT_NE(src_node, nullptr);
	EXPECT_NE(dst_node, nullptr);

	EXPECT_NO_THROW(value = src_node.value());
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(value = dst_node.value());
	EXPECT_EQ(value, 1);

	EXPECT_EQ(src_node.value(), dst_node.value());
}

TEST(singly_list__node_type__operators, copy_assignment_operator__filled_list_to_filled_list) {
	adt::singly_list<int> src = {2}, dst = {1};

	adt::singly_list<int>::iterator src_it = src.begin(), 
									dst_it = dst.begin();
	adt::singly_list<int>::node_type src_node(src_it),
									 dst_node(dst_it);
	adt::singly_list<int>::value_type value;
	
	EXPECT_NO_THROW(dst_node = src_node);

	EXPECT_NE(src_node, nullptr);
	EXPECT_NE(dst_node, nullptr);

	EXPECT_NO_THROW(value = src_node.value());
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(value = dst_node.value());
	EXPECT_EQ(value, 2);

	EXPECT_EQ(src_node.value(), dst_node.value());
}

TEST(singly_list__node_type__operators, move_assignment_operator__empty_list_to_empty_list) {
	adt::singly_list<int> src, dst;

	adt::singly_list<int>::iterator src_it = src.begin(), 
									dst_it = dst.begin();

	adt::singly_list<int>::node_type src_node(src_it),
									 dst_node(dst_it);
	
	EXPECT_NO_THROW(dst_node = std::move(src_node));
						
	EXPECT_EQ(src_node, nullptr);
	EXPECT_EQ(dst_node, nullptr);

	EXPECT_THROW(src_node.value(), std::runtime_error);
	EXPECT_THROW(dst_node.value(), std::runtime_error);
}

TEST(singly_list__node_type__operators, move_assignment_operator__empty_list_to_filled_list) {
	adt::singly_list<int> src, dst = {1};

	adt::singly_list<int>::iterator src_it = src.begin(), 
									dst_it = dst.begin();
	adt::singly_list<int>::node_type src_node(src_it),
									 dst_node(dst_it);
	
	EXPECT_NO_THROW(dst_node = std::move(src_node));
	EXPECT_EQ(src_node, nullptr);
	EXPECT_EQ(dst_node, nullptr);

	EXPECT_THROW(src_node.value(), std::runtime_error);
	EXPECT_THROW(dst_node.value(), std::runtime_error);
}

TEST(singly_list__node_type__operators, move_assignment_operator__filled_list_to_empty_list) {
	adt::singly_list<int> src = {1}, dst;

	adt::singly_list<int>::iterator src_it = src.begin(), 
									dst_it = dst.begin();
	adt::singly_list<int>::node_type src_node(src_it),
									 dst_node(dst_it);
	adt::singly_list<int>::value_type value;
	
	EXPECT_NO_THROW(dst_node = std::move(src_node));

	EXPECT_EQ(src_node, nullptr);
	EXPECT_NE(dst_node, nullptr);

	EXPECT_THROW(value = src_node.value(), std::runtime_error);

	EXPECT_NO_THROW(value = dst_node.value());
	EXPECT_EQ(value, 1);
}

TEST(singly_list__node_type__operators, move_assignment_operator__filled_list_to_filled_list) {
	adt::singly_list<int> src = {2}, dst = {1};

	adt::singly_list<int>::iterator src_it = src.begin(), 
									dst_it = dst.begin();
	adt::singly_list<int>::node_type src_node(src_it),
									 dst_node(dst_it);
	adt::singly_list<int>::value_type value;
	
	EXPECT_NO_THROW(dst_node = std::move(src_node));

	EXPECT_EQ(src_node, nullptr);
	EXPECT_NE(dst_node, nullptr);

	EXPECT_THROW(value = src_node.value(), std::runtime_error);

	EXPECT_NO_THROW(value = dst_node.value());
	EXPECT_EQ(value, 2);
}

TEST(singly_list__node_type__operators, nullptr_assignment_operator__empty_list) {
	adt::singly_list<int> list;

	adt::singly_list<int>::iterator it = list.begin();

	adt::singly_list<int>::node_type node(it);
	
	EXPECT_NO_THROW(node = nullptr);
						
	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(node.value(), std::runtime_error);
}

TEST(singly_list__node_type__operators, nullptr_assignment_operator__filled_list) {
	adt::singly_list<int> list = {1};

	adt::singly_list<int>::iterator it = list.begin();
	adt::singly_list<int>::node_type node(it);
	
	EXPECT_NO_THROW(node = nullptr);

	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(node.value(), std::runtime_error);
}

TEST(singly_list__node_type__operators, iterator_assignment_operator__empty_list) {
	adt::singly_list<int> list;

	adt::singly_list<int>::iterator it = list.begin();

	adt::singly_list<int>::node_type node;
	
	EXPECT_NO_THROW(node = it);
						
	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(node.value(), std::runtime_error);
}

TEST(singly_list__node_type__operators, iterator_assignment_operator__filled_list) {
	adt::singly_list<int> list = {1, 2};

	adt::singly_list<int>::iterator it = list.begin();
	adt::singly_list<int>::node_type node(it);

	adt::singly_list<int>::value_type value;
	
	EXPECT_NO_THROW(it++);
	
	EXPECT_NO_THROW(node = it);

	EXPECT_NE(node, nullptr);

	EXPECT_NO_THROW(value = node.value());
	
	EXPECT_EQ(value, 2);
}

/* ----------------------------------------Node Type Methods Tests------------------------------------------- */
TEST(singly_list__node_type__methods, empty__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::node_type node(list.begin());

	EXPECT_EQ(node, nullptr);
	EXPECT_TRUE(node.empty() == true);
}

TEST(singly_list__node_type__methods, empty__filled_list) {
	adt::singly_list<int> list = {1};
	adt::singly_list<int>::node_type node(list.begin());

	EXPECT_NE(node, nullptr);
	EXPECT_FALSE(node.empty() == true);
}

/* -------------------------------------Singly List Constructors Tests--------------------------------------- */
TEST(singly_list__constructors, default_constructor) {
	adt::singly_list<int> list;
	adt::singly_list<int>::iterator it = list.begin();

	EXPECT_TRUE(it == nullptr);
	EXPECT_TRUE(list.empty());
	EXPECT_EQ(list.size(), 0);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(singly_list__constructors, initializer_list_constructor) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::iterator it = list.begin();
	adt::singly_list<int>::value_type value;

	EXPECT_NE(it, nullptr);
	EXPECT_FALSE(list.empty());
	EXPECT_EQ(list.size(), 3);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(it++);
	EXPECT_THROW(value = *it, std::runtime_error);

	EXPECT_THROW(it++, std::runtime_error);
}

TEST(singly_list__constructors, size_constructor) {
	adt::singly_list<int> list(3);
	adt::singly_list<int>::iterator it = list.begin();
	adt::singly_list<int>::value_type value;

	EXPECT_TRUE(it != nullptr);
	EXPECT_FALSE(list.empty());
	EXPECT_EQ(list.size(), 3);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 0);
}

TEST(singly_list__constructors, copy_constructor) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::iterator it = list.begin();

	adt::singly_list<int> list_copy(list);
	adt::singly_list<int>::iterator it_copy = list_copy.begin();

	adt::singly_list<int>::value_type value, val_copy;

	EXPECT_EQ(list.size(), list_copy.size());
	EXPECT_EQ(list.size(), 3);

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(val_copy = *it_copy);
	EXPECT_EQ(value, val_copy);
	EXPECT_EQ(val_copy, 1);
	EXPECT_NE(it, it_copy);
	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(it_copy++);

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(val_copy = *it_copy);
	EXPECT_EQ(value, val_copy);
	EXPECT_EQ(val_copy, 2);
	EXPECT_NE(it, it_copy);
	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(it_copy++);

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(val_copy = *it_copy);
	EXPECT_EQ(value, val_copy);
	EXPECT_EQ(val_copy, 3);
	EXPECT_NE(it, it_copy);
	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(it_copy++);

	EXPECT_THROW(it++, std::runtime_error);
	EXPECT_THROW(it_copy++, std::runtime_error);
}

TEST(singly_list__constructors, move_constructor) {
	adt::singly_list<int> list_src = {1, 2, 3};
	adt::singly_list<int>::iterator it_src_before = list_src.begin();

	adt::singly_list<int> list_dst = std::move(list_src);
	adt::singly_list<int>::iterator it_src_after = list_src.begin();
	adt::singly_list<int>::iterator it_dst = list_dst.begin();

	EXPECT_NE(list_src.size(), list_dst.size());
	EXPECT_EQ(list_src.size(), 0);
	EXPECT_EQ(list_dst.size(), 3);

	EXPECT_EQ(it_src_before, it_dst);
	EXPECT_EQ(it_src_after, nullptr);
	EXPECT_THROW(static_cast<void>(*it_src_after), std::runtime_error);
}

TEST(singly_list__constructors, iterator_constructor) {
	adt::singly_list<int> init_list = {1, 2, 3},
						  it_list(init_list.begin(), init_list.end());
	adt::singly_list<int>::iterator it = it_list.begin();

	adt::singly_list<int>::value_type value;

	EXPECT_TRUE(it != nullptr);
	EXPECT_FALSE(it_list.empty());
	EXPECT_EQ(it_list.size(), 3);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(it++);
	EXPECT_THROW(value = *it, std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(singly_list__constructors, range_constructor) {
	std::vector<int> vec = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int> list(std::from_range, vec);
	adt::singly_list<int>::const_iterator cit = list.cbegin();
	adt::singly_list<int>::value_type value;

	EXPECT_EQ(list.size(), 6);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);
	EXPECT_NO_THROW(cit++);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);
	EXPECT_NO_THROW(cit++);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);
	EXPECT_NO_THROW(cit++);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);
	EXPECT_NO_THROW(cit++);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);
	EXPECT_NO_THROW(cit++);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 6);
	EXPECT_NO_THROW(cit++);

	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(value = *cit, std::runtime_error);

	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__constructors, size_and_value_constructor) {
	EXPECT_THROW(adt::singly_list<int>(0, 101), std::invalid_argument);

	adt::singly_list<int> list(3, 101);
	adt::singly_list<int>::iterator it = list.begin();
	adt::singly_list<int>::value_type value;

	EXPECT_FALSE(it == nullptr);
	EXPECT_FALSE(list.empty());
	EXPECT_EQ(list.size(), 3);
	
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it++);
	EXPECT_THROW(value = *it, std::runtime_error);

	EXPECT_THROW(it++, std::runtime_error);
}

/* --------------------------------------Singly List Destructor Tests--------------------------------------- */
TEST(singly_list__destructor, destructor) {
	adt::singly_list<int> list = {1, 2, 3};
	list.~singly_list();

	adt::singly_list<int>::const_iterator cit = list.cbegin();

	EXPECT_EQ(cit, nullptr);
}

/* ---------------------------------Singly List Overloaded Operators Tests---------------------------------- */
TEST(singly_list__operators, assignment_operator__self_assignment) {
	adt::singly_list<int> list = {1, 2, 3},
						& list_ref = list;
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::value_type value;
    
    list_ref = list;
	it = list_ref.begin();

    EXPECT_TRUE(&list == &list_ref);

	EXPECT_NO_THROW(value = *it);
    EXPECT_EQ(1, value);

	EXPECT_NO_THROW(it++);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(2, value);

	EXPECT_NO_THROW(it++);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(3, value);

	EXPECT_NO_THROW(it++);
	EXPECT_THROW(value = *it, std::runtime_error);
}

TEST(singly_list__operators, assignment_operator__empty_to_empty) {
	adt::singly_list<int> src,
						  dst;
	adt::singly_list<int>::iterator src_it,
	                                dst_it;
	adt::singly_list<int>::value_type value;

	dst = src;

	dst_it = dst.begin();
	src_it = src.begin();
    
    EXPECT_TRUE(&src != &dst);
	EXPECT_EQ(src_it, dst_it);

	EXPECT_THROW(src_it++, std::runtime_error);
	EXPECT_THROW(dst_it++, std::runtime_error);

	EXPECT_THROW(value = *src_it, std::runtime_error);
	EXPECT_THROW(value = *dst_it, std::runtime_error);

	// Used to silence [-Wunused-but-set-variable] warning
	static_cast<void>(value);
}

TEST(singly_list__operators, assignment_operator__filled_to_empty) {
	adt::singly_list<int> src = {1, 2, 3},
						  dst;
	adt::singly_list<int>::iterator src_it,
	                                dst_it;
	int src_val, dst_val;

	dst = src;

	dst_it = dst.begin();
	src_it = src.begin();
    
    EXPECT_TRUE(&src != &dst);
	
	EXPECT_NO_THROW(src_val = *src_it);
	EXPECT_NO_THROW(dst_val = *dst_it);

	EXPECT_EQ(src_val, dst_val);
	EXPECT_EQ(1, dst_val);

	EXPECT_NO_THROW(src_it++);
	EXPECT_NO_THROW(dst_it++);

	EXPECT_NO_THROW(src_val = *src_it);
	EXPECT_NO_THROW(dst_val = *dst_it);
	EXPECT_EQ(src_val, dst_val);
	EXPECT_EQ(2, dst_val);

	EXPECT_NO_THROW(src_it++);
	EXPECT_NO_THROW(dst_it++);

	EXPECT_NO_THROW(src_val = *src_it);
	EXPECT_NO_THROW(dst_val = *dst_it);
	EXPECT_EQ(src_val, dst_val);
	EXPECT_EQ(3, dst_val);

	EXPECT_NO_THROW(src_it++);
	EXPECT_NO_THROW(dst_it++);

	EXPECT_THROW(src_val = *src_it, std::runtime_error);
	EXPECT_THROW(dst_val = *dst_it, std::runtime_error);

	EXPECT_THROW(src_it++, std::runtime_error);
	EXPECT_THROW(dst_it++, std::runtime_error);
}

TEST(singly_list__operators, assignment_operator__filled_to_filled) {
	adt::singly_list<int> src = {1, 2, 3},
						  dst = {4, 5, 6};
	adt::singly_list<int>::iterator src_it,
	                                dst_it;
	int src_val, dst_val;

	dst = src;

	dst_it = dst.begin();
	src_it = src.begin();
    
    EXPECT_TRUE(&src != &dst);
	
	EXPECT_NO_THROW(src_val = *src_it);

	EXPECT_NO_THROW(dst_val = *dst_it);

	EXPECT_EQ(src_val, dst_val);
	EXPECT_EQ(1, dst_val);

	EXPECT_NO_THROW(src_it++);
	EXPECT_NO_THROW(dst_it++);

	EXPECT_NO_THROW(src_val = *src_it);
	EXPECT_NO_THROW(dst_val = *dst_it);
	EXPECT_EQ(src_val, dst_val);
	EXPECT_EQ(2, dst_val);

	EXPECT_NO_THROW(src_it++);
	EXPECT_NO_THROW(dst_it++);

	EXPECT_NO_THROW(src_val = *src_it);
	EXPECT_NO_THROW(dst_val = *dst_it);
	EXPECT_EQ(src_val, dst_val);
	EXPECT_EQ(3, dst_val);

	EXPECT_NO_THROW(src_it++);
	EXPECT_NO_THROW(dst_it++);

	EXPECT_THROW(src_val = *src_it, std::runtime_error);
	EXPECT_THROW(dst_val = *dst_it, std::runtime_error);

	EXPECT_THROW(src_it++, std::runtime_error);
	EXPECT_THROW(dst_it++, std::runtime_error);
}

TEST(singly_list__operators, move_operator__empty_to_empty) {
	adt::singly_list<int> src,
						  dst;
	adt::singly_list<int>::iterator it_src,
									it_dst;
	adt::singly_list<int>::value_type value;

	dst = std::move(src);

	it_src = src.begin();
	it_dst = dst.begin();

	EXPECT_THROW(value = *it_src, std::runtime_error);
	EXPECT_THROW(value = *it_dst, std::runtime_error);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_THROW(it_dst++, std::runtime_error);

	// Used to silence [-Wunused-but-set-variable] warning
	static_cast<void>(value);
}

TEST(singly_list__operators, move_operator__empty_to_filled) {
	adt::singly_list<int> src = {1, 2, 3},
						  dst;
	adt::singly_list<int>::iterator it_src,
									it_dst;
	adt::singly_list<int>::value_type value;

	dst = std::move(src);

	it_src = src.begin();
	it_dst = dst.begin();

	EXPECT_TRUE(it_src == nullptr);

	EXPECT_THROW(value = *it_src, std::runtime_error);

	EXPECT_NO_THROW(value = *it_dst);
	EXPECT_EQ(value, 1);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_NO_THROW(it_dst++);

	EXPECT_NO_THROW(value = *it_dst);
	EXPECT_EQ(value, 2);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_NO_THROW(it_dst++);

	EXPECT_NO_THROW(value = *it_dst);
	EXPECT_EQ(value, 3);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_NO_THROW(it_dst++);

	EXPECT_THROW(value = *it_src, std::runtime_error);
	EXPECT_THROW(value = *it_dst, std::runtime_error);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_THROW(it_dst++, std::runtime_error);
}

TEST(singly_list__operators, move_operator__filled_to_filled) {
	adt::singly_list<int> src = {1, 2, 3},
						  dst = {4, 5, 6};
	adt::singly_list<int>::iterator it_src,
									it_dst;
	adt::singly_list<int>::value_type value;

	dst = std::move(src);

	it_src = src.begin();
	it_dst = dst.begin();

	EXPECT_TRUE(it_src == nullptr);

	EXPECT_THROW(value = *it_src, std::runtime_error);

	EXPECT_NO_THROW(value = *it_dst);
	EXPECT_EQ(value, 1);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_NO_THROW(it_dst++);

	EXPECT_NO_THROW(value = *it_dst);
	EXPECT_EQ(value, 2);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_NO_THROW(it_dst++);

	EXPECT_NO_THROW(value = *it_dst);
	EXPECT_EQ(value, 3);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_NO_THROW(it_dst++);

	EXPECT_THROW(value = *it_src, std::runtime_error);
	EXPECT_THROW(value = *it_dst, std::runtime_error);

	EXPECT_THROW(it_src++, std::runtime_error);
	EXPECT_THROW(it_dst++, std::runtime_error);
}

TEST(singly_list__operators, equals_operator__singly_list__both_empty) {
	adt::singly_list<int> lhs, rhs;
	
	EXPECT_TRUE(lhs.empty());
	EXPECT_TRUE(rhs.empty());
	EXPECT_NE(&lhs, &rhs);
	EXPECT_EQ(lhs, rhs);
	EXPECT_EQ(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__singly_list__same_values) {
	adt::singly_list<int> lhs = {1, 2, 3, 4}, 
						  rhs = {1, 2, 3, 4};
	
	EXPECT_NE(&lhs, &rhs);
	EXPECT_EQ(lhs, rhs);
	EXPECT_EQ(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__singly_list__different_values) {
	adt::singly_list<int> lhs = {1, 2, 3, 4}, 
						  rhs = {5, 6, 7};
	
	EXPECT_NE(&lhs, &rhs);
	EXPECT_NE(lhs, rhs);
	EXPECT_NE(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__ranges__both_empty) {
	adt::singly_list<int> lhs;
	std::initializer_list<int> rhs;
	
	EXPECT_TRUE(lhs.empty());
	EXPECT_TRUE(rhs.size() == 0);
	EXPECT_NE(static_cast<void*>(&lhs), static_cast<void*>(&rhs));
	EXPECT_EQ(lhs, rhs);
	EXPECT_EQ(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__ranges__same_values) {
	adt::singly_list<int> lhs = {1, 2, 3, 4}; 
	std::initializer_list<int> rhs = {1, 2, 3, 4};
	
	EXPECT_NE(static_cast<void*>(&lhs),static_cast<void*>(&rhs));
	EXPECT_EQ(lhs, rhs);
	EXPECT_EQ(lhs.size(), rhs.size());
}

TEST(singly_list__operators, equals_operator__ranges__different_values) {
	adt::singly_list<int> lhs = {1, 2, 3, 4};
	std::initializer_list<int> rhs = {5, 6, 7};
	
	EXPECT_NE(static_cast<void*>(&lhs), static_cast<void*>(&rhs));
	EXPECT_NE(lhs, rhs);
	EXPECT_NE(lhs.size(), rhs.size());
}

/* --------------------------------------Singly List Methods Tests------------------------------------------- */
TEST(singly_list__methods, assign__value__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {101, 101, 101, 101, 101, 101, 101, 101, 101, 101};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.assign(10, 101));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__value__count_equals_list_size) {
	adt::singly_list<int> list(5);
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {69, 69, 69, 69, 69};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(5, 69));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__value__count_greater_than_list_size) {
	adt::singly_list<int> list(5, 69);
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {101, 101, 101, 101, 101, 101, 101, 101, 101, 101};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(10, 101));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__value__count_less_than_list_size) {
	adt::singly_list<int> list(10, 101);
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {69, 69, 69, 69, 69, 101, 101, 101, 101, 101};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(list.assign(5, 69));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__empty_list_filled_container) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4};
	std::initializer_list<int> matcher = {1, 2, 3, 4};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 4);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__filled_list_empty_container) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));
	EXPECT_NO_THROW(cit = list.cbegin());

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__list_size_equals_container_size) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {5, 4, 3, 2, 1};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__list_size_greater_than_container_size) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type size;
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {5, 4, 3, 2, 1, 6, 7, 8, 9, 10};

	// Check size before calling assign()
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 10);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));

	// Check size after calling assign()
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__iterators__list_size_less_than_container_size) {
	adt::singly_list<int> list = {5, 4, 3, 2, 1};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign(vec.begin(), vec.end()));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__empty_list_empty_init_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values, matcher;

	EXPECT_NO_THROW(list.assign(values));
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__empty_list_filled_init_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values = {1, 2, 3, 4, 5},
							   matcher = {1, 2, 3, 4, 5};

	// Check size before call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	
	EXPECT_NO_THROW(list.assign(values));

	// Check size after call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__list_size_equals_init_list_size) {
	adt::singly_list<int> list = {6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values = {1, 2, 3, 4, 5},
							   matcher = {1, 2, 3, 4, 5};

	// Check size before call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);
	
	EXPECT_NO_THROW(list.assign(values));

	// Check size after call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(list.size(), 5);
	
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__list_size_greater_than_init_list_size) {
	adt::singly_list<int> list = {15, 16, 14, 13, 12, 11, 10, 9, 8, 7, 6};
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values = {1, 2, 3, 4, 5},
							   matcher = {1, 2, 3, 4, 5, 11, 10, 9, 8, 7, 6};

	// Check size before call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 11);
	
	EXPECT_NO_THROW(list.assign(values));

	// Check size after call to assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 11);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign__initializer_list__list_size_less_than_init_list_size) {
	adt::singly_list<int> list = {43, 21, 390, 4, 5000};
	adt::singly_list<int>::size_type size;
	std::initializer_list<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
							   matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	// Check size before call to assign()
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 5);
	
	EXPECT_NO_THROW(list.assign(values));

	// Check size after call to assign()
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 11);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign_range__empty_list_empty_container) {
	std::vector<int> vec;
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator cit;
	
	EXPECT_NO_THROW(list.assign_range(vec));
	EXPECT_NO_THROW(cit = list.cbegin());

	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__methods, assign_range__empty_list_filled_container) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	// Check size before call to assign_range()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.assign_range(vec));

	// Check size after call to assign_range()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign_range__list_size_equals_container_size) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {5, 4, 3, 2, 1};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign_range(vec));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign_range__list_size_greater_than_container_size) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {5, 4, 3, 2, 1, 6, 7, 8, 9, 10};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(list.assign_range(vec));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, assign_range__list_size_less_than_container_size) {
	adt::singly_list<int> list = {5, 4, 3, 2, 1};
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// Check size before calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.assign_range(vec));

	// Check size after calling assign()
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, front__empty) {
	adt::singly_list<int> list;

	EXPECT_THROW(static_cast<void>(list.front()), std::runtime_error);
}

TEST(singly_list__methods, front__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.front());
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, back__empty) {
	adt::singly_list<int> list;

	EXPECT_THROW(static_cast<void>(list.back()), std::runtime_error);
}

TEST(singly_list__methods, back__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.back());
	EXPECT_EQ(value, 3);
}

TEST(singly_list__methods, resize__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(list.resize(0));
	EXPECT_TRUE(list.empty() == true);
	EXPECT_THROW(value = *list.cbegin(), std::runtime_error);

	EXPECT_NO_THROW(list.resize(1));
	EXPECT_TRUE(list.size() == 1);
	EXPECT_NO_THROW(value = *list.cbegin());
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(list.resize(10));
	EXPECT_TRUE(list.size() == 10);
	EXPECT_TRUE(*(list.cbegin() + 9) == 0);
}

TEST(singly_list__methods, resize__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::size_type size;
	adt::singly_list<int>::value_type value;

	// Test 0
	EXPECT_NO_THROW(list.resize(4));

	cit = list.cbegin();
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 4);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 0);


	// Test 1
	EXPECT_NO_THROW(list.resize(5));

	cit = list.cbegin();
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 5);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(cit++);
	EXPECT_THROW(value = *cit, std::runtime_error);
	

	// Test 2
	EXPECT_NO_THROW(list.resize(4));

	cit = list.cbegin();
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 4);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(cit++);
	EXPECT_THROW(value = *cit, std::runtime_error);


	// Test 3
	EXPECT_NO_THROW(list.resize(0));

	cit = list.cbegin();
	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 0);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(singly_list__methods, remove__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type vals_removed;

	EXPECT_NO_THROW(vals_removed = list.remove(101));
	EXPECT_EQ(vals_removed, 0);
}

TEST(singly_list__methods, remove__single) {
	adt::singly_list<int> list = {1};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;
	adt::singly_list<int>::size_type size, vals_removed;

	EXPECT_NO_THROW(vals_removed = list.remove(1));
	EXPECT_EQ(vals_removed, 1);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 0);

	EXPECT_NO_THROW(cit = list.cbegin());
	EXPECT_TRUE(cit == nullptr);
	EXPECT_THROW(value = *cit, std::runtime_error);

	static_cast<void>(value);
}

TEST(singly_list__methods, remove__consecutive__front) {
	adt::singly_list<int> list = {1, 1, 1, 1, 1, 2, 3, 4, 5};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {2, 3, 4, 5};

	EXPECT_NO_THROW(vals_removed = list.remove(1));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 4);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove__consecutive__back) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 5, 5, 5, 5, 5};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {1, 2, 3, 4};

	EXPECT_NO_THROW(vals_removed = list.remove(5));
	EXPECT_EQ(vals_removed, 6);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 4);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove__every_other) {
	adt::singly_list<int> list = {1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 4, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 10};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {2, 3, 3, 3, 3, 3, 4, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 10};

	// Removing all 1's
	EXPECT_NO_THROW(vals_removed = list.remove(1));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 25);

	EXPECT_EQ(list, matcher);

	// Removing all 3's
	matcher = {2, 4, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 10};
	EXPECT_NO_THROW(vals_removed = list.remove(3));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 20);

	EXPECT_EQ(list, matcher);

	// Removing all 5's
	matcher = {2, 4, 6, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 10};
	EXPECT_NO_THROW(vals_removed = list.remove(5));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 15);

	EXPECT_EQ(list, matcher);

	// Removing all 7's
	matcher = {2, 4, 6, 8, 9, 9, 9, 9, 9, 10};
	EXPECT_NO_THROW(vals_removed = list.remove(7));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 10);

	EXPECT_EQ(list, matcher);

	// Removing all 9's
	matcher = {2, 4, 6, 8, 10};
	EXPECT_NO_THROW(vals_removed = list.remove(9));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove_if__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type vals_removed;

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));
	EXPECT_EQ(vals_removed, 0);
}

TEST(singly_list__methods, remove_if__single) {
	adt::singly_list<int> list = {2};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;
	adt::singly_list<int>::size_type size, vals_removed;

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));

	EXPECT_EQ(vals_removed, 1);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 0);

	EXPECT_NO_THROW(cit = list.cbegin());
	EXPECT_TRUE(cit == nullptr);
	EXPECT_THROW(value = *cit, std::runtime_error);

	static_cast<void>(value);
}

TEST(singly_list__methods, remove_if__consecutive__front) {
	adt::singly_list<int> list = {2, 2, 2, 2, 2, 3};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {3};

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 1);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove_if__consecutive__back) {
	adt::singly_list<int> list = {5, 6, 6, 6, 6, 6};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {5};

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));
	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 1);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, remove_if__every_other) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type size, vals_removed;
	std::initializer_list<int> matcher = {1, 3, 5, 7, 9};

	EXPECT_NO_THROW(vals_removed = list.remove_if([](adt::singly_list<int>::value_type value) -> bool {
		return value % 2 == 0;
	}));

	EXPECT_EQ(vals_removed, 5);

	EXPECT_NO_THROW(size = list.size());
	EXPECT_EQ(size, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, clear) {
	adt::singly_list<int> list;

	EXPECT_NO_THROW(list.clear());

	list = {1, 2, 3};
	EXPECT_NO_THROW(list.clear());
	EXPECT_TRUE(list.cbegin() == nullptr);
	EXPECT_TRUE(list.empty() == true);
}

TEST(singly_list__methods, insert_after__lref__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::value_type value = 101;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, value), std::runtime_error);
}

TEST(singly_list__methods, insert_after__lref__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::value_type lvalue = 101;

	EXPECT_THROW(list.insert_after(pos, lvalue), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__lref__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		EXPECT_NO_THROW(it = list.insert_after(pos, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos++);
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__lref__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		EXPECT_NO_THROW(it = list.insert_after(pos, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 2);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__rref__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::value_type value = 101;
	adt::singly_list<int>::reference& value_ref = value;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, value_ref), std::runtime_error);
}

TEST(singly_list__methods, insert_after__rref__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::value_type value = 101;
	adt::singly_list<int>::reference& value_ref = value;

	EXPECT_THROW(list.insert_after(pos, value_ref), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__rref__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		adt::singly_list<int>::reference& i_ref = i;
		EXPECT_NO_THROW(it = list.insert_after(pos, i_ref));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos++);
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__rref__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		adt::singly_list<int>::reference& i_ref = i;
		EXPECT_NO_THROW(it = list.insert_after(pos, i_ref));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 2);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, matcher.size());

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__lref_and_count__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::value_type value = 101;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, 3, value), std::runtime_error);
}

TEST(singly_list__methods, insert_after__lref_and_count__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::value_type value = 101;

	EXPECT_THROW(list.insert_after(pos, 3, value), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__lref_and_count__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		EXPECT_NO_THROW(it = list.insert_after(pos, 3, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 3);
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__lref_and_count__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9, 9, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		EXPECT_NO_THROW(it = list.insert_after(pos, 3, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 4);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, matcher.size());

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__iterators__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	std::vector<int> vec = {1, 2, 3};

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, vec.cbegin(), vec.cend()), std::runtime_error);
}

TEST(singly_list__methods, insert_after__iterators__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	std::vector<int> vec = {1, 2, 3};

	EXPECT_THROW(list.insert_after(pos, vec.cbegin(), vec.cend()), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__iterators__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		EXPECT_NO_THROW(it = list.insert_after(pos, 3, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 3);
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__iterators__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9, 9, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		EXPECT_NO_THROW(it = list.insert_after(pos, 3, i));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 4);
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, matcher.size());

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__initializer_list__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	std::initializer_list<int> values = {1, 2, 3, 4, 5};

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_after(pos, values), std::runtime_error);
}

TEST(singly_list__methods, insert_after__initializer_list__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	std::initializer_list<int> values = {1, 2, 3, 4, 5};

	EXPECT_THROW(list.insert_after(pos, values), std::invalid_argument);
}

TEST(singly_list__methods, insert_after__initializer_list__front) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> values = {1, 2, 3, 4, 5},
							   matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	EXPECT_NO_THROW(it = list.insert_after(pos, values));
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(*it, 5);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, insert_after__initializer_list__in_between) {
	adt::singly_list<int> list = {1, 10};
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {2, 3, 4, 5, 6, 7, 8, 9};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 2);

	EXPECT_NO_THROW(it = list.insert_range_after(pos, values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
	EXPECT_EQ(*it, 9);
}

TEST(singly_list__methods, insert_range_after__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	std::vector<int> vec = {1, 2, 3, 4};

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.insert_range_after(pos, vec), std::runtime_error);
}

TEST(singly_list__methods, insert_range_after__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	std::vector<int> vec = {1, 2, 3, 4};

	EXPECT_THROW(list.insert_range_after(pos, vec), std::invalid_argument);
}

TEST(singly_list__methods, insert_range_after__front) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	std::vector<int> vec = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	EXPECT_NO_THROW(it = list.insert_range_after(pos, vec));
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(*it, 5);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, emplace_after__segmentation_fault) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_THROW(list.emplace_after(pos, std::forward<int>(101)), std::runtime_error);
}

TEST(singly_list__methods, emplace_after__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	std::vector<int> vec = {1, 2, 3, 4};

	EXPECT_THROW(list.insert_range_after(pos, vec), std::invalid_argument);
}

TEST(singly_list__methods, emplace_after__consecutive) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 1; i <= 5; i++) {
		EXPECT_NO_THROW(it = list.emplace_after(pos, std::forward<int>(i)));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos++);
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, emplace_after__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	for (adt::singly_list<int>::value_type i = 1; i < 10; i += 2) {
		EXPECT_NO_THROW(it = list.emplace_after(pos, std::forward<int>(i)));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i);
		EXPECT_NO_THROW(pos += 2);
	}

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, erase_after__single_iterator__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.erase_after(pos), std::runtime_error);

	list = {1};
	pos = list.cbegin();

	EXPECT_NE(pos, nullptr);
	EXPECT_EQ(pos + 1, nullptr);
	EXPECT_THROW(list.erase_after(pos), std::runtime_error);
}

TEST(singly_list__methods, erase_after__single_iterator__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other = {101};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();

	EXPECT_THROW(list.erase_after(pos), std::invalid_argument);
}

TEST(singly_list__methods, erase_after__single_iterator__consecutive) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher;

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);
	EXPECT_NE(pos, nullptr);

	for (adt::singly_list<int>::value_type i = 0; i < 4; i++) {
		EXPECT_NO_THROW(it = list.erase_after(pos));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i + 2);
	}

	EXPECT_NO_THROW(it = list.erase_after(pos));
	EXPECT_EQ(it, nullptr);
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, erase_after__single_iterator__every_other) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {2, 4, 6, 8, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	adt::singly_list<int>::value_type j = 2;
	for (adt::singly_list<int>::value_type i = 0; i < 5; i++) {
		EXPECT_NO_THROW(it = list.erase_after(pos));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, j);
		EXPECT_NO_THROW(pos++);
		j += 2;
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);
	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, erase_after__iterator_range__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator first = list.cbegin(),
										  last = list.cend();

	EXPECT_EQ(first, nullptr);
	EXPECT_THROW(list.erase_after(first, last), std::runtime_error);
}

TEST(singly_list__methods, erase_after__iterator_range__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other = {101};

	adt::singly_list<int>::const_iterator first = other.cbefore_begin();
	adt::singly_list<int>::const_iterator last = other.cend();

	EXPECT_THROW(list.erase_after(first, last), std::invalid_argument);
}

TEST(singly_list__methods, erase_after__iterator_range__consecutive) {
	adt::singly_list<int> list = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	for (adt::singly_list<int>::value_type i = 0; i < 5; i++) {
		EXPECT_NO_THROW(it = list.erase_after(pos, pos + 3));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, i + 1);
		EXPECT_NO_THROW(pos++);
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, erase_after__iterator_range__every_other) {
	adt::singly_list<int> list = {1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9, 9, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::size_type sz;
	adt::singly_list<int>::value_type value;
	std::initializer_list<int> matcher = {2, 4, 6, 8, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 20);

	adt::singly_list<int>::value_type j = 2;
	for (adt::singly_list<int>::value_type i = 0; i < 5; i++) {
		EXPECT_NO_THROW(it = list.erase_after(pos, pos + 4));
		EXPECT_NO_THROW(value = *it);
		EXPECT_EQ(value, j);
		EXPECT_NO_THROW(pos++);
		j += 2;
	}

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, splice_after__lref__segmentation_fault) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, other), std::runtime_error);
}

TEST(singly_list__methods, splice_after__lref__different_instance) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();

	EXPECT_THROW(list.splice_after(pos, other), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__lref__same_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.before_begin();

	EXPECT_NE(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, list), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__lref__empty_other) {
	adt::singly_list<int> list = {1, 2, 3}, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::size_type sz;

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NE(pos, nullptr);
	EXPECT_NO_THROW(list.splice_after(pos, other));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);
}

TEST(singly_list__methods, splice_after__lref__filled_other) {
	adt::singly_list<int> list = {1, 2, 3},
						  other = {4, 5, 6};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_NE(pos, nullptr);

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(list.splice_after(pos, other));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 6);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, matcher);
	EXPECT_EQ(other.cbegin(), nullptr);
}

TEST(singly_list__methods, splice_after__rref__segmentation_fault) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other)), std::runtime_error);
}

TEST(singly_list__methods, splice_after__rref__different_instance) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();

	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other)), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__rref__same_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.before_begin();

	EXPECT_NE(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(list)), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__rref__empty_other) {
	adt::singly_list<int> list = {1, 2, 3}, 
						  other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::size_type sz;

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NE(pos, nullptr);
	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other)));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);
}

TEST(singly_list__methods, splice_after__rref__filled_other) {
	adt::singly_list<int> list = {1, 2, 3},
						  other = {4, 5, 6};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_NE(pos, nullptr);

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 3);

	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other)));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 6);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, matcher);
	EXPECT_EQ(other.cbegin(), nullptr);
}

TEST(singly_list__methods, splice_after__lref_and_iterator__segmentation_fault) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::iterator it;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, other, it), std::runtime_error);
}

TEST(singly_list__methods, splice_after__lref_and_iterator__different_instance) {
	adt::singly_list<int> list;
	adt::singly_list<int> other = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::iterator it = other.begin();

	EXPECT_THROW(list.splice_after(pos, other, it), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__lref_and_iterator__consecutive) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5},
						  other = {6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 4;
	adt::singly_list<int>::iterator it = other.before_begin();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
							   other_matcher = {};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 5);

	for (std::size_t i = 0; i < 5; i++) {
		EXPECT_NO_THROW(list.splice_after(pos, other, it));
		pos++;
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__lref_and_iterator__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10},
						  other = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it = other.before_begin();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
							   other_matcher = {2, 4, 6, 8, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 10);

	for (std::size_t i = 0; i < 5; i++) {
		EXPECT_NO_THROW(list.splice_after(pos, other, it));
		pos += 2;
		it++;
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__rref_and_iterator__segmentation_fault) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::iterator it;

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), it), std::runtime_error);
}

TEST(singly_list__methods, splice_after__rref_and_iterator__different_instance) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::iterator it = other.begin();

	EXPECT_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), it), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__rref_and_iterator__consecutive) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5},
						  other = {6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 4;
	adt::singly_list<int>::iterator it = other.before_begin();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
							   other_matcher = {};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 5);

	for (std::size_t i = 0; i < 5; i++) {
		EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), it));
		pos++;
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__rref_and_iterator__every_other) {
	adt::singly_list<int> list = {2, 4, 6, 8, 10},
						  other = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::iterator it = other.before_begin();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
							   other_matcher = {2, 4, 6, 8, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 10);

	for (std::size_t i = 0; i < 5; i++) {
		EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), it));
		pos += 2;
		it++;
	}
	
	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__lref_and_iterator_range__segmentation_fault) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = list.cbegin(),
										  first = other.cbegin(),
										  last = other.cend();
	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, other, first, last), std::runtime_error);
}

TEST(singly_list__methods, splice_after__lref_and_iterator_range__different_instance) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();
	adt::singly_list<int>::const_iterator first = other.cbegin();
	adt::singly_list<int>::const_iterator last = other.cend();

	EXPECT_THROW(list.splice_after(pos, other, first, last), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__lref_and_iterator_range__consecutive) {
	adt::singly_list<int> list, other = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin(),
										  first = other.cbefore_begin(),
										  last = other.cend();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5},
							   other_matcher = {};
							
	EXPECT_NO_THROW(list.splice_after(pos, other, first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);
	
	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__lref_and_iterator_range__every_other) {
	adt::singly_list<int> list = {1, 2, 3, 7, 8, 9, 13, 14, 15},
						  other = {4, 5, 6, 10, 11, 12};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2,
										  first = other.cbefore_begin(),
										  last = first + 4;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14, 15},
							   other_matcher = {10, 11, 12};

	EXPECT_NO_THROW(list.splice_after(pos, other, first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 12);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 3);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);

	list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	other_matcher = {};
	pos += 6;
	first = other.cbefore_begin();
	last = first + 4;

	EXPECT_NO_THROW(list.splice_after(pos, other, first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);

}

TEST(singly_list__methods, splice_after__rref_and_iterator_range__segmentation_fault) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = list.cbegin(),
										  first = other.cbegin(),
										  last = other.cend();
	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.splice_after(pos, other, first, last), std::runtime_error);
}

TEST(singly_list__methods, splice_after__rref_and_iterator_range__different_instance) {
	adt::singly_list<int> list, other = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin(),
										  first = other.cbegin(),
										  last = other.cend();

	EXPECT_THROW(list.splice_after(pos, other, first, last), std::invalid_argument);
}

TEST(singly_list__methods, splice_after__rref_and_iterator_range__consecutive) {
	adt::singly_list<int> list, other = {1, 2, 3, 4, 5};
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin(),
										  first = other.cbefore_begin(),
										  last = other.cend();
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5},
							   other_matcher = {};
							
	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);
	
	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);
}

TEST(singly_list__methods, splice_after__rref_and_iterator_range__every_other) {
	adt::singly_list<int> list = {1, 2, 3, 7, 8, 9, 13, 14, 15},
						  other = {4, 5, 6, 10, 11, 12};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2,
										  first = other.cbefore_begin(),
										  last = first + 4;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14, 15},
							   other_matcher = {10, 11, 12};

	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 12);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 3);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);

	list_matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	other_matcher = {};
	pos += 6;
	first = other.cbefore_begin();
	last = first + 4;

	EXPECT_NO_THROW(list.splice_after(pos, std::forward<adt::singly_list<int>>(other), first, last));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 15);

	EXPECT_NO_THROW(sz = other.size());
	EXPECT_EQ(sz, 0);

	EXPECT_EQ(list, list_matcher);
	EXPECT_EQ(other, other_matcher);

}

TEST(singly_list__methods, push_back__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	list.push_back(1);
	EXPECT_NO_THROW(value = *list.begin());

	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, push_back__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	list.push_back(4);
	EXPECT_NO_THROW(value = *(list.begin() + 3));

	EXPECT_TRUE(list.size() == 4);
	EXPECT_EQ(value, 4);
}

TEST(singly_list__methods, push_front__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	list.push_front(0);
	EXPECT_NO_THROW(value = *list.begin());

	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, push_front__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::value_type value;

	list.push_front(-1);
	it = list.begin();

	EXPECT_TRUE(list.size() == 4);

	EXPECT_NO_THROW(value = *it);

	EXPECT_EQ(value, -1);

	EXPECT_NO_THROW(it++);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, pop_back__empty) {
	adt::singly_list<int> list;

	EXPECT_THROW(list.pop_back(), std::runtime_error);
}

TEST(singly_list__methods, pop_back__filled__single) {
	adt::singly_list<int> list(1, -1);
	adt::singly_list<int>::iterator it;

	EXPECT_NO_THROW(list.pop_back());

	it = list.begin();
	EXPECT_TRUE(list.size() == 0);

	EXPECT_TRUE(it == nullptr);
}

TEST(singly_list__methods, pop_back__filled__multiple) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(list.pop_back());

	it = list.begin();

	EXPECT_TRUE(list.size() == 2);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(1, value);
	EXPECT_NO_THROW(it++);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(2, value);
	EXPECT_NO_THROW(it++);

	EXPECT_TRUE(it == nullptr);
}

TEST(singly_list__methods, pop_front__empty) {
	adt::singly_list<int> list;
	
	EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST(singly_list__methods, pop_front__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::iterator it;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(list.pop_front());

	it = list.begin();

	EXPECT_TRUE(list.size() == 2);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(2, value);
	EXPECT_NO_THROW(it++);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(3, value);
	EXPECT_NO_THROW(it++);

	EXPECT_TRUE(it == nullptr);
}

TEST(singly_list__methods, emplace_back__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.emplace_back(0));

	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, emplace_back__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	value = list.emplace_back(4);

	EXPECT_TRUE(list.size() == 4);

	EXPECT_EQ(value, 4);

	
	value = list.emplace_back(5);

	EXPECT_TRUE(list.size() == 5);

	EXPECT_EQ(value, 5);
}

TEST(singly_list__methods, emplace_front__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.emplace_front(0));

	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, emplace_front__filled) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::value_type value;

	EXPECT_NO_THROW(value = list.emplace_front(0));

	EXPECT_TRUE(list.size() == 4);
	EXPECT_EQ(value, 0);

	EXPECT_NO_THROW(value = list.emplace_front(-1));
	EXPECT_TRUE(list.size() == 5);
	EXPECT_EQ(value, -1);
}

TEST(singly_list__methods, prepend_range__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.prepend_range(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, prepend_range__filled) {
	adt::singly_list<int> list = {6, 7, 8, 9, 10};
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.prepend_range(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, append_range__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 0);

	EXPECT_NO_THROW(list.append_range(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, append_range__filled) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5};
	adt::singly_list<int>::size_type sz;
	std::vector<int> values = {6, 7, 8, 9, 10};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 5);

	EXPECT_NO_THROW(list.append_range(values));

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 10);

	EXPECT_EQ(list, matcher);
}

TEST(singly_list__methods, swap) {
	adt::singly_list<int> list1 = {1, 2, 3},
						  list2 = {4, 5, 6};
	adt::singly_list<int>::value_type value;

	list1.swap(list2);

	EXPECT_NO_THROW(value = list1.front());
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(value = list2.front());
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, reverse__empty) {
	adt::singly_list<int> list;
	list.reverse();

	EXPECT_TRUE(list.cbegin() == nullptr);
}

TEST(singly_list__methods, reverse__filled__single) {
	adt::singly_list<int> list(1, 1);
	adt::singly_list<int>::const_iterator cit = list.cbegin();

	list.reverse();

	EXPECT_TRUE(*cit == 1);
	EXPECT_THROW(static_cast<void>(*(cit + 1)), std::runtime_error);
}

TEST(singly_list__methods, reverse__filled__multiple) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;

	list.reverse();

	EXPECT_NO_THROW(cit = list.cbegin());
	
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 6);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, unique__empty) {
	adt::singly_list<int> list;
	adt::singly_list<int>::value_type value = list.unique();

	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, unique__filled__single) {
	adt::singly_list<int> list(1, 1);
	adt::singly_list<int>::value_type value = list.unique();

	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, unique__filled__all_unique) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6};
	adt::singly_list<int>::value_type value = list.unique();

	EXPECT_EQ(value, 0);
}

TEST(singly_list__methods, unique__filled__all_dups) {
	adt::singly_list<int> list = {1, 1, 1, 1, 1, 1};
	adt::singly_list<int>::value_type value = list.unique();

	EXPECT_EQ(value, 5);
	EXPECT_NO_THROW(value = *list.cbegin());
	EXPECT_EQ(value, 1);
	EXPECT_TRUE(list.size() == 1);
}

TEST(singly_list__methods, unique__filled__mixed) {
	adt::singly_list<int> list = {1, 2, 2, 3, 4, 5, 5, 5, 6};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;

	EXPECT_EQ(list.unique(), 3);

	cit = list.cbegin();

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);

	EXPECT_NO_THROW(cit++);
	EXPECT_THROW(value = *cit, std::runtime_error);

	EXPECT_EQ(list.size(), 6);
}

TEST(singly_list__methods, sort__accending_order) {
	adt::singly_list<int> list = {1, 3, 6, 2, 5, 4};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;

	// void sort()
	list.sort();
	cit = list.cbegin();

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 6);
}

TEST(singly_list__methods, sort__decending_order) {
	adt::singly_list<int> list = {1, 3, 6, 2, 5, 4};
	adt::singly_list<int>::const_iterator cit;
	adt::singly_list<int>::value_type value;

	// template<class Compare>
	// void sort(Compare comp)
	list.sort(std::greater<int>{});
	cit = list.cbegin();

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 6);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 5);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 4);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 3);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 2);

	EXPECT_NO_THROW(cit++);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);
}

TEST(singly_list__methods, is_sorted__no_argument__empty_list) {
	adt::singly_list<int> list;
	EXPECT_FALSE(list.is_sorted());
}

TEST(singly_list__methods, is_sorted__no_argument__unsorted_list) {
	adt::singly_list<int> list = {1, 5, 3, 7, 9, 100, 69, 101, 2};
	EXPECT_FALSE(list.is_sorted());
}

TEST(singly_list__methods, is_sorted__no_argument__sorted_list) {
	adt::singly_list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	EXPECT_TRUE(list.is_sorted());
}

TEST(singly_list__methods, is_sorted__argument__empty_list) {
	adt::singly_list<int> list;
	EXPECT_FALSE(list.is_sorted(std::greater<adt::singly_list<int>::value_type>{}));
}

TEST(singly_list__methods, is_sorted__argument__unsorted_list) {
	adt::singly_list<int> list = {1, 5, 3, 7, 9, 100, 69, 101, 2};
	EXPECT_FALSE(list.is_sorted(std::greater<adt::singly_list<int>::value_type>{}));
}

TEST(singly_list__methods, is_sorted__argument__sorted_list) {
	adt::singly_list<int> list = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	EXPECT_TRUE(list.is_sorted(std::greater<adt::singly_list<int>::value_type>{}));
}

TEST(singly_list__methods, extract_after__iterator__segmentation_fault) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbegin();

	EXPECT_EQ(pos, nullptr);
	EXPECT_THROW(list.extract_after(pos), std::runtime_error);
} 

TEST(singly_list__methods, extract_after__iterator__invalid_iterator) {
	adt::singly_list<int> list, other;
	adt::singly_list<int>::const_iterator pos = other.cbefore_begin();

	EXPECT_NE(pos, nullptr);
	EXPECT_THROW(list.extract_after(pos), std::invalid_argument);
} 

TEST(singly_list__methods, extract_after__iterator__empty_list) {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	adt::singly_list<int>::node_type node_handle;

	EXPECT_NE(pos, nullptr);
	EXPECT_NO_THROW(node_handle = list.extract_after(pos));

	EXPECT_TRUE(node_handle.empty());
	EXPECT_EQ(node_handle, nullptr);
	
	EXPECT_THROW(node_handle.value(), std::runtime_error);
}

TEST(singly_list__methods, extract_after__iterator__filled_list) {
	adt::singly_list<int> list = {1, 2, 3};
	adt::singly_list<int>::const_iterator pos = list.cbegin();
	adt::singly_list<int>::node_type node_handle;
	adt::singly_list<int>::size_type sz;
	std::initializer_list<int> matcher = {1, 3};

	EXPECT_NE(pos, nullptr);
	EXPECT_NO_THROW(node_handle = list.extract_after(pos));

	EXPECT_FALSE(node_handle.empty());
	EXPECT_NE(node_handle, nullptr);
	
	EXPECT_EQ(node_handle.value(), 2);

	EXPECT_NO_THROW(sz = list.size());
	EXPECT_EQ(sz, 2);
	EXPECT_EQ(list, matcher);
}
