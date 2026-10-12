r"""alfa.py: writing the game's level scripts (the script VM's task images, GodData kind 12).

The VM (src/recovered/unit_06CA60.cpp, sub_68310) runs 32-bit words: an opcode in the low byte,
a mode byte, then a 16-bit operand or two signed bytes (b2, b3); some opcodes carry data words.
The web suite's script_engine/cfh_decompiler.py names and decodes them; the ones a task needs:

  push   5   mode n: n data words follow, pushed in order
  load   6   operand: push local slot n          store  7: pop into local slot n
  jz    17   operand: pop, jump by it (from this word) when zero
  jump  18   operand: jump by it                 halt  20: end
  command 21 operand: the command's index (the level's command table); pops its arguments,
             pushes its result (symbols.json's "commands": pops, returns)
  pop   38   operand: drop n words
  task_call 39  mode 5, b2 -1, b3 the sender filter (1 anyone, 0x26 from self): wait for the
             message whose id is on the stack (CallTaskScript)
  task_yield 40 mode 1, b2 1: wait for it (YieldTask)
  function 31 mode 0, operand the class function's index: target on the stack, its arguments
             pushed before it (CallObjectFunction: a function of the target's class script)
  action 45  mode 1 (insert) or 0 (append), b2 0: target on the stack, then the message's key in
             the data word; the message's arguments (its "pops") pushed before the target
             (QueueAction: a message to the target's script, as the port's sub_6B5F0)

A task image (sub_72BA0 kind 4, sub_72F00; type_72A30 in include/types/type_72810.h):
  +0x00  "A\0", a relocated flag (0), its kind (4)
  +0x04  type_72A30, offsets relative to +0x04: its name's, its id, the code's, the
         imports', the code's word count (16 bits), the imports' count (16 bits)
  +0x18  the code, then the imports (12 bytes each: an 8-byte key, the kind in the top bits:
         0x20000000 a task, 0x10000000 a function library), then its name (the debug builds'
         scripts, L_3_1's, have one: "L_3_1_CheckPointMonitor"; the release builds' an empty
         string, 0 then 0xCC padding).

Debug information, as the debug builds' scripts carry it: opcode 48 (line, 0xDDDDDD30) and a data
word, the source file's index (the symbols image's file table, GLOBAL.DFF) in its top half and
the line in its low half (sub_6A6F0: the running line, reported to the debugger). With LINE_FILE
set (make_flat.py's with_source_file: its own path added to the table), every Asm marks each
statement (a command, call, action, wait, jump or halt with the pushes before it) with the line of
the task's builder that wrote it, a line word before its pushes when the line changes.
In GODDATA.DFF it is a kind-8 god-asset record: a 28-byte header (8, 0, the record's size, the
tag, the key's two words, a seventh word), then the image (type_3DFAD4::vf_000 reads it).
"""
import struct, sys


def f32(x):
    """A float's bits as a data word."""
    return struct.unpack('<I', struct.pack('<f', x))[0]


LINE_FILE = None    # the source file's index for line words (None: none written)


class Asm:
    """Builds a code word list; labels are resolved when the code is finished."""

    def __init__(self):
        self.words, self.fix, self.labels = [], [], {}
        self.file, self.line, self.start = LINE_FILE, None, None
        # (the function making this code, the task's builder: its lines are the statements,
        # a helper it calls, _tp_wait's three instructions, one statement at the call's line)
        self.owner = sys._getframe(1).f_code

    def mark(self):
        """A statement's line word (opcode 48), before its pushes (self.start, the first push's
        word), when the builder's line (its frame's, else the first frame outside this file) is
        not the last one marked, as the compiler writes one for each source statement."""
        at, self.start = (len(self.words) if self.start is None else self.start), None
        if self.file is None:
            return
        f = sys._getframe(1)
        while f and f.f_code.co_filename == __file__:
            f = f.f_back
        g = f
        while g and g.f_code is not self.owner:
            g = g.f_back
        f = g or f
        if f is None or f.f_lineno == self.line:
            return
        self.line = f.f_lineno
        self.words[at:at] = [0xDDDDDD30, (self.file << 16 | self.line & 0xFFFF) & 0xFFFFFFFF]
        self.labels = {k: v + 2 if v > at else v for k, v in self.labels.items()}
        self.fix = [(p + 2 if p >= at else p, k) for p, k in self.fix]

    def word(self, op, mode=0xDD, operand=None, b2=None, b3=None, statement=True):
        if statement:
            self.mark()
        elif self.start is None:
            self.start = len(self.words)
        if operand is not None:
            w = op | (mode << 8) | ((operand & 0xFFFF) << 16)
        else:
            w = op | (mode << 8) | ((b2 & 0xFF) << 16) | ((b3 & 0xFF) << 24)
        self.words.append(w)

    def label(self, name):
        self.labels[name] = len(self.words)

    def push(self, *values):
        self.word(5, len(values), 1 if len(values) == 1 else len(values), statement=False)
        self.words += [v & 0xFFFFFFFF for v in values]

    def command(self, index):
        self.word(21, 0xDD, index)

    def pop(self, n=1):
        self.word(38, 0xDD, n)

    def jump(self, label):
        self.mark()
        self.fix.append((len(self.words), label))
        self.word(18, 0xDD, 0)

    def jz(self, label):
        """Pops a word; jumps to label when it is zero (opcode 17, the operand relative)."""
        self.mark()
        self.fix.append((len(self.words), label))
        self.word(17, 0xDD, 0)

    def halt(self):
        self.mark()
        self.words.append(0xDDDDDD14)

    def wait_message(self, message, sender=1):
        """CallTaskScript(message, -1, sender, true); YieldTask(1)."""
        self.push(message)
        self.word(39, 5, b2=-1, b3=sender)
        self.word(40, 1, b2=1, b3=0xDD)

    def queue(self, message, args, target_command, append=False):
        """QueueAction(target, message, ACTION_INSERT_CURRENT, args...), or ACTION_APPEND with
        append: the arguments, then the target (the result of the command target_command), then
        the action."""
        for a in args:
            self.push(a)
        self.command(target_command)
        self.word(45, 0 if append else 1, b2=0, b3=0xDD)
        self.words.append(message)

    def function(self, index, args, target_command):
        """CallObjectFunction(target, function_<index>, args...): the arguments, then the target
        (the result of the command target_command), then the call (opcode 31, mode 0)."""
        for a in args:
            self.push(a)
        self.command(target_command)
        self.word(31, 0, index)

    def finish(self):
        for at, name in self.fix:
            rel = self.labels[name] - at
            self.words[at] = (self.words[at] & 0xFFFF) | ((rel & 0xFFFF) << 16)
        return self.words


def task_image(ident, words, imports=(), name=''):
    """A task image: id, code words, imports ((key8, kind word), ...), its name."""
    code = struct.pack('<%dI' % len(words), *words)
    imp = b''.join(k + struct.pack('<I', kind) for k, kind in imports)
    code_off = 0x14                    # (from +0x04: the code at +0x18)
    imp_off = code_off + len(code)
    name_off = imp_off + len(imp)
    text = name.encode('ascii') + b'\0'
    text += b'\xcc' * (-len(text) % 4)
    body = struct.pack('<4i2H', name_off, ident, code_off, imp_off if imports else 0, len(words), len(imports))
    return b'A\0\0\x04' + body + code + imp + text


def god_record(template, key8, image):
    """A GODDATA.DFF chunk for image under key8: template's (a kind-12 task record's) chunk and
    record headers, the sizes and the key replaced."""
    rec = bytearray(template[12:12 + 28])
    struct.pack_into('<I', rec, 8, 28 + len(image))
    rec[16:24] = key8
    payload = bytes(rec) + image
    kind, _, ver = struct.unpack_from('<3I', template)
    return struct.pack('<3I', kind, len(payload), ver) + payload
