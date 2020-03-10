#ifndef UTREEXO_FOREST_H
#define UTREEXO_FOREST_H

#include <uint256.h>

#include <string>
#include <unordered_map>
#include <vector>

class undoBlock;
class BlockProof;

/// LeafTXO is a hash of an individual tx to be added to the Utreexo tree
struct LeafTXO
{
    /// Hash is the TXID of the tx
    uint256 Hash;
    /// Duration is how many blocks elapsed from the creation 
    /// of the tx to when the tx was spent.
    /// If a tx was created at block 100 and was spent at block 200,
    /// it has a Duration of 100.
    /// Used for caching purposes
    uint32_t Duration;

    /// Remember calculates whether the LeafTXO should be cached or not.
    /// User defined cache duration will be used to deterimine theh bool.
    /// Ex. User defined to remember all txs that have a Duration of 1000.
    /// LeafTXO with Duration of 500 will have a Remember value of true.
    /// LeafTXO with Duration of 2000 will have a Remember value of false.
    bool Remember;
};

/// BlockProof provides all data to prove all the LeafTXOs' existance in a given block
/// Since the only time you'll want to prove a UTXO's existence is when you're spending
/// so BlockProof is used for targeting what leaves to delete as well.
struct BlockProof
{
    /// Targets represents all the leaf locations to delete for data field in Forest
    /// for a given block.
    std::vector<uint64_t> Targets;

    /// Proof is the actual 256 bit hashes needed to calculate to a root for a given
    /// LeafTXO. Position of these Proofs are implied as they can be computed from 
    /// leaf positions.
    std::vector<uint256> Proof;
};

/*
 * The forest is structured in the space of a tree numbered from the bottom left,
 * taking up the space of a perfect tree that can contain the whole forest.
 * This means that in most cases there will be null nodes in the tree.
 * That's OK; it helps reduce renumbering nodes and makes it easier to think about
 * addressing.  It also might work well for on-disk serialization.
 * There might be a better / optimal way to do this but it seems OK for now.
*/
class Forest
{
public:
    /// Add adds the given vector of LeafTXOs to the Utreexo forest
    void Add(const std::vector<LeafTXO> adds);

    /// Remove removes the given vector of LeafTXOs from the Utreexo forest
    void Remove(const std::vector<uint64_t>& dels);
    undoBlock Modify(const std::vector<LeafTXO>& adds, const std::vector<uint64_t> dels);

    BlockProof Prove(const uint256& wanted) const;
    std::vector<BlockProof> ProveMany(const std::vector<uint256>& wanted) const;
    bool Verify(const BlockProof& p) const;
    bool VerifyMany(const std::vector<BlockProof>& p) const;
    BlockProof ProveBlock(const std::vector<uint256>& hs) const;
    bool VerifyBlockProof(const BlockProof& bp) const;

    void Undo(const undoBlock& ub) const;
    void PosMapSanity() const;
    std::string Stats() const;
    std::string ToString() const;
    std::vector<uint256> GetTops() const;
    undoBlock BuildUndoData(uint64_t numadds, const std::vector<uint64_t>& dels) const;

private:
    /// reMap recalculates the height of the forest
    /// Does not recalculate a height decrease
    void reMap(uint8_t destHeight);

    /// cleanup removes extra uneeded hashes from the data vector
    void cleanup();

    void sanity() const;
    /// numLeaves represents the number of leaves in the Utreexo forest.
    /// Imagine the bottom nodes in a binary tree or all the individual txs in
    /// a merkle tree.
    uint64_t numLeaves;

    /// Different from block height. Same concept as binary tree height
    /// A Utreexo state may have several merkle trees. This is referred to as the 
    /// forest.
    /// When there is only 1 tree in the forest, height of the forest is equivalent
    /// to the tree. When there are multiple trees, height += tallest_tree + 1 
    /// A Utreexo state may reduce in height. However, this is not calculated at the
    /// moment. So height may be higher than the tallest tree at a state.
    /// Usually the tree will always grow so there is little benefit to calculating
    /// down.
    uint8_t height;

    /// data is the actual leaves in the forest. All are added incrementally.
    /// newest added leaf will be on the far right and the oldest will be on the 
    /// far left.
    std::vector<uint256> data;

    /// positionMap maps individual hashes to their position on the data vector
    std::unordered_map<uint64_t, uint256> positionMap;
};

#endif // UTREEXO_FOREST_H
