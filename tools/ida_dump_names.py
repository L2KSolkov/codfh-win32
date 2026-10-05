# IDAPython, run inside IDA by tools/export_symbols.py. Prints every function
# (start, name, size) and every stored name (address, name) as one JSON object.
import json

import ida_funcs
import ida_segment
import idautils
import idc

out = {'functions': [], 'names': [], 'segments': [], 'chunks': []}
for ea in idautils.Functions():
    f = ida_funcs.get_func(ea)
    out['functions'].append([ea, idc.get_func_name(ea), f.end_ea - f.start_ea])
    # Tail chunks: code IDA attributes to this function but placed elsewhere,
    # such as EH unwind funclets in the grouped .text$x block.
    for start, end in idautils.Chunks(ea):
        if start != f.start_ea:
            out['chunks'].append([start, end - start, ea])
for ea, name in idautils.Names():
    out['names'].append([ea, name])
for seg_ea in idautils.Segments():
    seg = ida_segment.getseg(seg_ea)
    out['segments'].append([seg.start_ea, seg.end_ea, ida_segment.get_segm_name(seg)])
print(json.dumps(out))
