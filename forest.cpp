#include <forest.h>

#include <blockproof.h>
#include <int_types.h>
#include <undo.h>

void Forest::Add(const std::vector<LeafTXO> adds)
{
    for (LeafTXO l : adds) {
        Forest::positionMap
    }

}

void Forest::Remove(const std::vector<uint64_t>& dels)
{
    // TODO
}

undoBlock Forest::Modify(const std::vector<LeafTXO>& adds, const std::vector<uint64_t> dels)
{
    // TODO
    return {};
}

BlockProof Forest::Prove(const uint256& wanted) const
{
    // TODO
    return {};
}

std::vector<BlockProof> Forest::ProveMany(const std::vector<uint256>& wanted) const
{
    // TODO
    return {};
}

bool Forest::Verify(const BlockProof& p) const
{
    // TODO
    return false;
}

bool Forest::VerifyMany(const std::vector<BlockProof>& p) const
{
    // TODO
    return false;
}

BlockProof Forest::ProveBlock(const std::vector<uint256>& hs) const
{
    // TODO
    return {};
}

bool Forest::VerifyBlockProof(const BlockProof& bp) const
{
    // TODO
    return false;
}

void Forest::Undo(const undoBlock& ub) const
{
    // TODO
}

void Forest::reMap(uint8_t destHeight)
{
    // TODO
}

void Forest::cleanup()
{
    // TODO
}

void Forest::sanity() const
{
    // TODO
}

void Forest::PosMapSanity() const
{
    // TODO
}

std::string Forest::Stats() const
{
    // TODO
    return {};
}

std::string Forest::ToString() const
{
    // TODO
    return {};
}

std::vector<uint256> Forest::GetTops() const
{
    // TODO
    return {};
}

undoBlock Forest::BuildUndoData(uint64_t numadds, const std::vector<uint64_t>& dels) const
{
    // TODO
    return {};
}
