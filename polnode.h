#ifndef UTREEXO_POLNODE_H
#define UTREEXO_POLNODE_H

#include <uint256.h>

/// polNode is the binary tree representation of a Utreexo Compact State Node
/// Each polNode points to nieces, not children.
class polNode
{
public:
    uint256 auntOp();
    bool auntable();
    bool deadEnd();
    void chop();
    void prune();
    void leafPrune();
    uint256 data;
    polNode* niece[2];
};

#endif // UTREEXO_POLNODE_H
