/*
 * The animation keys' shared tables (src/recovered/unit_07CA20.cpp): a channel whose keys are
 * another animation's keeps them as a packed word, bit 31 for shared, bit 30 for not yet resolved
 * and the table's address in the low 30 bits. The Xbox's addresses are all below 1 GB; the port's
 * (a large-address-aware process) are not, and an address at or over 0x40000000 lost its bit 30
 * (read back 1 GB too low, and taken for unresolved again). The port keeps the addresses here and
 * packs an index in their place: port_anim_key_pack gives the index of p (the same one each time
 * p is packed), port_anim_key_unpack the address of a packed word's index.
 */

#include <unordered_map>
#include <vector>

static std::vector<void *> s_apKeys;
static std::unordered_map<void *, unsigned> s_mIndex;

int port_anim_key_pack(void *p)
{
    std::unordered_map<void *, unsigned>::iterator it = s_mIndex.find(p);
    unsigned i;

    if (it != s_mIndex.end())
        i = it->second;
    else
    {
        i = (unsigned)s_apKeys.size();
        s_apKeys.push_back(p);
        s_mIndex[p] = i;
    }
    return (int)(i | 0x80000000u);
}

void *port_anim_key_unpack(int v)
{
    unsigned i = (unsigned)v & 0x3FFFFFFFu;

    return i < s_apKeys.size() ? s_apKeys[i] : 0;
}
