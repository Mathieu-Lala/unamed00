/**
 * @file include/ecs/internal/Pool.hpp
 *
 */

#ifndef POOL_HPP_
# define POOL_HPP_

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
    static constexpr type get(const T *, ...)
    {
        return DEFAULT_BLOCK_SIZE;
    }

    template<typename T>
    static constexpr
        std::enable_if_t<!std::is_void_v<decltype(T::BLOCK_SIZE)>, type>
    get(const T *, int)
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
        for (auto &i : mBlocks)
            delete[] i.data;
    }

    template<typename... Args>
    ComponentType *add(entity::ID entityID, Args ...args)
    {
        const auto [blockIndex, componentIndex] = getIndices(entityID);

        if (mBlocks.size() < blockIndex + 1)
            mBlocks.resize(blockIndex + 1);

        auto &block = mBlocks[blockIndex];
        if (!block.data) block.data = new std::int8_t[BLOCK_SIZE * sizeof(ComponentType)];
        block.occupied[componentIndex] = true;

        return new(getPointer(blockIndex, componentIndex)) ComponentType(std::forward<Args>(args)...);
    }

    ComponentType *get(entity::ID entityID)
    {
        const auto [blockIndex, componentIndex] = getIndices(entityID);
        return getPointer(blockIndex, componentIndex);
    }

    void remove(entity::ID entityID) override
    {
        const auto [blockIndex, componentIndex] = getIndices(entityID);
        auto component = getPointer(blockIndex, componentIndex);
        component->~ComponentType();
        mBlocks[blockIndex].occupied[componentIndex] = false;
        checkBlockUsage(blockIndex);
    }

private:

    static constexpr auto BLOCK_SIZE = BlockSize::get<ComponentType>(nullptr, 0);

    static constexpr auto getIndices(entity::ID entityID) -> std::pair<size_t, size_t>
    {
        return { entityID / BLOCK_SIZE, entityID % BLOCK_SIZE };
    }

    ComponentType *getPointer(std::size_t blockIndex, std::size_t componentIndex)
    {
        return reinterpret_cast<ComponentType *>(mBlocks[blockIndex].data) + componentIndex;
    }

    struct Block {
        std::int8_t *data;
        std::bitset<BLOCK_SIZE> occupied;

        Block() : data(nullptr), occupied() { }
        ~Block() = default;
    };

    std::vector<Block> mBlocks;

    void checkBlockUsage(std::size_t blockIndex)
    {
        auto &block = mBlocks[blockIndex];
        if (block.occupied.none()) {
            delete[] block.data;
            block.data = nullptr;
        }
    }

};

} // namespace componenet

} // namespace ecs

#endif /* !POOL_HPP_ */
