// The text type's (type_1CB670, game/loc.h) default constructor, alone in its
// object: unit_0DC400's deferred template functions end before it (PLAN M7).

#include "rw/ostypes.h"
#include "game/loc.h"

// The text's default constructor, out of line (/OPT:ICF folds every
// string type's empty one into it; config/aliases.txt).
// match: ??0type_1CB670@@QAE@XZ @ 0x000E87E0
type_1CB670::type_1CB670()
{
}
