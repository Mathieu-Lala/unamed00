/**
 * @file include/ecs/internal/Pool.hpp
 *
 */

#ifndef ECS_INTERNAL_POOL_HPP_
# define ECS_INTERNAL_POOL_HPP_

# include <bitset>
# include <cinttypes>
# include <vector>

namespace ecs {

namespace component {

namespace {

struct BlockSize {

    using type = std::size_t;

    static constexpr type DEFAULT_BLOCK_SIZE = 64ul;

    template<typename T>
    static constexpr
    auto get(const T *, ...) -> type
    {
        return DEFAULT_BLOCK_SIZE;
    }

    template<typename T>
    static constexpr
    auto get(const T *, int) ->
        std::enable_if_t<!std::is_void_v<decltype(T::BLOCK_SIZE)>, type>
    {
        return T::BLOCK_SIZE;
    }

};

} // anonymous namespace

class PoolBase {
public:
    virtual ~PoolBase() = default;
    virtual void remove(entity::ID) = 0;
};

template<typename ComponentType>
class Pool : public PoolBase {
public:

    Pool() = default;
    virtual ~Pool()
    {
        for (auto &i : m_blocks)
            delete[] i.data;
    }

    template<typename... Args>
    auto add(entity::ID entityID, Args ...args) -> ComponentType *
    {
        const auto [blockIndex, componentIndex] = getIndices(entityID);

        if (m_blocks.size() < blockIndex + 1)
            m_blocks.resize(blockIndex + 1);

        auto &block = m_blocks[blockIndex];
        if (!block.data) block.data = new std::int8_t[BLOCK_SIZE * sizeof(ComponentType)];
        block.occupied[componentIndex] = true;

        return new(getPointer(blockIndex, componentIndex)) ComponentType(std::forward<Args>(args)...);
    }

    auto get(entity::ID entityID) -> ComponentType *
    {
        if (!has(entityID)) return nullptr;
        const auto [blockIndex, componentIndex] = getIndices(entityID);
        return getPointer(blockIndex, componentIndex);
    }

    void remove(entity::ID entityID) override
    {
        const auto [blockIndex, componentIndex] = getIndices(entityID);
        auto component = getPointer(blockIndex, componentIndex);
        component->~ComponentType();
        m_blocks[blockIndex].occupied[componentIndex] = false;
        checkBlockUsage(blockIndex);
    }

    auto has(entity::ID entityID) const -> bool
    {
        const auto [blockIndex, componentIndex] = getIndices(entityID);
        return m_blocks.size() > blockIndex && m_blocks[blockIndex].occupied[componentIndex];
    }

private:

    static constexpr auto BLOCK_SIZE = BlockSize::get<ComponentType>(nullptr, 0);

    static constexpr
    auto getIndices(entity::ID entityID) -> std::pair<size_t, size_t>
    {
        return { entityID / BLOCK_SIZE, entityID % BLOCK_SIZE };
    }

    auto getPointer(std::size_t blockIndex, std::size_t componentIndex) -> ComponentType *
    {
        return reinterpret_cast<ComponentType *>(m_blocks[blockIndex].data) + componentIndex;
    }

    struct Block {
        std::int8_t *data;
        std::bitset<BLOCK_SIZE> occupied;

        Block() : data(nullptr), occupied() { }
        ~Block() = default;
    };

    std::vector<Block> m_blocks;

    void checkBlockUsage(std::size_t blockIndex)
    {
        auto &block = m_blocks[blockIndex];
        if (block.occupied.none()) {
            delete[] block.data;
            block.data = nullptr;
        }
    }

};

} // namespace componenet

} // namespace ecs

#endif /* !ECS_INTERNAL_POOL_HPP_ */
