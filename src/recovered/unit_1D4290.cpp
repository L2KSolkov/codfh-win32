// The queued packet's implicit copy constructor. Instantiate it from the
// packet header: the unrelated HUD headers introduce a singleton guard
// named $S1, which shifts VC7.1's generated array-loop local names and
// swaps their stack slots (docs/toolchain.md).

#include "game/netqueue.h"

// match: ??0type_3E4E58@@QAE@ABU0@@Z @ 0x001D4290
// The existing list append naturally instantiates the packet copy. Its
// own matching body is placed from unit_1D0100.cpp at 0x1D4070.
template RwInt32 type_1FA230_list<type_3E4E58>::sub_1D3F80(const type_3E4E58 &arg_0);
