/**
* @file      BList.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Representation of a list.
*/

#ifndef BENCODING_BLIST_H
#define BENCODING_BLIST_H

#include <initializer_list>
#include <list>
#include <memory>
#include <vector>

#include "BItem.h"

namespace bencoding {

/**
* @brief Representation of a list.
*
* The interface models the interface of @c std::list.
*
* Use create() to create instances of the class.
*/
class BList: public BItem {
private:
	/// List of items.
	using BItemList = std::vector<std::shared_ptr<BItem>>;

public:

	/// Value type.
	using value_type = BItemList::value_type;

	/// Size type.
	using size_type = BItemList::size_type;

	/// Reference.
	using reference = BItemList::reference;

	/// Constant reference.
	using const_reference = BItemList::const_reference;

	/// Iterator (@c BidirectionalIterator).
	using iterator = BItemList::iterator;

	/// Constant iterator (constant @c BidirectionalIterator).
	using const_iterator = BItemList::const_iterator;

public:
	static std::unique_ptr<BList> create();
	static std::unique_ptr<BList> create(std::vector<value_type> items);
    BItemList &value();

    BList::reference &operator[](size_t idx);

	/// @name Capacity
	/// @{
	size_type size() const;
	bool empty() const;
	void clear();
	/// @}

	/// @name Modifiers
	/// @{
	void push_back(const value_type &bItem);
	void pop_back();
    void shuffle();
    // BList &extend(const BList &list_b);
    void extend(std::shared_ptr<BList> list_b);

	template <typename T >
    std::shared_ptr<T> getItem(size_t idx) {
        return (*this)[idx]->as<T>();
    }

    void setItem(size_t idx, BItemPtr item) {
        assert(idx <= this->size());
        (*this)[idx] = item;
    }

    std::shared_ptr<BList> range(int s_idx);
    std::shared_ptr<BList> range(int s_idx, int e_idx);

	/// @}

	/// @name Element Access
	/// @{
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;
	/// @}

	/// @name Iterators
	/// @{
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	/// @}

	/// @name BItemVisitor Support
	/// @{
	virtual void accept(BItemVisitor *visitor) override;
	/// @}

private:
	BList();
	explicit BList(std::vector<value_type> items);

private:
	/// Underlying list of items.
	BItemList itemList;
};

using BListPtr = std::shared_ptr<BList>;

} // namespace bencoding

#endif
