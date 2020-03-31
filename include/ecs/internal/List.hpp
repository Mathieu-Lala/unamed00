/**
 * @file include/ecs/internal/List.hpp
 *
 */

#ifndef LIST_HPP_
# define LIST_HPP_

# include <cinttypes>
# include <limits>
# include <iterator>

namespace ecs {

namespace entity { struct Handler; };

struct EntityList;

// used by std::for_each
class Iterator {
public:
    using IndexType = std::size_t;
    static constexpr IndexType MAX_INDEX = std::numeric_limits<IndexType>::max();

    using iterator_category = std::forward_iterator_tag;
    using value_type = entity::Handler;
    using pointer = entity::Handler *;
    using reference = entity::Handler &;
    using difference_type = std::ptrdiff_t;

    Iterator() :
        m_list  (nullptr),
        m_index (MAX_INDEX)
    { }
    Iterator(const EntityList *list, IndexType index) :
        m_list  (list),
        m_index (index)
    { }

    Iterator &operator++();
    Iterator operator++(int);

    bool operator==(const Iterator &other) const
        { return this->m_list == other.m_list && this->m_index == other.m_index; }
    bool operator!=(const Iterator &other) const
        { return !(*this == other); }

    entity::Handler operator*() const;

private:
    const EntityList *m_list;
    IndexType m_index;
};

struct EntityList {

    component::Mask m_mask;

    EntityList(component::Mask mask) : m_mask(mask) { }
    ~EntityList() = default;

    Iterator begin() const { return ++Iterator(this, -1); }
    Iterator end() const { return Iterator(this, Iterator::MAX_INDEX); }

};

// Implementation

Iterator Iterator::operator++(int)
{
    Iterator ret(*this);
    (*this)++;
    return ret;
}

} // namespace ecs

#endif /* !LIST_HPP_ */
