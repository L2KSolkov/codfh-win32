# IDAPython, run inside IDA by tools/initializers.py. For every entry of the
# C++ dynamic-initializer table (__xc_a..__xc_z, 0x426D50..0x4273B4), lists the
# data addresses its function references and the functions it calls, and does
# the same for each atexit destructor thunk it registers.
import json

import ida_bytes
import idautils
import idc

TABLE_START, TABLE_END = 0x426D50, 0x4273B4


def refs(func_ea):
    data, calls = [], []
    end = idc.find_func_end(func_ea)
    if end == idc.BADADDR:
        end = func_ea + 0x40
    for head in idautils.Heads(func_ea, end):
        for ref in idautils.DataRefsFrom(head):
            data.append(ref)
        if idc.print_insn_mnem(head) == 'call':
            target = idc.get_operand_value(head, 0)
            calls.append(target)
        if idc.print_insn_mnem(head) == 'push' and idc.get_operand_type(head, 0) == idc.o_imm:
            value = idc.get_operand_value(head, 0)
            if idc.get_func_attr(value, idc.FUNCATTR_START) == value:
                data.append(value)
    return data, calls


out = []
for slot in range(TABLE_START, TABLE_END, 4):
    target = ida_bytes.get_dword(slot)
    if target in (0, 0xFFFFFFFF):
        continue
    data, calls = refs(target)
    out.append({'slot': slot, 'init': target, 'data': data, 'calls': calls})
print(json.dumps(out))
