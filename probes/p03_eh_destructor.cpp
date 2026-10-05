// Probe 03: C++ EH. A destructor that calls a member function, then its base
// destructor. The EH frame, the state stores (0, then -1), the unwind funclet
// and the handler thunk must all match; the funclet and thunk live in the
// grouped .text$x block at the end of .text.
//
// match: ??1type_probe_78B40@@QAE@XZ @ 0x00078B40
// match: .text$x+0 @ 0x002FF9F0
// match: __ehhandler$??1type_probe_78B40@@QAE@XZ @ 0x002FF9F8
// symbol: ??1type_probe_16C2A0@@QAE@XZ = 0x0016C2A0

struct type_probe_16C2A0
{
    ~type_probe_16C2A0();  // sub_16C2A0
};

struct type_probe_78B40 : type_probe_16C2A0
{
    void sub_78B90();
    ~type_probe_78B40();  // sub_78B40
};

// sub_78B40
type_probe_78B40::~type_probe_78B40()
{
    sub_78B90();
}
