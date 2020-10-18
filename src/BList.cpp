/**
* @file      BList.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the BList class.
*/

#include "BList.h"

#include <cassert>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "BItemVisitor.h"

namespace bencoding {

/**
* @brief Constructs an empty list.
*/
BList::BList() = default;

/**
* @brief Constructs a list containing the given @a items.
*/
BList::BList(std::vector<value_type> items):
	itemList(items) {}

/**
* @brief Creates and returns a new list.
*/
std::shared_ptr<BList> BList::create() {
	return std::shared_ptr<BList>(new BList());
}

/**
* @brief Creates a returns a new list containing the given @a items.
*/
std::shared_ptr<BList> BList::create(std::vector<value_type> items) {
	return std::shared_ptr<BList>(new BList(items));
}

BList::BItemList &BList::value(){
    return this->itemList;
}

void BList::clear() {
    itemList.clear();
}

/**
* @brief Returns the number of items in the list.
*/
BList::size_type BList::size() const {
	return itemList.size();
}

/**
* @brief Checks if the list is empty.
*
* @return @c true if the list is empty, @c false otherwise.
*/
bool BList::empty() const {
	return itemList.empty();
}

/**
* @brief Appends the given item to the end of the list.
*
* @preconditions
*  - @a bItem is non-null
*/
void BList::push_back(const value_type &bItem) {
	assert(bItem && "cannot add a null item to the list");

	itemList.push_back(bItem);
}

/**
* @brief Removes the last element of the list.
*
* References and iterators to the erased element are invalidated.
*
* @preconditions
*  - list is non-empty
*/
void BList::pop_back() {
	assert(!empty() && "cannot call pop_back() on an empty list");

	itemList.pop_back();
}

/**
* @brief Returns a reference to the first item in the list.
*
* @preconditions
*  - list is non-empty
*/
BList::reference BList::front() {
	assert(!empty() && "cannot call front() on an empty list");

	return itemList.front();
}

BList::reference &BList::operator[](size_t idx) {
    assert(itemList.size() > idx && "cannot call front() on an empty list");

    return itemList[idx];
}

void BList::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(itemList.begin(), itemList.end(), e);
}

// BList &BList::extend(const BList &list_b) {
//     this->itemList.reserve(this->size() + std::distance(list_b.begin(), list_b.end()));
//     this->itemList.insert(this->end(), list_b.begin(), list_b.end());
//     return *this;
// }

void BList::extend(BListPtr list_b) {
    this->itemList.reserve(this->size() + std::distance(list_b->begin(), list_b->end()));
    this->itemList.insert(this->end(), list_b->begin(), list_b->end());
}

void BList::range_erase(int s_idx) {
    this->range_erase(s_idx, this->size());
}

void BList::range_erase(int s_idx, int e_idx) {
    if (this->size() == 0) {
        return ;
    }

    if (s_idx < 0) {
        s_idx = this->size() + s_idx;
    }
    if (e_idx < 0) {
        e_idx = this->size() + e_idx;
    }

    int count = e_idx - s_idx;

    for (int i = 0; i < count; i++)
        this->itemList.erase(this->itemList.begin() + s_idx);
}

std::shared_ptr<BList> BList::range(int s_idx) {
    return this->range(s_idx, this->size());
}
std::shared_ptr<BList> BList::range(int s_idx, int e_idx) {
    if (this->size() == 0) {
        return BList::create();
    }

    if (s_idx < 0) {
        s_idx = this->size() + s_idx;
    }
    if (e_idx < 0) {
        e_idx = this->size() + e_idx;
    }

    assert(s_idx <= static_cast<int>(this->size()));
    assert(s_idx <= e_idx);

    auto newList = BList::create(std::vector<value_type>(this->begin() + s_idx, this->begin() + e_idx));
    return newList;
}

/**
* @brief Returns a constant reference to the first item in the list.
*
* @preconditions
*  - list is non-empty
*/
BList::const_reference BList::front() const {
	assert(!empty() && "cannot call front() on an empty list");

	return itemList.front();
}

/**
* @brief Returns a reference to the last item in the list.
*
* @preconditions
*  - list is non-empty
*/
BList::reference BList::back() {
	assert(!empty() && "cannot call back() on an empty list");

	return itemList.back();
}

/**
* @brief Returns a constant reference to the last item in the list.
*
* @preconditions
*  - list is non-empty
*/
BList::const_reference BList::back() const {
	assert(!empty() && "cannot call back() on an empty list");

	return itemList.back();
}

/**
* @brief Returns an iterator to the beginning of the list.
*/
BList::iterator BList::begin() {
	return itemList.begin();
}

/**
* @brief Returns an iterator to the end of the list.
*/
BList::iterator BList::end() {
	return itemList.end();
}

/**
* @brief Returns a constant iterator to the beginning of the list.
*/
BList::const_iterator BList::begin() const {
	return itemList.begin();
}

/**
* @brief Returns a constant iterator to the end of the list.
*/
BList::const_iterator BList::end() const {
	return itemList.end();
}

/**
* @brief Returns a constant iterator to the beginning of the list.
*/
BList::const_iterator BList::cbegin() const {
	return itemList.cbegin();
}

/**
* @brief Returns a constant iterator to the end of the list.
*/
BList::const_iterator BList::cend() const {
	return itemList.cend();
}

void BList::accept(BItemVisitor *visitor) {
	visitor->visit(this);
}

} // namespace bencoding
