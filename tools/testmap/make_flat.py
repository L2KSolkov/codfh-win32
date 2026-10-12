r"""make_flat.py <out> [--src DIR] [--size N] [--cells N]: a test level with an empty flat floor.

Writes <out> (a level folder, e.g. build/port_sp/LEVELS/TESTFLAT) for the port's
-leveldir option (port/src/cli.cpp): codfh.exe -map 1 -leveldir TESTFLAT (the source level's -map number), run from the folder
holding LEVELS (files COD.PAK lacks are opened relative to the working directory).

What a level needs to start (sub_D7570's gate, docs: the god-asset request list and the
loading-stage counter dword_4B86FC):
  - GODDATA.DFF answering every god asset the level's objects and the level start ask for,
    and holding the level-directory, path-node, particle and object-list chunks the stage
    counter waits on. GodData is read on demand (unrequested assets are skipped), so the
    source level's own GodData.dff, unchanged, satisfies a level with fewer objects.
  - GLOBAL.DFF and LEVEL.DFF: the source level's, LEVEL.DFF filtered to its system entities and
    its PlayerTrigger (no triggers, scripts, sections or SectionInfo/StartingSections, so
    sub_D8660 loads sections 1-4 and finds only S_1).
  - SECTIONS\\S_1.RWS: section records (kind, size, data; kind 11 ends) holding a collision BSP
    (record 2, sub_142890) and an opaque BSP (record 0, sub_142030), both RenderWare 3.6 worlds
    (chunk version 0x1803FFFF) with one atomic sector. The collision world's sector carries a
    collision tree (RpCollision skips sectors without one): coll_tree's splits, leaves of at
    most COLL_LEAF triangles.
  - Clump banks: not copied; -leveldir reads Clumps\ from the -map level's own folder in the
    pack (sub_D7F40), so the source level must be the -map level (L_1_1_B is -map 1, which
    has no intro movie). A bank read off the disk crashed in sub_190B20.
The floor is centred under the source level's PlayerTrigger, at its feet (120 below it).

"""
import argparse, math, pathlib, re, struct, sys

VER = 0x1803FFFF            # RenderWare 3.6.0.3, as the levels' files are stamped
SUITE = r'C:\cfh-web-suite'  # its attribute-packet decoder finds the PlayerTrigger's matrix

# The system entities a level keeps (the rest of LEVEL.DFF is left out).
KEEP = {'RenderTrigger', 'WorldLight', 'CAnimPackSelector', 'CPickupSelector',
        'CShellLevelBehaviorClass', 'CAnimBankInfo', 'LevelInfo', 'CMountedWeaponSelector',
        'LevelClumpBankParamTrigger', 'CPoolSizes', 'CSoundBankSelector', 'CDebugTools',
        'PlayerTrigger'}


def chunk(kind, payload):
    return struct.pack('<3I', kind, len(payload), VER) + payload


def material(colour):
    # struct: flags, colour, unused, textured, ambient/specular/diffuse; ext: the game's 0x7A7
    s = struct.pack('<I4BIi3f', 0, *colour, 0, 0, 1.0, 1.0, 1.0)
    return chunk(0x7, chunk(0x1, s) + chunk(0x3, chunk(0x7A7, struct.pack('<I', 0))))


COLL_LEAF = 32      # triangles a collision leaf holds at most (RenderWare's limit: 239, 0xEF)


def coll_tree(verts, tris):
    """A collision tree for tris (RpCollTree, src/rw/plugin/collis/ctdata.[ch]): (splits, map).
    Each split (16 bytes) is its left and right sectors (type, contents, index, value: the left
    covers the axis up to its value, the right from its value up, the two may overlap); type
    is the axis (0 x, 4 y, 8 z), the left's with 1 set; contents is a leaf's count (index its
    first place in the map) or 0xFF for a split (index the split's). Split 0 is the root. The
    tree halves its triangles at the median of their centres along the longest side of their
    box until a part holds at most COLL_LEAF; the map lists the triangles leaf by leaf."""
    boxes = []
    for a, b, c in tris:
        ps = (verts[a], verts[b], verts[c])
        boxes.append(([min(p[k] for p in ps) for k in range(3)], [max(p[k] for p in ps) for k in range(3)]))
    splits, order = [], []

    def sector(ids):
        """(contents, index) for ids, splits added for it."""
        if len(ids) <= COLL_LEAF:
            first = len(order)
            order.extend(ids)
            return len(ids), first
        lo = [min(boxes[i][0][k] for i in ids) for k in range(3)]
        hi = [max(boxes[i][1][k] for i in ids) for k in range(3)]
        axis = max(range(3), key=lambda k: hi[k] - lo[k])
        ids = sorted(ids, key=lambda i: boxes[i][0][axis] + boxes[i][1][axis])
        left, right = ids[:len(ids) // 2], ids[len(ids) // 2:]
        me = len(splits)
        splits.append(None)
        lval = max(boxes[i][1][axis] for i in left)
        rval = min(boxes[i][0][axis] for i in right)
        lc, li = sector(left)
        rc, ri = sector(right)
        splits[me] = struct.pack('<BBHfBBHf', axis * 4 | 1, lc, li, lval, axis * 4, rc, ri, rval)
        return 0xFF, me

    contents, index = sector(list(range(len(tris))))
    return splits, order


def world(verts, tris, fmt, normals=None, prelit=None, colltree=False, colour=(255, 255, 255, 255)):
    nv, nt = len(verts), len(tris)
    xs, ys, zs = zip(*verts)
    inf = (min(xs), min(ys) - 1.0, min(zs))
    sup = (max(xs), max(ys) + 1.0, max(zs))
    # atomic sector
    s = struct.pack('<3i3f3f2i', 0, nt, nv, *inf, *sup, 0, 0)
    s += b''.join(struct.pack('<3f', *v) for v in verts)
    if normals is not None:
        s += b''.join(struct.pack('<3bB', *n, 0) for n in normals)
    if prelit is not None:
        s += b''.join(struct.pack('<4B', *c) for c in prelit)
    s += b''.join(struct.pack('<4H', a, b, c, 0) for a, b, c in tris)
    mesh = struct.pack('<3I', 0, 1, nt * 3) + struct.pack('<2I', nt * 3, 0)
    mesh += b''.join(struct.pack('<3I', *t) for t in tris)
    ext = chunk(0x50E, mesh)
    if colltree:
        # (with an entry map, rpCOLLTREE_USEMAP: the game's own line test, sub_91F40, reads it
        # unchecked; split, coll_tree, when there are more than a leaf holds)
        if nt <= COLL_LEAF:
            splits, order = [], list(range(nt))
        else:
            splits, order = coll_tree(verts, tris)
        tree = chunk(0x1, struct.pack('<I3f3f2I', 1, *inf, *sup, nt, len(splits)) + b''.join(splits)
                     + struct.pack('<%dH' % nt, *order))
        ext += chunk(0x11D, struct.pack('<I', 0x36003) + chunk(0x2C, tree))
    sector = chunk(0x9, chunk(0x1, s) + chunk(0x3, ext))
    # world: root is the sector; bounding box sup then inf
    w = struct.pack('<i3f6I3f3f', 1, 0.0, 0.0, 0.0, nt, nv, 0, 1, 0, fmt, *sup, *inf)
    mats = chunk(0x8, chunk(0x1, struct.pack('<Ii', 1, -1)) + material(colour))
    return chunk(0xB, chunk(0x1, w) + mats + sector + chunk(0x3, b''))


def floor(cx, y, cz, size, cells, course=None):
    """The floor section: its collision world (the floor's two triangles, and the course's solids)
    and its drawn world (a checkerboard of cells a
    side, and the course)."""
    step = size / cells
    x0, z0 = cx - size / 2, cz - size / 2
    x1, z1 = x0 + size, z0 + size
    # collision: two triangles wound so their normals face +y (the floor is flat: its cells are
    # only drawn), then the course's
    cverts = [(x0, y, z0), (x0, y, z1), (x1, y, z0), (x1, y, z1)]
    ctris = [(0, 1, 2), (2, 1, 3)]
    if course is not None:
        v, t = course.collision()
        ctris += [(a + len(cverts), b + len(cverts), c + len(cverts)) for a, b, c in t]
        cverts += v
    coll = world(cverts, ctris, 0x40000000, colltree=True)
    # opaque: four vertices a cell, prelit as a checkerboard (positions, prelit, normals, light)
    verts, tris, prelit = [], [], []
    for i in range(cells):
        for j in range(cells):
            b = len(verts)
            xa, xb, za, zb = x0 + i * step, x0 + (i + 1) * step, z0 + j * step, z0 + (j + 1) * step
            verts += [(xa, y, za), (xa, y, zb), (xb, y, za), (xb, y, zb)]
            shade = (150, 150, 150, 255) if (i + j) & 1 else (90, 95, 100, 255)
            prelit += [shade] * 4
            tris += [(b, b + 1, b + 2), (b + 2, b + 1, b + 3)]
    normals = [(0, 127, 0)] * len(verts)
    if course is not None:
        v, t, n, c = course.drawn()
        tris += [(a + len(verts), b + len(verts), d + len(verts)) for a, b, d in t]
        verts += v
        normals += n
        prelit += c
    opaque = world(verts, tris, 0x40000000 | 0x2 | 0x8 | 0x10 | 0x20, normals=normals, prelit=prelit)
    rec = lambda kind, data: struct.pack('<2I', kind, len(data)) + data
    return rec(2, coll) + rec(0, opaque) + struct.pack('<I', 11)


def path_graph(cx, y, cz, size, spacing=500.0, cell=500):
    """GODDATA's path-node graph (record kind 13: sub_142CA0 -> sub_F8350; layout in the web
    suite's PATHFINDING.md) for the floor: a grid of waypoints (type 1) spacing apart at floor
    height, each linked to its eight neighbours, and the search grid of cell-sized squares
    (world x, z) listing the nodes in each. Six structures: the 96-byte header, node offsets by
    id (id 0 the null), the node buffer (flags, type, two runtime words, position, then link
    words: two 12-bit ids each, a zero id ending them), the grid's cells (a list index, 0xFFFF
    none), the lists' offsets and the lists (packed like the links)."""
    m = int(size // spacing) + 1
    x0, z0 = cx - size / 2, cz - size / 2
    ident = lambda i, j: i * m + j + 1
    pos = {ident(i, j): (x0 + i * spacing, y, z0 + j * spacing) for i in range(m) for j in range(m)}
    assert len(pos) + 1 <= 4096, 'at most 4095 nodes (12-bit ids)'

    def packed(ids):
        words, ids = [], list(ids)
        for k in range(0, len(ids), 2):
            words.append(ids[k] | ((ids[k + 1] << 12) if k + 1 < len(ids) else 0))
        if len(ids) % 2 == 0:
            words.append(0)
        return struct.pack('<%dI' % len(words), *words)

    buf, offs = b'', [0]
    for i in range(m):
        for j in range(m):
            n = ident(i, j)
            links = [ident(i + a, j + b) for a in (-1, 0, 1) for b in (-1, 0, 1)
                     if (a or b) and 0 <= i + a < m and 0 <= j + b < m]
            offs.append(len(buf))
            buf += struct.pack('<IHHii3f', 0, 1, 0, 0, 0, *pos[n]) + packed(links)
    ox, oz = x0 - cell, z0 - cell
    gw = gh = int((size + 2 * cell) // cell) + 1
    lists, cells = {}, [0xFFFF] * (gw * gh)
    for n, (px, py, pz) in pos.items():
        lists.setdefault(int((pz - oz) // cell) * gw + int((px - ox) // cell), []).append(n)
    lbuf, loffs = b'', []
    for k, (c, ids) in enumerate(sorted(lists.items())):
        cells[c] = k
        loffs.append(len(lbuf))
        lbuf += packed(ids)
    s2 = struct.pack('<%dI' % len(offs), *offs)
    s4 = struct.pack('<%dH' % len(cells), *cells)
    s5 = struct.pack('<%dI' % len(loffs), *loffs)
    head = struct.pack('<6I3f', 5, cell, len(offs), 0, 0, 0, ox, 0.0, oz)
    head += struct.pack('<15I', gw, gh, 0, len(s2), 0, len(buf), 0, len(s4), len(loffs), 0, len(s5), 0,
                        len(lbuf), 0, 0)
    assert len(head) == 96
    body = b''.join(chunk(1, b) for b in (head, s2, buf, s4, s5, lbuf))
    rec = struct.pack('<7I', 13, 0, 28 + len(body), 0, 0, 0, 0) + body
    return chunk(0x719, rec), len(pos)


def with_path_graph(god, graph):
    """GODDATA with its path-node graph (the kind-13 chunk) replaced."""
    out = []
    for kind, c in chunks_of(god):
        if kind == 0x719 and len(c) >= 16 and struct.unpack_from('<I', c, 12)[0] == 13:
            c = graph
        out.append(c)
    return b''.join(out)


def filter_level(data, bazooka=False):
    sys.path.insert(0, SUITE)
    from objects import packet
    out, kept, player = b'', [], None
    p = 0
    while p + 12 <= len(data):
        kind, size, _ = struct.unpack_from('<3I', data, p)
        body = data[p + 12:p + 12 + size]
        keep = True
        if kind == 0x704:
            cls, guid, cmds = packet(body[4:])
            keep = cls in KEEP or guid == SOLDIER
            if keep:
                kept.append(cls)
            if cls == 'PlayerTrigger':
                player = cmds
        if keep and kind == 0x704 and guid == SOLDIER:
            # (its name, SoldierTrigger command 1: the one shown over it; its weapon, 38)
            edits = {('SoldierTrigger', 1): SOLDIER_NAME.encode() + b'\0'}
            if bazooka:
                edits[('SoldierTrigger', 38)] = SOLDIER_WEAPON
            out += rewrite_packet(data[p:p + 12 + size], edits)
        elif keep:
            out += data[p:p + 12 + size]
        p += 12 + size
    return out, kept, player


def rewrite_packet(chunk, edits, guid=None):
    """A 0x704 chunk (header, the global flag, the attribute packet) with commands replaced:
    edits maps (owner, command) to its new bytes; guid, if given, the new instance ID (16
    bytes). Packet entries are (size with its 8-byte head, kind, data); a zero size ends them."""
    body = chunk[12:]
    used = set()
    out, q, owner = bytearray(body[:4]), 4, ''
    while q + 4 <= len(body):
        n = struct.unpack_from('<I', body, q)[0]
        if n == 0:
            out += body[q:]
            break
        k = struct.unpack_from('<I', body, q + 4)[0]
        raw = body[q + 8:q + n]
        if k == 0x80000000:
            owner = raw.split(b'\0', 1)[0].decode('cp1252')
        elif k == 0x40000000 and guid is not None:
            raw = guid
        elif (owner, k) in edits:
            raw = edits[owner, k]
            used.add((owner, k))
        out += struct.pack('<2I', len(raw) + 8, k) + raw
        q += n
    missing = set(edits) - used
    if missing:
        print('rewrite_packet: no such commands to replace: %s' % ', '.join('%s %d' % m for m in sorted(missing)))
    kind, _, ver = struct.unpack_from('<3I', chunk)
    return struct.pack('<3I', kind, len(out), ver) + bytes(out)


def chunks_of(data):
    p = 0
    while p + 12 <= len(data):
        kind, size, _ = struct.unpack_from('<3I', data, p)
        yield kind, data[p:p + 12 + size]
        p += 12 + size


def selector_keys(level_dff, packet):
    """The pickup settings keys a level's CPickupSelector registers (its command 0: a count,
    then 8-byte keys of type-43 assets, each naming a pickup id and its model)."""
    for kind, c in chunks_of(level_dff):
        if kind == 0x704:
            cls, guid, cmds = packet(c[16:])
            if cls == 'CPickupSelector':
                for o, k, raw in cmds:
                    if o == 'CPickupSelector' and k == 0:
                        n = struct.unpack_from('<I', raw)[0]
                        return [raw[4 + i * 8:12 + i * 8] for i in range(n)]
    return []


def skey(raw8):
    return '%08X,%08X' % struct.unpack('<2I', raw8)


def god_records(goddata):
    """GODDATA.DFF's god-asset chunks (0x719, records of kinds 8 and 9: a 28-byte header of kind,
    section, size, tag and the key's two words, then the data) by their first record's key; and
    the other chunks (the level's directory, path nodes, particles, object lists)."""
    assets, other = {}, []
    for kind, c in chunks_of(goddata):
        if kind == 0x719 and len(c) >= 12 + 28 and struct.unpack_from('<I', c, 12)[0] in (8, 9):
            assets.setdefault(skey(c[12 + 16:12 + 24]), c)
        else:
            other.append(c)
    return assets, other


def record_data(chunk):
    size = struct.unpack_from('<I', chunk, 12 + 8)[0]
    return chunk[12 + 28:12 + size]


# Levels whose god data, between them, hold every pickup settings asset the disc has: 95 of
# the 110 pickup ids, the Bazooka (16) from the multiplayer MP_9. No level's god data has the
# others: 0, 1, 107, the Luger's (4, 18-20), the Bazooka's ammunition (60-62), the M8 smoke
# (88, 89), one teddy bear (90) and the Grease Gun's ammunition (105, 106).
PICKUP_LEVELS = ['L_3_5_C', 'L_1_2', 'L_2_2_B', 'L_2_1', 'L_1_2_B', 'L_3_1_B', 'L_3_3', 'L_2_2', 'L_3_5_B',
                 'MP_9']


def pickup_assets(pak, level, level_dff, god, packet):
    """god with the other levels' god-asset chunks added after its own (their pickup settings,
    models and textures; only what is asked for is read), and one settings key per pickup id
    the levels have (from their CPickupSelectors; the id is the settings' link 2, a 4-byte
    variable, as bind_pickup_models and the game read it)."""
    from associations import refs
    assets, other = god_records(god)
    order = list(assets)
    settings = []
    for lv in [level] + PICKUP_LEVELS:
        if lv == level:
            dff = level_dff
        else:
            dff = pak.read('LEVELS\\%s\\LEVEL.DFF' % lv)
            for k, c in god_records(pak.read('LEVELS\\%s\\GODDATA.DFF' % lv))[0].items():
                if k not in assets:
                    assets[k] = c
                    order.append(k)
        settings += [raw for raw in selector_keys(dff, packet) if raw not in settings]
    by_id = {}
    for raw in settings:
        c = assets.get(skey(raw))
        if c is None:
            continue
        try:
            var = assets.get(refs(record_data(c)).get(2))
        except ValueError:
            continue
        if var is not None and len(record_data(var)) == 4:
            pid = struct.unpack('<i', record_data(var))[0]
            if 0 <= pid < 110:
                by_id.setdefault(pid, raw)
    # (the level's own chunks first, in its order: the non-asset ones where they were)
    god_out = []
    seen = set()
    for kind, c in chunks_of(god):
        god_out.append(c)
        if kind == 0x719 and len(c) >= 40 and struct.unpack_from('<I', c, 12)[0] in (8, 9):
            seen.add(skey(c[12 + 16:12 + 24]))
    god_out += [assets[k] for k in order if k not in seen]
    return b''.join(god_out), by_id


def pickup_triggers(level_dff, ids, matrix, y, packet):
    """One PickupTrigger per pickup id: copies of the level's first (its creation script spawns
    its pickup at the level's start), each a new instance ID, its id (PickupTrigger command 0),
    a quantity (1: 30), no fall (2: 0), no respawn, at its place on a line across the player
    start's view 8 m ahead, 0.8 m apart (its matrix, CSystemCommands command 1: right, up, at,
    position, each four floats)."""
    template = next(c for kind, c in chunks_of(level_dff)
                    if kind == 0x704 and packet(c[16:])[0] == 'PickupTrigger')
    guid = packet(template[16:])[1]
    words = [int(w, 16) for w in guid.split('-')]
    right, at, px, pz = matrix[0:3], matrix[8:11], matrix[12], matrix[14]
    fx, fz = at[0], at[2]
    flen = math.hypot(fx, fz) or 1.0
    fx, fz = fx / flen, fz / flen
    rx, rz = fz, -fx
    out = b''
    n = len(ids)
    for i, pid in enumerate(sorted(ids)):
        off = (i - (n - 1) / 2.0) * 80.0
        pos = (px + fx * 800.0 + rx * off, y, pz + fz * 800.0 + rz * off)
        m = struct.pack('<16f', rx, 0, rz, 0, 0, 1, 0, 0, fx, 0, fz, 0, pos[0], pos[1], pos[2], 1)
        new_guid = struct.pack('<4I', words[0], words[1], words[2], 0xC0DE0000 + pid)
        out += rewrite_packet(template, {
            ('PickupTrigger', 0): struct.pack('<i', pid),
            ('PickupTrigger', 1): struct.pack('<i', 30),
            ('PickupTrigger', 2): struct.pack('<i', 0),
            ('PickupTrigger', 3): struct.pack('<i', -1),
            ('Trigger', 14): SPAWN_TASK,
            ('CSystemCommands', 1): m,
        }, new_guid)
    return out


# Every kind of vehicle the disc has (--no-vehicles leaves them out), in a row 25 m in front of
# the player (clear of the pickups' line at 8 m: at 15 m the longest took four pickups' places), 10 m apart, facing as the player does: for each, a copy of the first trigger in its
# source level whose definition's (VehicleTrigger command 2) records name its texture. The
# sources are levels with no clump banks (their vehicles' models are all in their GodData),
# whose GodData chunks are added to the level's (after its own and the pickups' levels': only
# what is asked for is read). Each copy: its own instance ID; its names (VehicleTrigger 0,
# Trigger 0) and links to other triggers (Trigger 15) cleared; its own tasks (VehicleTrigger 14,
# which may import its level's scripts, and 15: its level's own, which finds that level's named
# entities) replaced, 14 by ours (PARKED_TASK: its AI off) and 15 cleared; its control (VehicleTrigger 7, unk_EC: 1 an AI crew's,
# its AI script and crew, which hold it; 2 the player put in at once, vf_268; 3 the player's to
# enter: L_1_5's player tank) set to 3. They spawn on "CreateChild" (their creation script,
# BasicCreationTrigger; the port's -leveldir sends it to kind 7). A vehicle (0x2860-0x29D0
# bytes) fits only entity pool 8, which L_1_1_B leaves at 0 (CPoolSizes command 8), and its guns
# are mounted weapons (0x5E0, pool 3, command 4): both raised.
VEHICLES = [
    ('Sherman', 'L_3_3', 'VehicleTrigger', b'VTrackL_Sherman'),
    ('Panzer IV', 'L_3_3', 'VehicleTrigger', b'VT_PanzerIV_middle'),
    ('King Tiger', 'L_3_3', 'VehicleTrigger', b'VT_KingTiger_back'),
    ('M12', 'L_3_3', 'VehicleTrigger', b'VT_M12_barrel'),
    ('Flak 88', 'L_3_3', 'FlakTrigger', b'VT_Flak88_barrel'),
    ('T-34', 'L_1_2_B', 'VehicleTrigger', b'VT_T34_back'),
    ('Sd.Kfz. 251', 'L_2_2', 'VehicleTrigger', b'VT_Sdkfz251_back'),
    ('Opel truck', 'L_2_2', 'VehicleTrigger', b'VT_Opel_front'),
    ('Jeep', 'L_2_2', 'VehicleTrigger', b'VT_Jeep_interior'),
]
VEHICLE_LOW = 0xC0DEF1A0
# The vehicles' own task (VehicleTrigger 14, unk_D0: control 3 gives the vehicle an AI object
# running its class, TankClass or VehicleClass, and this task, sub_70F40): its AI off, as the
# tank script's "ConnectEntityToSelf" turns it off for a driver ("SetManeuverState" 2,
# "SetAIMode" 0, "SetAIControl" 0; the port's drive button does the same). Without it the class
# runs its own AI (Pursue, Attack) for its source level's side. (Not the levels' way for a player
# tank: their spawn message block, VehicleTrigger 16, "ExternalEntityControlled", puts the player
# in it at once, as L_1_5 starts in its tank.)
PARKED_TASK = struct.pack('<2I', 0xC0DE5EA7, 1)
TASK_POOL_EXTRA = 100
CMD_SETAICONTROL, CMD_SETMANEUVERSTATE, CMD_SETAIMODE = 432, 433, 441


def parked_task(ident, name='TESTFLAT_ParkedVehicle'):
    import alfa
    a = alfa.Asm()
    a.wait_message(MSG_INITIALIZE, 1)
    _tp_wait(a, 0.5)
    a.push(2)
    a.command(CMD_SETMANEUVERSTATE)
    a.push(0)
    a.command(CMD_SETAIMODE)
    a.pop(1)
    a.push(0)
    a.command(CMD_SETAICONTROL)
    a.halt()
    return alfa.task_image(ident, a.finish(), name=name)
# A vehicle's gun (VehicleTrigger 52 set) is mounted-weapon slot VehicleTrigger 53 (GLOBAL.DFF's
# CMountedWeaponBehavior entities: the same seven in every level), whose model a kind-0x2F asset
# binds when it is read; the level's CMountedWeaponSelector (command 0: a count, then keys) asks
# for those. L_1_1_B's asks for the tripod MG42's alone, and the Jeep's .50 cal (slot 2) then
# has none: its spawn faulted (type_3DC9B0::sub_166FA0, a null model). So the selector is given
# the source levels' keys too.


def mounted_selector_keys(dff, packet):
    for kind, c in chunks_of(dff):
        if kind == 0x704 and packet(c[16:])[0] == 'CMountedWeaponSelector':
            raw = next(r for o, k, r in packet(c[16:])[2] if o == 'CMountedWeaponSelector' and k == 0)
            n = struct.unpack_from('<I', raw)[0]
            return [raw[4 + i * 8:12 + i * 8] for i in range(n)]
    return []


def with_mounted_selector(level, keys, packet):
    """level's CMountedWeaponSelector asking for its own keys and then keys."""
    out = b''
    for kind, c in chunks_of(level):
        if kind == 0x704 and packet(c[16:])[0] == 'CMountedWeaponSelector':
            have = mounted_selector_keys(c, packet)
            allk = have + [k for k in keys if k not in have]
            c = rewrite_packet(c, {('CMountedWeaponSelector', 0): struct.pack('<I', len(allk)) + b''.join(allk)})
        out += c
    return out


def all_god_records(god):
    """Every record (not only each chunk's first) of a GODDATA.DFF, data by key."""
    out = {}
    for kind, c in chunks_of(god):
        if kind == 0x719:
            q = 12
            while q + 28 <= len(c):
                h = struct.unpack_from('<7I', c, q)
                if h[2] <= 0:
                    break
                out.setdefault('%08X,%08X' % (h[4], h[5]), c[q + 28:q + h[2]])
                q += h[2]
    return out


def names_tag(recs, key, tag, depth=3):
    """Whether tag's bytes are in key's record or (depth deep) the records it holds keys of."""
    d = recs.get(key)
    if d is None:
        return False
    if tag in d:
        return True
    if depth:
        for i in range(0, len(d) - 7, 4):
            k = '%08X,%08X' % struct.unpack_from('<2I', d, i)
            if k in recs and k != key and names_tag(recs, k, tag, depth - 1):
                return True
    return False


def vehicle_triggers(pak, god, matrix, y, packet, ahead=2500.0, spacing=1000.0):
    """(god with the sources' chunks added, [trigger chunks], [labels])."""
    have = set(god_records(god)[0])
    extra, picked, cache = [], [], {}
    for label, lv, cls, tag in VEHICLES:
        if lv not in cache:
            g = pak.read('LEVELS\\%s\\GODDATA.DFF' % lv)
            cache[lv] = (g, all_god_records(g), pak.read('LEVELS\\%s\\LEVEL.DFF' % lv))
            for k, c in god_records(g)[0].items():
                if k not in have:
                    have.add(k)
                    extra.append(c)
        g, recs, dff = cache[lv]
        for kind, c in chunks_of(dff):
            if kind != 0x704:
                continue
            ccls, guid, cmds = packet(c[16:])
            model = next((r for o, k, r in cmds if o == 'VehicleTrigger' and k == 2), b'')
            if ccls == cls and len(model) == 8 and names_tag(recs, skey(model), tag):
                picked.append((c, guid, label))
                break
        else:
            print('vehicles: no %s in %s' % (label, lv))
    at, px, pz = matrix[8:11], matrix[12], matrix[14]
    flen = math.hypot(at[0], at[2]) or 1.0
    fx, fz = at[0] / flen, at[2] / flen
    rx, rz = fz, -fx
    out = []
    for i, (c, guid, label) in enumerate(picked):
        off = (i - (len(picked) - 1) / 2.0) * spacing
        pos = (px + fx * ahead + rx * off, y, pz + fz * ahead + rz * off)
        m = struct.pack('<16f', fz, 0, -fx, 0, 0, 1, 0, 0, fx, 0, fz, 0, pos[0], pos[1], pos[2], 1)
        words = [int(w, 16) for w in guid.split('-')]
        out.append(rewrite_packet(c, {('Trigger', 15): struct.pack('<I', 0), ('CSystemCommands', 1): m,
                                      ('VehicleTrigger', 0): bytes(8), ('Trigger', 0): bytes(8),
                                      ('VehicleTrigger', 14): PARKED_TASK, ('VehicleTrigger', 15): bytes(8),
                                      ('VehicleTrigger', 7): struct.pack('<i', 3),
                                      ('Trigger', 14): SPAWN_TASK},
                                  struct.pack('<4I', words[0], words[1], words[2], VEHICLE_LOW + i)))
    guns = []
    for lv, (g, recs, dff) in cache.items():
        guns += [k for k in mounted_selector_keys(dff, packet) if k not in guns]
    return god + b''.join(extra), out, [label for c, guid, label in picked], guns


# Background vehicles (with the vehicles; --no-vehicles leaves them out too): a T-34 and a Sherman
# driving for ever round a 15 m circle ahead and to the side (TRACK_U, TRACK_V, TRACK_R), half
# the loop apart. The track: a spline resource (LEVEL.DFF chunk 0x716: a header of its name,
# 16-byte id, "rwID_SPLINE" and source path, then its data's size and an RpSpline chunk, 0x0C:
# a 32-byte name, its point count and type, 2 a closed loop, then the points; a copy of
# L_1_1_B's own with its id, points and sizes replaced) and a SplinePath entity attaching it
# (CSystemCommands 0, the id) under a name (SplinePath 0: a kind-0x2E name object, a copy of
# L_1_1_B's spline's name record under its own key; SplinePath::HandleAttributes registers the
# path in it, flags 0x80), its mode wrapping (SplinePath 1, unk_1C & 3: 1). Each vehicle: a
# copy of L_2_2's GimpVehicleTrigger (kind 0x23), its model (command 2) the vehicle row's T-34
# or Sherman definition (L_1_2_B's, L_3_3's: their GodData merged), its class script L_1_5's
# gimp vehicles' (command 8; the set-up runs it unchecked: L_2_2's has none), its creation script the
# soldiers' (Trigger 13: BasicCreationTrigger, the port's -leveldir sends it "CreateChild"),
# and a task of its own (command 9, kind 0xC): when it starts, "SetSplinePathFromName" (the
# track's name), "SetSplinePosition" (its start along it), "SetSplineIncrement" (a step a
# 32nd of the loop: type_3DE0E0::vf_03C moves its point on once within 5 m of it) and
# "SetGimpVehicleMoveState" 2 (following its spline). A gimp vehicle (type_3DE0E0, 0x990
# bytes) fits only pool 5, which L_1_1_B leaves at 0 (CPoolSizes command 5): raised.
TRACK_U, TRACK_V, TRACK_R, TRACK_POINTS = 6500.0, 4000.0, 1500.0, 16
TRACK_ID = bytes.fromhex('c0de7aac0000000000000000c0de7aac')
TRACK_NAME = struct.pack('<2I', 0xC0DE7AAC, 1)
GIMP_LOW = 0xC0DE61F0
GIMPS = [('T-34', 'L_1_2_B', b'VT_T34_back', 0.0), ('Sherman', 'L_3_3', b'VTrackL_Sherman', 0.5)]
GIMP_SOURCE, GIMP_CLASS_LEVEL = 'L_2_2', 'L_1_5'
CMD_SETSPLINEPATHFROMNAME, CMD_SETSPLINEPOSITION, CMD_SETSPLINEINCREMENT = 288, 277, 276
CMD_SETGIMPVEHICLEMOVESTATE = 8


def renamed_record(chunk, key8):
    """A copy of a GodData record chunk under the key key8."""
    c = bytearray(chunk)
    c[12 + 16:12 + 24] = key8
    return bytes(c)


def named_records(assets, chunk, key8, text):
    """Copies of a name object's chain under keys of our own, its text ours: the name object
    (chunk: a kind-0x2E record, its data's +4 the key of a reference record, tag 0x10B8, whose
    +4 is the key of a text record, tag 0x0B2010B3, the name; the debugger's ScriptName and
    the game read it through them). The reference's key is key8's second word + 0x100, the
    text's + 0x200. Only key8's copy (the old text kept) when the chain is not that shape."""
    def data(c):
        return c[12 + 28:12 + struct.unpack_from('<I', c, 12 + 8)[0]]
    ref = assets.get(skey(data(chunk)[4:12]))
    txt = ref and assets.get(skey(data(ref)[4:12]))
    if ref is None or txt is None or struct.unpack_from('<I', ref, 12 + 12)[0] != 0x10B8 \
            or struct.unpack_from('<I', txt, 12 + 12)[0] != 0x0B2010B3:
        print('named_records: %s keeps its template\'s name' % text)
        return [renamed_record(chunk, key8)]
    k0, k1 = struct.unpack('<2I', key8)
    ref_key, txt_key = struct.pack('<2I', k0, k1 + 0x100), struct.pack('<2I', k0, k1 + 0x200)
    body = text.encode('ascii') + b'\0'
    body += bytes(-len(body) % 4)
    head = bytearray(txt[12:12 + 28])
    struct.pack_into('<2I', head, 4, 28 + len(body), 28 + len(body))
    head[16:24] = txt_key
    kind, _, ver = struct.unpack_from('<3I', txt)
    txt_out = struct.pack('<3I', kind, 28 + len(body), ver) + bytes(head) + body
    ref_out = bytearray(renamed_record(ref, ref_key))
    ref_out[12 + 28 + 4:12 + 28 + 12] = txt_key
    name_out = bytearray(renamed_record(chunk, key8))
    name_out[12 + 28 + 4:12 + 28 + 12] = ref_key
    return [bytes(name_out), bytes(ref_out), txt_out]


def track_points(matrix, y):
    at, px, pz = matrix[8:11], matrix[12], matrix[14]
    flen = math.hypot(at[0], at[2]) or 1.0
    fx, fz = at[0] / flen, at[2] / flen
    rx, rz = fz, -fx
    cx, cz = px + rx * TRACK_U + fx * TRACK_V, pz + rz * TRACK_U + fz * TRACK_V
    return [(cx + TRACK_R * math.cos(2 * math.pi * i / TRACK_POINTS), y + 10.0,
             cz + TRACK_R * math.sin(2 * math.pi * i / TRACK_POINTS)) for i in range(TRACK_POINTS)]


def track_chunks(level_dff, god, points, packet):
    """(the spline resource chunk, the SplinePath chunk, the name record) for points."""
    res = next(c for kind, c in chunks_of(level_dff) if kind == 0x716 and b'rwID_SPLINE' in c)
    body = res[12:]
    q = 4
    n = struct.unpack_from('<I', body, q)[0]
    q += 4 + n                      # (past the name: its id next)
    head = bytearray(body[:4 + struct.unpack_from('<I', body)[0]])
    head[q:q + 16] = TRACK_ID
    data = bytes(32) + struct.pack('<2i', len(points), 2) + b''.join(struct.pack('<3f', *p) for p in points)
    rw = struct.pack('<3I', 0x0C, len(data), VER) + data
    payload = bytes(head) + struct.pack('<I', len(rw)) + rw
    kind, _, ver = struct.unpack_from('<3I', res)
    res_chunk = struct.pack('<3I', kind, len(payload), ver) + payload
    tmpl = next(c for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[0] == 'SplinePath')
    cmds = {(o, k): raw for o, k, raw in packet(tmpl[16:])[2]}
    words = [int(w, 16) for w in packet(tmpl[16:])[1].split('-')]
    path = rewrite_packet(tmpl, {('CSystemCommands', 0): TRACK_ID, ('SplinePath', 0): TRACK_NAME,
                                 ('SplinePath', 1): struct.pack('<I', 1)},
                          struct.pack('<4I', words[0], words[1], words[2], 0xC0DE7AAC))
    name_rec = renamed_record(god_records(god)[0][skey(cmds['SplinePath', 0][:8])], TRACK_NAME)
    return res_chunk, path, name_rec


def gimp_task(ident, start, name):
    import alfa
    a = alfa.Asm()
    a.wait_message(MSG_INITIALIZE, 1)
    a.push(*struct.unpack('<2I', TRACK_NAME))
    a.command(CMD_SETSPLINEPATHFROMNAME)
    a.push(alfa.f32(start))
    a.command(CMD_SETSPLINEPOSITION)
    a.push(alfa.f32(1.0 / 32))
    a.command(CMD_SETSPLINEINCREMENT)
    a.push(2)
    a.command(CMD_SETGIMPVEHICLEMOVESTATE)
    a.halt()
    return alfa.task_image(ident, a.finish(), name=name)


def gimp_vehicles(pak, god, level_dff, matrix, y, packet, template):
    """(level chunks, god chunks) for the background vehicles and their track; god must hold
    the GIMPS' source levels' GodData (vehicle_triggers adds it)."""
    import alfa
    pts = track_points(matrix, y)
    res_chunk, path, name_rec = track_chunks(level_dff, god, pts, packet)
    tmpl = next(c for kind, c in chunks_of(pak.read('LEVELS\\%s\\LEVEL.DFF' % GIMP_SOURCE))
                if kind == 0x704 and packet(c[16:])[0] == 'GimpVehicleTrigger')
    own_13 = next(raw for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[1] == SOLDIER
                  for o, k, raw in packet(c[16:])[2] if o == 'Trigger' and k == 13)
    words = [int(w, 16) for w in packet(tmpl[16:])[1].split('-')]
    level_out, god_out = [res_chunk, path], [name_rec]
    # (their class script, command 8: L_1_5's, whose GodData is added; the vehicle's set-up,
    # type_3DE0E0::sub_17EA70, runs it unchecked, and L_2_2's has none)
    cls = next(raw for kind, c in chunks_of(pak.read('LEVELS\\%s\\LEVEL.DFF' % GIMP_CLASS_LEVEL))
               if kind == 0x704 and packet(c[16:])[0] == 'GimpVehicleTrigger'
               for o, k, raw in packet(c[16:])[2] if o == 'GimpVehicleTrigger' and k == 8 and any(raw))
    have = set(god_records(god)[0])
    god_out += [c for k, c in god_records(pak.read('LEVELS\\%s\\GODDATA.DFF' % GIMP_CLASS_LEVEL))[0].items()
                if k not in have]
    for i, (label, lv, tag, start) in enumerate(GIMPS):
        recs = all_god_records(pak.read('LEVELS\\%s\\GODDATA.DFF' % lv))
        model = None
        for kind, c in chunks_of(pak.read('LEVELS\\%s\\LEVEL.DFF' % lv)):
            if kind == 0x704 and packet(c[16:])[0] == 'VehicleTrigger':
                m = next((r for o, k, r in packet(c[16:])[2] if o == 'VehicleTrigger' and k == 2), b'')
                if len(m) == 8 and names_tag(recs, skey(m), tag):
                    model = m
                    break
        p = pts[int(start * TRACK_POINTS) % TRACK_POINTS]
        mtx = struct.pack('<16f', 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, p[0], y, p[2], 1)
        key = struct.pack('<2I', GIMP_LOW + i, 0x7A5C)
        god_out.append(alfa.god_record(template, key, gimp_task(TASK_ID + 10 + i, start,
                                                                'TESTFLAT_GimpVehicle_' + re.sub(r'\W', '', GIMPS[i][0]))))
        level_out.append(rewrite_packet(tmpl, {('GimpVehicleTrigger', 2): model, ('GimpVehicleTrigger', 9): key,
                                               ('GimpVehicleTrigger', 8): cls, ('Trigger', 13): own_13,
                                               ('Trigger', 14): SPAWN_TASK,
                                               ('CSystemCommands', 1): mtx},
                                        struct.pack('<4I', words[0], words[1], words[2], GIMP_LOW + i)))
    return level_out, god_out


# The level's own scripts (alfa.py tasks, each a GodData kind-12 record, a copy of the kept
# soldier's task record's header): everything that spawns or fires starts itself, as a level's
# tasks start theirs, with no help from the port.
#  - SPAWN_TASK, every spawner's (Trigger 14, kind 0xC: a task any trigger runs; the pickups',
#    vehicles', background vehicles' and gimps' triggers): when it starts and two seconds on,
#    "CreateChild" (0) queued to its own trigger's script (GetMyAIObjectPointer: the task's
#    owner, the trigger's type_3D2E7C), which its creation script (Trigger 13,
#    BasicCreationTrigger) spawns its child on.
#  - gun_task, each projectile generator's (the artillery and the machine gun): when it starts
#    and a second on, "StartProjectileGenerator" (0) queued to its trigger's script (its class
#    script, ProjectileGeneratorCreation, makes and starts the generator), two seconds on its
#    aim, "PG_TargetPoint" (x, y, z, spread: floats in single player).
SPAWN_TASK = struct.pack('<2I', 0xC0DE5A57, 1)
MSG_CREATECHILD, MSG_STARTPROJECTILEGENERATOR = 78, 6
CMD_PG_TARGETPOINT = 178


def spawn_task(ident, name='TESTFLAT_SpawnChild'):
    import alfa
    a = alfa.Asm()
    a.wait_message(MSG_INITIALIZE, 1)
    _tp_wait(a, 2.0)
    a.queue(MSG_CREATECHILD, [0], CMD_GETMYAIOBJECTPOINTER)
    a.halt()
    return alfa.task_image(ident, a.finish(), name=name)


def gun_task(ident, target, spread, name):
    # (aimed from its first moment and again every tenth of a second for as long as it runs:
    # until a point target, a generator targets by its trigger's mode, ProjectileGeneratorTrigger
    # 10, unk_E4: 1, the nearest enemy, the default, which on the guns' side is the player;
    # PG_TargetPoint does nothing before the class script has made the generator, which may be
    # before the start or well after it, and a point target, once set, is kept (unk_38 2: the
    # shots go to the point with the spread, type_11DB10::vf_024 and type_11E440::vf_024; the
    # entity it held before, unk_24, stays only for the line of sight check))
    import alfa
    a = alfa.Asm()
    a.wait_message(MSG_INITIALIZE, 1)
    a.queue(MSG_STARTPROJECTILEGENERATOR, [0], CMD_GETMYAIOBJECTPOINTER)
    a.label('aim')
    a.push(alfa.f32(target[0]), alfa.f32(target[1]), alfa.f32(target[2]), alfa.f32(spread))
    a.command(CMD_PG_TARGETPOINT)
    a.pop(1)
    _tp_wait(a, 0.1)
    a.jump('aim')
    a.halt()
    return alfa.task_image(ident, a.finish(), name=name)


def task_template(god, level_dff, packet):
    """The kept soldier's task record (a kind-12 record's header for ours)."""
    own = next(raw for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[1] == SOLDIER
               for o, k, raw in packet(c[16:])[2] if o == 'SoldierTrigger' and k == 8)
    return god_records(god)[0].get(skey(own[:8])) or god_records(god)[0][TASK_TEMPLATE]


# The teleport trigger (with the course: course.py's pad, beside the player start): a plain
# Trigger on the pad (a copy of the source level's first Trigger with a task, command 14), a 2 m
# box (Trigger 1 its shape, 2-4 its half sizes) named TP_PAD (Trigger 0: a kind-0x2E name object,
# its record a copy of the template's), its task one of ours (Trigger 14, kind 0xC): when it
# starts, three seconds on (before the player is made IsNamedEntityInTrigger faults), for ever:
# "GetEntityFromName" (the player's name: his script's handle, as the levels' tasks pass it;
# "GetPlayerEntity"'s, his entity table's, faulted) and "IsNamedEntityInTrigger" (that handle,
# TP_PAD: the player in its volume); if so "TeleportNamedObjectToNamedPoint" (the player's name, the
# PlayerTrigger's command 0, to TP_TOP's) and a second's wait; else a tenth's. TP_TOP: a second
# copy, with no task, on the 20 m tower's top (the point the teleport puts the player at: its
# matrix's, 1.3 m up, so he lands on it).
TP_PAD, TP_TOP = struct.pack('<2I', 0xC0DE7E1E, 1), struct.pack('<2I', 0xC0DE7E1E, 2)
TP_TASK = struct.pack('<2I', 0xC0DE7E1E, 3)
TP_LOW = 0xC0DE7E10
CMD_GETENTITYFROMNAME, CMD_ISNAMEDENTITYINTRIGGER, CMD_TELEPORTNAMEDOBJECTTONAMEDPOINT = 146, 193, 101


def teleport_task(ident, player, name='TESTFLAT_TeleportPad'):
    import alfa
    a = alfa.Asm()
    a.wait_message(MSG_INITIALIZE, 1)
    _tp_wait(a, 3.0)                   # (the player is made after the triggers: a handle with no entity faults)
    a.label('loop')
    a.push(*struct.unpack('<2I', player))
    a.command(CMD_GETENTITYFROMNAME)
    a.push(*struct.unpack('<2I', TP_PAD))
    a.command(CMD_ISNAMEDENTITYINTRIGGER)
    a.jz('out')
    a.push(*struct.unpack('<2I', player))
    a.push(*struct.unpack('<2I', TP_TOP))
    a.command(CMD_TELEPORTNAMEDOBJECTTONAMEDPOINT)
    _tp_wait(a, 1.0)
    a.jump('loop')
    a.label('out')
    _tp_wait(a, 0.1)
    a.jump('loop')
    a.halt()
    return alfa.task_image(ident, a.finish(), name=name)


def _tp_wait(a, seconds):
    import alfa
    a.push(alfa.f32(seconds))
    a.push(MSG_GENERICTIMER)
    a.push(0)
    a.command(CMD_REGISTERTIMER)
    a.pop(1)
    a.wait_message(MSG_GENERICTIMER, 0x26)


def teleport_triggers(level_dff, god, pad, top, packet):
    """(level chunks, god chunks): the pad's trigger, the tower top's, their names and the task."""
    import alfa
    tmpl, player, task_tmpl = None, None, None
    for kind, c in chunks_of(level_dff):
        if kind != 0x704:
            continue
        cls, guid, cmds = packet(c[16:])
        d = {(o, k): raw for o, k, raw in cmds}
        if cls == 'Trigger' and tmpl is None and any(d.get(('Trigger', 14), b'')) and any(d.get(('Trigger', 0), b'')):
            tmpl, task_tmpl = c, d['Trigger', 14][:8]
        if cls == 'PlayerTrigger':
            player = d['PlayerTrigger', 0][:8]
    assets = god_records(god)[0]
    tcmds = {(o, k): raw for o, k, raw in packet(tmpl[16:])[2]}
    name_rec = assets[skey(tcmds['Trigger', 0][:8])]
    words = [int(w, 16) for w in packet(tmpl[16:])[1].split('-')]
    out = []
    for i, (pos, name, task) in enumerate(((pad, TP_PAD, TP_TASK), (top, TP_TOP, bytes(8)))):
        h = 100.0 if i == 0 else 130.0
        m = struct.pack('<16f', 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, pos[0], pos[1] + h, pos[2], 1)
        out.append(rewrite_packet(tmpl, {('Trigger', 0): name, ('Trigger', 14): task, ('Trigger', 13): bytes(8),
                                         ('Trigger', 1): struct.pack('<i', 1), ('Trigger', 2): struct.pack('<f', 100.0),
                                         ('Trigger', 3): struct.pack('<f', 100.0), ('Trigger', 4): struct.pack('<f', 100.0),
                                         ('Trigger', 15): struct.pack('<I', 0), ('CSystemCommands', 1): m},
                                  struct.pack('<4I', words[0], words[1], words[2], TP_LOW + i)))
    gods = named_records(assets, name_rec, TP_PAD, 'TP_PAD') + named_records(assets, name_rec, TP_TOP, 'TP_TOP') + [
            alfa.god_record(assets[skey(task_tmpl)], TP_TASK, teleport_task(TASK_ID + 20, player))]
    return out, gods


# The fly pad (course.py's fly_pad, 3 m ahead of the start, the kept soldier 5.5 m ahead facing
# it): a plain Trigger box named FLY_PAD (made as the teleport pad's, no task of its own), and
# the soldier's task (SoldierTrigger 8: on his AI object, so his entity is the one thrown): his
# setup (his own targeting off), then for ever: the player (GetEntityFromName, the PlayerTrigger's
# name) in FLY_PAD's volume (IsNamedEntityInTrigger), then "SendFlying" (300): he flies away from
# the pad's centre, strength FLY_STRENGTH (200 to 1000: a 45 to 65 degree launch, faster for
# more, slower the further he is; type_3DAFC8::sub_13DF40), and six seconds' wait (one flight at a time: he lands first); else a tenth's. SendFlying throws the calling script's entity, a
# soldier or a gimp only ("This entity has no wings!"): the player cannot be thrown so.
FLY_PAD = struct.pack('<2I', 0xC0DEF1E5, 1)
FLY_LOW = 0xC0DEF1E0
FLY_STRENGTH = 1000.0             # (a soldier's most: sub_13DF40 clamps it to 200..1000, flt_429CA8)
CMD_SENDFLYING = 300


def fly_task(ident, player, pad):
    import alfa
    a = alfa.Asm()
    a.wait_message(MSG_INITIALIZE, 1)
    _tp_wait(a, 1.0)
    _setup(a)
    a.label('loop')
    a.push(*struct.unpack('<2I', player))
    a.command(CMD_GETENTITYFROMNAME)
    a.push(*struct.unpack('<2I', FLY_PAD))
    a.command(CMD_ISNAMEDENTITYINTRIGGER)
    a.jz('idle')
    a.push(alfa.f32(pad[0]), alfa.f32(pad[1]), alfa.f32(pad[2]), alfa.f32(FLY_STRENGTH))
    a.command(CMD_SENDFLYING)
    _tp_wait(a, 6.0)
    a.jump('loop')
    a.label('idle')
    _tp_wait(a, 0.1)
    a.jump('loop')
    a.halt()
    return alfa.task_image(ident, a.finish(), name='TESTFLAT_FlyPadSoldier')


def fly_trigger(level_dff, god, pad, packet):
    """(level chunk, god chunks, the player's name): the fly pad's Trigger box and its names."""
    tmpl, player = None, None
    for kind, c in chunks_of(level_dff):
        if kind != 0x704:
            continue
        cls, guid, cmds = packet(c[16:])
        d = {(o, k): raw for o, k, raw in cmds}
        if cls == 'Trigger' and tmpl is None and any(d.get(('Trigger', 14), b'')) and any(d.get(('Trigger', 0), b'')):
            tmpl = c
        if cls == 'PlayerTrigger':
            player = d['PlayerTrigger', 0][:8]
    assets = god_records(god)[0]
    tcmds = {(o, k): raw for o, k, raw in packet(tmpl[16:])[2]}
    words = [int(w, 16) for w in packet(tmpl[16:])[1].split('-')]
    m = struct.pack('<16f', 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, pad[0], pad[1] + 100.0, pad[2], 1)
    chunk = rewrite_packet(tmpl, {('Trigger', 0): FLY_PAD, ('Trigger', 14): bytes(8), ('Trigger', 13): bytes(8),
                                  ('Trigger', 1): struct.pack('<i', 1), ('Trigger', 2): struct.pack('<f', 100.0),
                                  ('Trigger', 3): struct.pack('<f', 100.0), ('Trigger', 4): struct.pack('<f', 100.0),
                                  ('Trigger', 15): struct.pack('<I', 0), ('CSystemCommands', 1): m},
                           struct.pack('<4I', words[0], words[1], words[2], FLY_LOW))
    return chunk, named_records(assets, assets[skey(tcmds['Trigger', 0][:8])], FLY_PAD, 'FLY_PAD'), player


# The course's ladders (course.py's ladder towers): a copy of L_3_1's LadderTrigger (a trigger
# volume only: no model, no commands of its own; Trigger 1 its shape, 2-4 its half sizes, 3 its
# half height, centred on its matrix; LadderTrigger::vf_028, unit_0CAA90.cpp, counts the player
# in it nearer its top than its bottom with no facing test), each its own instance ID, at its
# tower's face, its half height the tower's half plus 25 (so its top is 50 cm above the
# tower's), facing out of the face. L_1_1_B has no ladders.
LADDER_LEVEL = 'L_3_1'
LADDER_LOW = 0xC0DE1AD0


def ladder_triggers(pak, ladders, packet):
    tmpl = next(c for kind, c in chunks_of(pak.read('LEVELS\\%s\\LEVEL.DFF' % LADDER_LEVEL))
                if kind == 0x704 and packet(c[16:])[0] == 'LadderTrigger')
    words = [int(w, 16) for w in packet(tmpl[16:])[1].split('-')]
    out = []
    for i, (pos, (fx, fz), half) in enumerate(ladders):
        m = struct.pack('<16f', fz, 0, -fx, 0, 0, 1, 0, 0, fx, 0, fz, 0, pos[0], pos[1], pos[2], 1)
        out.append(rewrite_packet(tmpl, {('CSystemCommands', 1): m, ('Trigger', 3): struct.pack('<f', half),
                                         ('Trigger', 0): bytes(8)},
                                  struct.pack('<4I', words[0], words[1], words[2], LADDER_LOW + i)))
    return out


# Artillery (--no-artillery leaves it out): copies of the level's first artillery generator
# (ProjectileGeneratorTrigger, kind 0x13, command 22 3: artillery shells; L_1_1_B's own, its
# class script ProjectileGeneratorCreation), ARTILLERY_GUNS of them 90 m ahead of the start and
# 15 m up, across the view, the zone (course.zone, 60 m ahead) between. Their class script makes
# and starts the generator on "StartProjectileGenerator" (state 2, then 3: PG_Manipulate... 2),
# which the port's -leveldir sends at the level's start; then it aims each generator at the zone
# ("PG_TargetPoint": type_1227C0::sub_1218A0) from the level folder's TESTMAP.TXT (a line a gun:
# "aim gx gy gz  x y z spread": the generator standing at gx, gy, gz aims at x, y, z). Their target names (command 11, a named point, unk_F0; 13, a named
# entity, unk_E8) are cleared: the generator's set-up looks them up (type_1227C0::vf_004) and the
# source level's are not on the floor (a null object: it faulted).
ARTILLERY_GUNS = 3
ARTILLERY_SIDE = 1                # (ProjectileGeneratorTrigger 0: 1 its unk_DC 1, the player's side)
ARTILLERY_LOW = 0xC0DEA470
ZONE_V, GUNS_V, GUNS_UP, ZONE_SPREAD = 6000.0, 9000.0, 1500.0, 500.0


def artillery_triggers(level_dff, matrix, y, packet, aims=None, tasks=None):
    tmpl = next((c for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[0] == 'ProjectileGeneratorTrigger'
                 and any(o == 'ProjectileGeneratorTrigger' and k == 22 and raw == struct.pack('<i', 3)
                         for o, k, raw in packet(c[16:])[2])), None)
    if tmpl is None:
        return []
    words = [int(w, 16) for w in packet(tmpl[16:])[1].split('-')]
    at, px, pz = matrix[8:11], matrix[12], matrix[14]
    flen = math.hypot(at[0], at[2]) or 1.0
    fx, fz = at[0] / flen, at[2] / flen
    rx, rz = fz, -fx
    out = []
    for i in range(ARTILLERY_GUNS):
        off = (i - (ARTILLERY_GUNS - 1) / 2.0) * 1500.0
        pos = (px + fx * GUNS_V + rx * off, y + GUNS_UP, pz + fz * GUNS_V + rz * off)
        # (facing back, towards the zone)
        m = struct.pack('<16f', -fz, 0, fx, 0, 0, 1, 0, 0, -fx, 0, -fz, 0, pos[0], pos[1], pos[2], 1)
        if aims is not None:
            aims.append(pos)
        task = struct.pack('<2I', 0xC0DE6A70, i) if tasks is not None else bytes(8)
        if tasks is not None:
            tasks.append(task)
        out.append(rewrite_packet(tmpl, {('CSystemCommands', 1): m, ('Trigger', 0): bytes(8),
                                         ('Trigger', 15): struct.pack('<I', 0), ('Trigger', 14): task,
                                         ('ProjectileGeneratorTrigger', 11): bytes(8),
                                         ('ProjectileGeneratorTrigger', 13): bytes(8),
                                         # (the player's side, 1: until its aim, a generator fires
                                         # at the nearest enemy, the player for L_1_1_B's German
                                         # guns, side 2; on side 1 it finds none and holds fire)
                                         ('ProjectileGeneratorTrigger', 0): struct.pack('<i', ARTILLERY_SIDE)},
                                  struct.pack('<4I', words[0], words[1], words[2], ARTILLERY_LOW + i)))
    return out


# A machine gun range (--no-mg leaves it out): MG_GIMPS of the level's gimps (GimpTrigger, kind
# 0x1F: its background soldiers, a definition, class script and health of their own) in a 2 by 3
# block MG_V ahead and MG_U across, facing the start, and a machine gun 30 m before them, 1.5 m
# up, firing at them: a copy of the level's first projectile generator of no projectile kind
# (command 22 0: bullets with tracers; bursts of 20 to 40), its target names (11, a point; 13, an
# entity) and its parent (4: one to attach to) cleared; the port aims it at the block's centre
# (TESTMAP.TXT's "aim" line). Each gimp: its own instance ID; its name (GimpTrigger 0), level
# task (7: the source level's, which may import its scripts), its path (15: a spline of the source
# level's, which its set-up looks up unchecked, type_3DDB98::sub_1774C0), links (Trigger 15) and trigger
# name (Trigger 0) cleared; its free spawn on (GimpTrigger 23: unk_24_18, past animation pool
# 0's four players, which GimpTrigger::vf_020 otherwise waits for; two came of six); its creation script the soldiers' (Trigger 13: BasicCreationTrigger,
# which the port's -leveldir sends "CreateChild"; their own is the Germans' creation class).
MG_GIMPS, MG_U, MG_V, MG_SPREAD = 6, -7000.0, 4000.0, 300.0
MG_LOW, MG_GIMP_LOW = 0xC0DE3600, 0xC0DE3610
MG_TASK = struct.pack('<2I', 0xC0DE6A70, 0x10)
# (the gun's side: ProjectileGeneratorTrigger 0, 0 its unk_DC 2, 1 its unk_DC 1: its bullets'
# flags, 0x202 or 0x201, type_11DB10::vf_024; L_1_1_B's gun is 0, side 2, and its gimps side 1:
# with 1 the bullets passed through them)
MG_SIDE = 0


def mg_range(level_dff, matrix, y, packet):
    """(level chunks, its target) for the machine gun range, or ([], None)."""
    pg = next((c for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[0] == 'ProjectileGeneratorTrigger'
               and any(o == 'ProjectileGeneratorTrigger' and k == 22 and raw == struct.pack('<i', 0)
                       for o, k, raw in packet(c[16:])[2])), None)
    gimp = next((c for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[0] == 'GimpTrigger'), None)
    if pg is None or gimp is None:
        return [], None
    own_13 = next(raw for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[1] == SOLDIER
                  for o, k, raw in packet(c[16:])[2] if o == 'Trigger' and k == 13)
    at, px, pz = matrix[8:11], matrix[12], matrix[14]
    flen = math.hypot(at[0], at[2]) or 1.0
    fx, fz = at[0] / flen, at[2] / flen
    rx, rz = fz, -fx
    w = lambda u, v, h: (px + rx * u + fx * v, y + h, pz + rz * u + fz * v)
    out = []
    gw = [int(t, 16) for t in packet(gimp[16:])[1].split('-')]
    for i in range(MG_GIMPS):
        u, v = MG_U + (i % 3 - 1) * 300.0, MG_V + (i // 3) * 300.0
        p = w(u, v, 0.0)
        # (facing back towards the start and the gun)
        m = struct.pack('<16f', -fz, 0, fx, 0, 0, 1, 0, 0, -fx, 0, -fz, 0, p[0], p[1], p[2], 1)
        out.append(rewrite_packet(gimp, {('GimpTrigger', 0): bytes(8), ('GimpTrigger', 7): bytes(8),
                                         ('GimpTrigger', 15): bytes(8), ('GimpTrigger', 23): struct.pack('<i', 1),
                                         ('Trigger', 0): bytes(8), ('Trigger', 15): struct.pack('<I', 0),
                                         ('Trigger', 13): own_13, ('Trigger', 14): SPAWN_TASK,
                                         ('CSystemCommands', 1): m},
                                  struct.pack('<4I', gw[0], gw[1], gw[2], MG_GIMP_LOW + i)))
    g = w(MG_U, MG_V - 3000.0, 150.0)
    m = struct.pack('<16f', fz, 0, -fx, 0, 0, 1, 0, 0, fx, 0, fz, 0, g[0], g[1], g[2], 1)
    pw = [int(t, 16) for t in packet(pg[16:])[1].split('-')]
    out.append(rewrite_packet(pg, {('CSystemCommands', 1): m, ('Trigger', 0): bytes(8),
                                   ('Trigger', 15): struct.pack('<I', 0), ('Trigger', 14): MG_TASK,
                                   ('ProjectileGeneratorTrigger', 0): struct.pack('<i', MG_SIDE),
                                   ('ProjectileGeneratorTrigger', 4): bytes(8),
                                   ('ProjectileGeneratorTrigger', 11): bytes(8),
                                   ('ProjectileGeneratorTrigger', 13): bytes(8)},
                              struct.pack('<4I', pw[0], pw[1], pw[2], MG_LOW)))
    t = w(MG_U, MG_V + 150.0, 100.0)
    return out, t


# The death animation gallery: GALLERY_GIMPS gimps in a row 15 m ahead of the start (2 m apart,
# facing it; L_1_1_B's GimpTrigger, as the machine gun range's), each with its own task
# (GimpTrigger 7, unk_D0, kind 0xC: on the gimp's AI object, so the entity it acts on is the
# gimp): for ever, its share of the level's death performances (gimp i the i-th of every
# GALLERY_GIMPS), each played ("SetPerformanceID" 499: plays the performance with that id) and
# printed (PrintInt: codfh.log's "script print"), GALLERY_SECONDS apart. The ids are the level's
# hit-death lookup's (COD_MapData+HitDeathData<level>+Filename, kind 0x12, type_ECDA0::sub_EC750:
# a count, then entries of a data length and four performance ids, a hit's, a death's and the
# partner's two; PlayHitDeathAnim picks one by five hit values, sub_ECA40): the deaths' column.
GALLERY_GIMPS, GALLERY_V, GALLERY_SPACING, GALLERY_SECONDS = 8, 1500.0, 200.0, 4.0
GALLERY_LOW = 0xC0DE6A00
CMD_SETPERFORMANCEID = 499


def hit_death_ids(god, level):
    """The level's death performance ids (its hit-death lookup's second column), sorted."""
    name = 'COD_MapData+HitDeathData%s+Filename' % level if re.match(r'L_\d_\d', level) else \
        'COD_MapData+HitDeathData+Filename'
    key = name_key(name)
    for kind, c in chunks_of(god):
        if kind == 0x719 and len(c) >= 40 and c[28:36] == key:
            d = record_data(c)
            n = struct.unpack_from('<i', d)[0]
            return sorted({struct.unpack_from('<4h', d, 8 + 12 * i)[1] for i in range(n)} - {-1, 0})
    return []


def gallery_task(ident, ids, name):
    import alfa
    a = alfa.Asm()
    a.wait_message(MSG_INITIALIZE, 1)
    _tp_wait(a, 2.0)
    a.label('loop')
    for pid in ids:
        a.push(pid)
        a.command(CMD_SETPERFORMANCEID)
        a.push(pid, pid)
        a.command(CMD_PRINTINT)
        _tp_wait(a, GALLERY_SECONDS)
    a.jump('loop')
    a.halt()
    return alfa.task_image(ident, a.finish(), name=name)


def death_gallery(level_dff, god, course, packet, template, level):
    """(level chunks, god chunks, the ids) for the gallery, or ([], [], [])."""
    import alfa
    ids = hit_death_ids(god, level)
    gimp = next((c for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[0] == 'GimpTrigger'), None)
    if not ids or gimp is None:
        return [], [], []
    own_13 = next(raw for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[1] == SOLDIER
                  for o, k, raw in packet(c[16:])[2] if o == 'Trigger' and k == 13)
    (fx, fz), gw = course.f, [int(t, 16) for t in packet(gimp[16:])[1].split('-')]
    out, gods = [], []
    for i in range(GALLERY_GIMPS):
        p = course.w((i - (GALLERY_GIMPS - 1) / 2.0) * GALLERY_SPACING, GALLERY_V, 0.0)
        # (facing back towards the start)
        m = struct.pack('<16f', -fz, 0, fx, 0, 0, 1, 0, 0, -fx, 0, -fz, 0, p[0], p[1], p[2], 1)
        task = struct.pack('<2I', GALLERY_LOW, i)
        out.append(rewrite_packet(gimp, {('GimpTrigger', 0): bytes(8), ('GimpTrigger', 7): task,
                                         ('GimpTrigger', 15): bytes(8), ('GimpTrigger', 23): struct.pack('<i', 1),
                                         ('Trigger', 0): bytes(8), ('Trigger', 15): struct.pack('<I', 0),
                                         ('Trigger', 13): own_13, ('Trigger', 14): SPAWN_TASK,
                                         ('CSystemCommands', 1): m},
                                  struct.pack('<4I', gw[0], gw[1], gw[2], GALLERY_LOW + 0x10 + i)))
        gods.append(alfa.god_record(template, task, gallery_task(TASK_ID + 80 + i, ids[i::GALLERY_GIMPS],
                                                                 'TESTFLAT_DeathGallery%d' % (i + 1))))
    return out, gods, ids


# The multiplayer view-model animations (ANIMGRPS\MPA_00\MPA_00D.ads: P02-P05, P14 the Luger's,
# P30-P32), which no level's data names: a string asset naming it (a copy of MP_9's "MPA_00C.ads"
# record, one letter changed, its own key) put into the CAnimPackSelector's slot 4 (command 0:
# six string keys, each pack's file name; CAnimPackSelector::HandleEvents loads them),
# L_1_1_B's Lvl_11K.ads (one scene family, I11), which a test level does not need.
MPA_00D_KEY = struct.pack('<2I', 0xC0DEA00D, 0x68E4DA08)

# The other first-person weapon animations (the P families: a weapon's pickup, raise and fire,
# and the sounds their events play) the six packs leave out (P06, P08, P11, P12, P15-P17, P20-P25,
# P28, P29, P38): the multiplayer nation packs holding them, loaded past the six by the port
# (ANIMPACKS.TXT in the level folder, port/src/cli.cpp's port_anim_packs: a bank each after
# CAnimPackSelector's six). The game itself has six slots; no level loads every weapon's.
EXTRA_ANIM_PACKS = ['MPA_00Ger.ads', 'MPA_00US.ads', 'MPA_00Rus.ads', 'MPA_00Brit.ads', 'MPA_00E.ads']
# The sounds those animations' events play (and the multiplayer weapons' own): the multiplayer
# levels' sound banks (CSoundBankSelector command 0: an id, a slot and the bank's number, its
# SB_AWD/SB_AGD files XBX_<number>; a sound finds its wave by the bank's id, sub_840D0), MP_9's
# five and MP_1's nation bank, loaded past the six slots by the port (SOUNDBANKS.TXT,
# port/src/cli.cpp's port_sound_banks)
EXTRA_SOUND_BANKS = [(0xA6FA4330, 0x750E091F, 221), (0x09865CC4, 0x4AB23397, 222), (0x0FE66C2A, 0x3ED71835, 74),
                     (0xAF212204, 0x6E57C042, 111), (0xD5EFE318, 0xB80E84BC, 83), (0xB734A125, 0xB9067F08, 132)]


def mpa_00d(pak):
    assets = god_records(pak.read('LEVELS\\MP_9\\GODDATA.DFF'))[0]
    c = bytearray(assets['3A2B8AD4,68E4DA08'])
    i = c.find(b'MPA_00C.ads')
    assert i > 0, 'MP_9 has no MPA_00C.ads string'
    c[i:i + 11] = b'MPA_00D.ads'
    c[12 + 16:12 + 24] = MPA_00D_KEY
    return bytes(c)


def with_anim_slot(level, slot, key8):
    out = b''
    for kind, c in chunks_of(level):
        if kind == 0x704 and b'CAnimPackSelector\0' in c[12:12 + 200]:
            sys.path.insert(0, SUITE)
            from objects import packet
            raw = next(r for o, k, r in packet(c[16:])[2] if o == 'CAnimPackSelector' and k == 0)
            raw = raw[:slot * 8] + key8 + raw[slot * 8 + 8:]
            c = rewrite_packet(c, {('CAnimPackSelector', 0): raw})
        out += c
    return out


# Entity pool 0's size (CPoolSizes command 0; sub_D5320 makes the nine pools from commands 0-8,
# once): in single player a pickup (kind 0x18, 0x3D0 bytes) takes pool 0 alone, and when it is
# full sacrifices the pickup farthest from the player (sub_D56D0), so L_1_1_B's 30 kept only 23
# of the line's 95. With the pickups it is raised by their count.
def with_pools(level, extra):
    """level's CPoolSizes with extra[command] added to each command's count. Its commands 0-8
    are pools 0, 1, 2, 4, 3, 5, 7, 6, 8 (CPoolSizes::HandleAttributes' fields, in sub_D5320's
    order), of 0x3D0, 0x420, 0x460, 0x5E0, 0x790, 0x9B0, 0x2170, 0x2260 and 0x29D0 bytes
    (dword_3D7130); an entity takes the first free pool its size fits. Command 9 is the script
    tasks' pool (m_taskObjectPool, dword_4498C8: 125 by default, 0x124 bytes each; a task past
    it faults in sub_71B90's allocation)."""
    out = b''
    for kind, c in chunks_of(level):
        if kind == 0x704 and b'CPoolSizes\0' in c[12:12 + 200]:
            sys.path.insert(0, SUITE)
            from objects import packet
            cmds = {k: r for o, k, r in packet(c[16:])[2] if o == 'CPoolSizes'}
            c = rewrite_packet(c, {('CPoolSizes', k): struct.pack('<i', struct.unpack('<i', cmds[k])[0] + n)
                                   for k, n in extra.items()})
        out += c
    return out


def with_selector(level, keys):
    """level's CPickupSelector given the settings keys (its command 0: a count, then keys)."""
    out = b''
    for kind, c in chunks_of(level):
        if kind == 0x704 and b'CPickupSelector\0' in c[12:12 + 200]:
            c = rewrite_packet(c, {('CPickupSelector', 0): struct.pack('<I', len(keys)) + b''.join(keys)})
        out += c
    return out


# Commands zeroed in place (god-asset keys: a zero key asks for nothing), by entity class and
# the command's owner: the source level's intro.
CLEAR = {
    # its script task (command 21, kind 12; PlayerTrigger::HandleAttributes, unit_0A9980.cpp):
    # the source level's mission script (L_1_1_B's: it finds the level's named entities, spawns
    # its squads and locks the player's movement; its class, command 20, sets the player up and
    # is kept)
    'PlayerTrigger': ('PlayerTrigger', (21,)),
    # the level's intro and outro movies (commands 6 and 7: sub_E8DB0 / sub_E8E30,
    # unit_0B6EB0.cpp; played by sub_E8910 / sub_E89E0)
    'CShellLevelBehaviorClass': ('CShellLevelBehaviorClass', (6, 7)),
}
# With --no-script, more: the kept soldier's creation script (Trigger command 13: the port's
# -patrol spawns it instead) and its own task (SoldierTrigger command 8: its level part, importing
# that level's sets and tasks, which a level with only it never answers). Command 7, every
# soldier's shared class, is kept: without it the spawn faults. Without --no-script its creation
# script is kept (BasicCreationTrigger: -leveldir's "CreateChild" spawns it) and command 8 is
# the patrol task written here (patrol_task).
CLEAR_NO_SCRIPT = {'SoldierTrigger': [('Trigger', (13,)), ('SoldierTrigger', (8,))]}

# The soldier trigger kept for -patrol (L_1_1_B's "Sgt. Puskov", a friendly), by instance ID.
SOLDIER = 'F7956219-4C3E0D0E-08011FA3-297B6267'
SOLDIER_NAME = 'debugging.games'
# Its weapon (SoldierTrigger command 38: a CNPCWeaponBehavior's key and a word, as other
# levels' soldiers carry it; the key picks the NPC weapon table's entry, sub_15CB40): slot 2, one
# of the two with the projectile flag (command 28: projectile kind 3, sub_15CCA0). Only with
# --bazooka: armed with it he takes a goto (AI state 2) but never moves (the level's animation
# packs have no rocket launcher walk, it seems), so the patrol keeps his own weapon.
SOLDIER_WEAPON = bytes.fromhex('bc1229293d6b44fa0f000000')


def clear_intro(data, no_script=False):
    out = bytearray(data)
    rules = list(CLEAR.items())
    if no_script:
        rules += [(cls, r) for cls, rs in CLEAR_NO_SCRIPT.items() for r in rs]
    p = 0
    while p + 12 <= len(out):
        kind, size, _ = struct.unpack_from('<3I', out, p)
        for cls, (owner_of, keys) in rules:
            if kind == 0x704 and (cls.encode() + b'\0') in out[p + 12:p + 12 + 200]:
                q, end, owner = p + 16, p + 12 + size, ''
                while q + 8 <= end:
                    n, k = struct.unpack_from('<2I', out, q)
                    if n == 0:
                        break
                    if k == 0x80000000:
                        owner = bytes(out[q + 8:q + n]).split(b'\0', 1)[0].decode('cp1252')
                    elif owner == owner_of and k in keys:
                        out[q + 8:q + n] = bytes(n - 8)
                    q += n
        p += 12 + size
    return bytes(out)


class Pak:
    """COD.PAK (unit_16C800.cpp): a 0x80-byte header (the file count at +0x7C), then 16-byte
    entries (size, offset, the path's 64-bit FNV-1 hash, upper-cased, basis halves swapped)."""

    def __init__(self, path):
        self.f = open(path, 'rb')
        head = self.f.read(0x80)
        n = struct.unpack_from('<I', head, 0x7C)[0]
        table = self.f.read(n * 16)
        self.entries = {}
        for i in range(n):
            size, off, key = struct.unpack_from('<IIQ', table, i * 16)
            self.entries[key] = (size, off)

    @staticmethod
    def key(path):
        v = 0x84222325CBF29CE4
        for c in path.upper().replace('/', '\\').encode():
            v = (v * 0x100000001B3) & 0xFFFFFFFFFFFFFFFF
            v ^= c
        return v

    def read(self, path):
        size, off = self.entries[self.key(path)]
        self.f.seek(off)
        return self.f.read(size)


def without_clones(data):
    """LEVEL.RWS's section records (kind, size, data; 11 ends: sub_142F70) without the level's
    scenery: its clones (records 7, the clone file, and 15, their clump) and its skybox worlds
    (8 and 9). Kept: the UV animation and texture dictionaries (5, 6, 10, 17), the tables (16,
    18) and the arena split (13)."""
    out, p = b'', 0
    while p + 4 <= len(data):
        kind = struct.unpack_from('<I', data, p)[0]
        if kind == 11:
            return out + data[p:p + 4]
        size = struct.unpack_from('<I', data, p + 4)[0]
        if kind not in (7, 8, 9, 15):
            out += data[p:p + 8 + size]
        p += 8 + size
    return out


def player_position(data):
    sys.path.insert(0, SUITE)
    from objects import Objects
    o = Objects()
    p = 0
    while p + 12 <= len(data):
        kind, size, _ = struct.unpack_from('<3I', data, p)
        if kind in (0x704, 0x705, 0x70d, 0x70e, 0x71b):
            o.read(kind, data[p + 12:p + 12 + size], 'level.dff')
        p += 12 + size
    for obj in o.finish([]):
        if obj['class'] == 'PlayerTrigger' and obj['position']:
            return obj['position'], obj['matrix']
    raise SystemExit('no PlayerTrigger position in the source level')


# The patrol task (alfa.py): its key and id, a task of L_1_1_B's (Puskov's own, the template for
# its GodData record), and the level's message and command numbers (its symbols: the web
# suite's output/L_1_1_B/symbols.json) it uses.
TASK_KEY = struct.pack('<2I', 0xC0DE7A5C, 0x00000001)
TASK_ID = 0xC0DE
TASK_TEMPLATE = 'EC9F6A20,8094E3DD'
MSG_INITIALIZE, MSG_GENERICTIMER, MSG_GOTOPOINT = 67, 132, 93
CMD_REGISTERTIMER, CMD_GETMYAIOBJECTPOINTER = 171, 542
CMD_PRINTINT = 167


def patrol_points(matrix, y, ahead=500.0, side=400.0):
    """The two points the soldier walks between: ahead of the player start's view, either side."""
    at, px, pz = matrix[8:11], matrix[12], matrix[14]
    flen = math.hypot(at[0], at[2]) or 1.0
    fx, fz = at[0] / flen, at[2] / flen
    rx, rz = fz, -fx
    return [(px + fx * ahead + rx * s, y, pz + fz * ahead + rz * s) for s in (-side, side)]


def patrol_task(points, seconds=6.0, trace=False):
    """The soldier's task: when it starts (Initialize), for ever: to the second point, a wait, to
    the first, a wait. Each leg is "SetTaskCommand_GoToPoint" (x, y, z, 0) queued to its own AI
    object (GetMyAIObjectPointer), which its class (SoldierClass) walks; each wait a GenericTimer
    (RegisterTimer seconds, GenericTimer, 0; then waiting for it from itself). The first leg
    waits a second after Initialize: his class takes a goto only once it is up (state 1's
    field_8), and drops one sent before. trace: PrintInt marks (1, 2, then 10/20/30 + the leg)."""
    import alfa
    a = alfa.Asm()
    def mark(n):
        if trace:
            a.push(n, n)
            a.command(CMD_PRINTINT)
    def wait(t):
        a.push(alfa.f32(t))
        a.push(MSG_GENERICTIMER)
        a.push(0)
        a.command(CMD_REGISTERTIMER)
        a.pop(1)
        a.wait_message(MSG_GENERICTIMER, 0x26)
    mark(1)
    a.wait_message(MSG_INITIALIZE, 1)
    _setup(a)                          # (his goto taken at once, his own targeting off)
    mark(2)
    wait(1.0)                          # (his class takes a goto only once it is up)
    a.label('loop')
    for leg, (x, y, z) in enumerate((points[1], points[0])):
        mark(10 + leg)
        a.queue(MSG_GOTOPOINT, [alfa.f32(x), alfa.f32(y), alfa.f32(z), 0], CMD_GETMYAIOBJECTPOINTER)
        mark(20 + leg)
        mark(30 + leg)
        wait(seconds)
    a.jump('loop')
    a.halt()
    return alfa.task_image(TASK_ID, a.finish(), name='TESTFLAT_SoldierPatrol')


def with_soldier(level, edits):
    """level with the kept soldier trigger's commands replaced (edits: (owner, command): bytes)."""
    sys.path.insert(0, SUITE)
    from objects import packet
    out = []
    for kind, c in chunks_of(level):
        if kind == 0x704 and packet(c[16:])[1] == SOLDIER:
            c = rewrite_packet(c, edits)
        out.append(c)
    return b''.join(out)


# The setup L_1_3_A's rocket soldiers' tasks begin with (god_BC96F8B7_BAA71723 and the rest),
# after Initialize: SoldierClass's function_37 (state 0: a switch on its first argument) with (0,
# 1), its field_8, which its task commands (state 1's SetTaskCommand_* handlers) need before
# they act (without it they are kept and wait); (5, 0), its own targeting off (AI flag 32, its
# target cleared); (4, 0), AI flag 16 off; (6, 0), AI flag 64 off; then "SetParameter" (0, 0)
# and (1, 0), appended.
MSG_SETPARAMETER, FN_SOLDIER_SET = 79, 37
SOLDIER_SETUP = ((0, 1), (5, 0), (4, 0), (6, 0))


def _setup(a):
    for args in SOLDIER_SETUP:
        a.function(FN_SOLDIER_SET, list(args), CMD_GETMYAIOBJECTPOINTER)
    for n in (0, 1):
        a.queue(MSG_SETPARAMETER, [n, 0], CMD_GETMYAIOBJECTPOINTER, append=True)


# The scripts the level does not use: class, state-machine and function images (Alfa images,
# kinds 2-4: data "A\0\0" then the kind) in single-record god-asset chunks (0x719, events 8
# and 9) that no key reaches. The roots are every 8 bytes of LEVEL.DFF, every non-script
# record and every other chunk (the level directory, path nodes, particles and object lists);
# a reached script's own bytes (its imports: keys) reach more. GodData is read by request: a
# trigger, a class or an import asks for a script by its key, and the game itself by name
# (NAMED_SCRIPTS, sub_D8A40's requests at the level start: their keys name_key's). Most of what
# this drops are the functions of the other levels whose god data pickup_assets and
# vehicle_triggers merge. The event scripts (kind 1: the list chunk, event 20) are kept:
# nothing names them by key.
NAMED_SCRIPTS = ['Scripts+TaskList+ScriptedSequence+Filename', 'Scripts+ClassList+PlayerClass+Filename']


def name_key(name):
    """A god asset's key from its name (sub_198A20): the name quoted (each '+' too), upper-cased,
    its even and its odd characters each hashed (FNV-1, sub_16C800)."""
    def fnv(text):
        h = 0x811C9DC5
        for c in text.encode():
            h = (h * 0x1000193 & 0xFFFFFFFF) ^ c
        return h
    q = ('"' + name.replace('+', '"+"') + '"').upper()
    return struct.pack('<2I', fnv(q[0::2]), fnv(q[1::2]))


def without_unused_scripts(god, level):
    def is_script(d):
        return len(d) >= 4 and d[:3] == b'A\0\0' and d[3] in (2, 3, 4)

    rows = []           # (chunk, its script record's key or None)
    data = {}           # key -> the records' data with that key
    roots = [level] + [name_key(n) for n in NAMED_SCRIPTS]
    for kind, c in chunks_of(god):
        key = None
        if kind == 0x719 and len(c) >= 12 + 28:
            ev, _, size = struct.unpack_from('<3I', c, 12)
            d = c[12 + 28:12 + size]
            if ev in (8, 9) and 12 + size == len(c) and is_script(d):
                key = c[12 + 16:12 + 24]
                data.setdefault(key, []).append(d)
        if key is None:
            roots.append(c)
        rows.append((c, key))
    keys = set(data)

    def refs(b):
        return {b[i:i + 8] for i in range(0, len(b) - 7, 4)} & keys

    seen, todo = set(), set()
    for b in roots:
        todo |= refs(b)
    while todo:
        k = todo.pop()
        seen.add(k)
        for d in data[k]:
            todo |= refs(d) - seen
    kept = b''.join(c for c, key in rows if key is None or key in seen)
    print('scripts: kept %d of %d class, machine and function scripts (%d KB of GodData dropped)' % (
        len(seen), len(keys), (len(god) - len(kept)) // 1024))
    return kept


# The release builds' scripts have no names (an empty string at their name offset, +4 from +4:
# kinds 2-4); the two debug builds', L_1_5_B's and L_3_1's, name theirs ("SoldierAnim",
# "QS_StartIdle"). Each of our level's unnamed scripts whose key one of them names gets that
# name: the string at the image's end (where the debug builds keep it), the offset pointed at
# it, the record's and the chunk's sizes grown. Only the name: the debug builds' code differs.
DEBUG_LEVELS = ['L_1_5_B', 'L_3_1']


def image_name(d):
    at = 4 + struct.unpack_from('<i', d, 4)[0]
    return d[at:d.index(0, at)] if 4 < at < len(d) else b''


def with_debug_names(god, pak):
    def scripts(data):
        for kind, c in chunks_of(data):
            if kind == 0x719 and len(c) >= 12 + 28:
                ev, _, size = struct.unpack_from('<3I', c, 12)
                d = c[12 + 28:12 + size]
                if ev in (8, 9) and 12 + size == len(c) and len(d) >= 8 and d[:3] == b'A\0\0' and d[3] in (2, 3, 4):
                    yield c, c[12 + 16:12 + 24], d
                    continue
            yield c, None, None

    names = {}
    for lv in DEBUG_LEVELS:
        for c, key, d in scripts(pak.read('LEVELS\\%s\\GODDATA.DFF' % lv)):
            if key is not None and image_name(d):
                names.setdefault(key, image_name(d))
    out, n = [], 0
    for c, key, d in scripts(god):
        if key is None:
            out.append(c)
        elif not image_name(d) and key in names:
            img = bytearray(d) + bytes(-len(d) % 4)
            struct.pack_into('<i', img, 4, len(img) - 4)
            img += names[key] + b'\0'
            img += b'\xcc' * (-len(img) % 4)
            head = bytearray(c[12:12 + 28])
            if struct.unpack_from('<I', head, 4)[0] == 28 + len(d):
                struct.pack_into('<I', head, 4, 28 + len(img))
            struct.pack_into('<I', head, 8, 28 + len(img))
            kind, _, ver = struct.unpack_from('<3I', c)
            out.append(struct.pack('<3I', kind, 28 + len(img), ver) + bytes(head) + bytes(img))
            n += 1
        else:
            out.append(c)
    print('debug names: %d of our scripts named from %s' % (n, ', '.join(DEBUG_LEVELS)))
    return b''.join(out)


# The generator's own source file in the level's script symbols (GLOBAL.DFF's Alfa data image,
# the symbols: sub_67E30 loads it): its file table (+0x2C its count, +0x30 its offset from +4,
# each entry an offset from the table; turned into pointers at load) and its names copied to
# the image's end with SOURCE_FILE added, the resource's sizes grown. Its index is our scripts' line words' file
# (alfa.LINE_FILE), as the debug builds' scripts name theirs ("S:/COD/Game/GameData/Scripts/...").
SOURCE_FILE = 'C:/codfh-win32/tools/testmap/make_flat.py'


def with_source_file(global_dff, path):
    """(GLOBAL.DFF with path in its symbols' file table, path's index), or (it, None)."""
    out, p, index = bytearray(), 0, None
    for kind, c in chunks_of(global_dff):
        if kind == 0x716 and index is None:
            hs = struct.unpack_from('<I', c, 12)[0]
            h_end = 16 + hs
            q, strings = 16, []
            for _ in range(4):          # name, (the GUID after it), type, filename, location
                n = struct.unpack_from('<I', c, q)[0]
                strings.append(c[q + 4:q + 4 + n].split(b'\0')[0])
                q += 4 + n + (16 if not strings[1:] else 0)
            size = struct.unpack_from('<I', c, h_end)[0]
            img = bytearray(c[h_end + 4:h_end + 4 + size])
            if strings[1] == b'spID_AlfaDataFile' and len(img) >= 52:
                count, rel = struct.unpack_from('<2I', img, 44)
                table = 4 + rel
                names = [bytes(img[e:img.index(0, e)]) for e in
                         (table + struct.unpack_from('<I', img, table + 4 * i)[0] for i in range(count))]
                names.append(path.encode('ascii'))
                img += bytes(-len(img) % 4)
                new_table = len(img)
                texts, at = b'', 4 * len(names)        # (the names copied after it: offsets stay positive)
                for n in names:
                    img += struct.pack('<I', at + len(texts))
                    texts += n + b'\0'
                img += texts + bytes(-len(texts) % 4)
                struct.pack_into('<2I', img, 44, count + 1, new_table - 4)
                body = c[12:h_end] + struct.pack('<I', len(img)) + bytes(img) + c[h_end + 4 + size:]
                c = struct.pack('<3I', kind, len(body), struct.unpack_from('<I', c, 8)[0]) + body
                index = count
        out += c
    return bytes(out), index


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('out')
    ap.add_argument('--level', default='L_1_1_B', help="the source level (the -map level's folder)")
    ap.add_argument('--pak', default=r'D:\CODFH_DUMP\COD.PAK', help="the data root's COD.PAK")
    ap.add_argument('--size', type=float, default=20000.0, help='floor width in units (cm)')
    ap.add_argument('--cells', type=int, default=10, help='checkerboard cells a side (drawn only)')
    ap.add_argument('--no-pickups', action='store_true', help='leave out the line of every pickup')
    ap.add_argument('--no-course', action='store_true', help='leave out the movement course and its ladders (course.py)')
    ap.add_argument('--no-artillery', action='store_true', help='leave out the artillery and its zone')
    ap.add_argument('--no-mg', action='store_true', help='leave out the machine gun range (gimps and a machine gun)')
    ap.add_argument('--gallery', action='store_true', help='add the death animation gallery (8 gimps playing every death)')
    ap.add_argument('--no-vehicles', action='store_true', help='leave out the row of every kind of vehicle')
    ap.add_argument('--no-extra-anims', action='store_true',
                    help="no ANIMPACKS.TXT or SOUNDBANKS.TXT: only the packs and banks the game loads "
                         "(most picked-up weapons unanimated and silent)")
    ap.add_argument('--no-mp-anims', action='store_true',
                    help="leave out the multiplayer view-model animations (MPA_00D.ads: the Luger's)")
    ap.add_argument('--bazooka', action='store_true',
                    help="arm the soldier with the rocket launcher (for the port's -shoot; he cannot walk with it)")
    ap.add_argument('--trace', action='store_true', help="the task prints its steps (PrintInt: codfh.log's 'script print')")
    ap.add_argument('--source-graph', action='store_true', help="keep the source level's path-node graph")
    ap.add_argument('--keep-scripts', action='store_true',
                    help="keep every script of the source levels' god data, used or not")
    ap.add_argument('--patrol', action='store_true',
                    help="the kept soldier patrols ahead of the start (the patrol task) instead of standing by the fly pad")
    ap.add_argument('--no-script', action='store_true',
                    help="no patrol task: the soldier's scripts cleared, for the port's -patrol / -shoot")
    a = ap.parse_args()
    out = pathlib.Path(a.out)
    pak = Pak(a.pak)
    src = lambda name: pak.read('LEVELS\\%s\\%s' % (a.level, name))
    (out / 'SECTIONS').mkdir(parents=True, exist_ok=True)
    level_dff = src('LEVEL.DFF')
    (x, y, z), matrix = player_position(level_dff)
    level, kept, _ = filter_level(level_dff, a.bazooka)
    level = clear_intro(level, a.no_script)
    god = src('GODDATA.DFF')
    import alfa
    global_dff, alfa.LINE_FILE = with_source_file(src('GLOBAL.DFF'), SOURCE_FILE)
    print("debug information: our scripts' lines, file %s (GLOBAL.DFF's file table)" % alfa.LINE_FILE)
    # (the PlayerTrigger's position is the player's frame, at standing eye height, 120, above
    # the feet: unit_0FD730.cpp's unk_434.y = unk_1A00 + feet; the level's own floor under
    # L_1_1_B's start is 120 below it)
    y -= 120.0
    if not a.no_pickups:
        sys.path.insert(0, SUITE)
        from objects import packet
        god, by_id = pickup_assets(pak, a.level, level_dff, god, packet)
        level = with_selector(level, [by_id[i] for i in sorted(by_id)])
        level += pickup_triggers(level_dff, by_id, matrix, y, packet)
        level = with_pools(level, {0: len(by_id)})
        print('pickups: %d ids in a line: %s' % (len(by_id), ' '.join(map(str, sorted(by_id)))))
    if not a.no_vehicles:
        sys.path.insert(0, SUITE)
        from objects import packet
        god, chunks, labels, guns = vehicle_triggers(pak, god, matrix, y, packet)
        level += b''.join(chunks)
        level = with_mounted_selector(level, guns, packet)
        level = with_pools(level, {8: len(chunks), 4: 3 * len(chunks)})
        print('vehicles: %d in a row 25 m ahead: %s' % (len(chunks), ', '.join(labels)))
        own8 = next(raw for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[1] == SOLDIER
                    for o, k, raw in packet(c[16:])[2] if o == 'SoldierTrigger' and k == 8)
        template = god_records(god)[0].get(skey(own8[:8])) or god_records(god)[0][TASK_TEMPLATE]
        lchunks, gchunks = gimp_vehicles(pak, god, level_dff, matrix, y, packet, template)
        level += b''.join(lchunks)
        god += b''.join(gchunks)
        level = with_pools(level, {5: len(GIMPS)})
        print('background vehicles: %s round a 15 m track' % ', '.join(g[0] for g in GIMPS))
    if not a.no_mp_anims:
        god += mpa_00d(pak)
        level = with_anim_slot(level, 4, MPA_00D_KEY)
        print('animation pack slot 4: MPA_00D.ads (the multiplayer view models: the Luger)')
    sys.path.insert(0, str(pathlib.Path(__file__).parent))
    sys.path.insert(0, SUITE)
    import course as course_mod
    at = matrix[8:11]
    flen = math.hypot(at[0], at[2]) or 1.0
    course = course_mod.Course(x, y, z, at[0] / flen, at[2] / flen)
    if not a.no_script:
        import alfa
        pts = patrol_points(matrix, y)
        from objects import packet
        own = next(raw for kind, c in chunks_of(level_dff) if kind == 0x704 and packet(c[16:])[1] == SOLDIER
                   for o, k, raw in packet(c[16:])[2] if o == 'SoldierTrigger' and k == 8)
        template = god_records(god)[0].get(skey(own[:8])) or god_records(god)[0][TASK_TEMPLATE]
        if a.patrol:
            god += alfa.god_record(template, TASK_KEY, patrol_task(pts, trace=a.trace))
            # (its trigger at the first point, facing the second: its matrix, CSystemCommands 1)
            at_pt, dx, dz = pts[0], pts[1][0] - pts[0][0], pts[1][2] - pts[0][2]
        else:
            pad, at_pt = course.fly_pad()
            chunk, gchunks, player = fly_trigger(level_dff, god, pad, packet)
            level += chunk
            god += b''.join(gchunks)
            god += alfa.god_record(template, TASK_KEY, fly_task(TASK_ID + 70, player, pad))
            at_pt = (at_pt[0], y, at_pt[2])
            # (facing the pad)
            dx, dz = pad[0] - at_pt[0], pad[2] - at_pt[2]
        n = math.hypot(dx, dz) or 1.0
        fx, fz = dx / n, dz / n
        m = struct.pack('<16f', fz, 0, -fx, 0, 0, 1, 0, 0, fx, 0, fz, 0, at_pt[0], at_pt[1], at_pt[2], 1)
        # (his spawner, Trigger 13 BasicCreationTrigger, made to spawn him: the SpawnChild task)
        level = with_soldier(level, {('SoldierTrigger', 8): TASK_KEY, ('Trigger', 14): SPAWN_TASK,
                                     ('CSystemCommands', 1): m})
        if a.patrol:
            print('patrol task: the soldier walks (%.0f, %.0f) <-> (%.0f, %.0f)' % (pts[0][0], pts[0][2], pts[1][0],
                                                                                pts[1][2]))
        else:
            print('fly pad: a trigger 3 m ahead; the soldier 5.5 m ahead is sent flying (SendFlying %.0f) '
                  'when the player steps in' % FLY_STRENGTH)
    sys.path.insert(0, str(pathlib.Path(__file__).parent))
    sys.path.insert(0, SUITE)
    import alfa
    from objects import packet
    ttmpl = task_template(god, level_dff, packet)
    god += alfa.god_record(ttmpl, SPAWN_TASK, spawn_task(TASK_ID + 30))
    god += alfa.god_record(ttmpl, PARKED_TASK, parked_task(TASK_ID + 60))
    if not a.source_graph:
        graph, nodes = path_graph(x, y, z, a.size)
        god = with_path_graph(god, graph)
        print('path nodes: %d on the floor (the source level graph replaced)' % nodes)
    (out / 'GLOBAL.DFF').write_bytes(global_dff)
    (out / 'LEVEL.RWS').write_bytes(without_clones(src('LEVEL.RWS')))
    from objects import packet
    if not a.no_course:
        course.build()
        print('movement course: %d collision triangles behind the player start (course.py)'
              % len(course.collision()[1]))
        if course.pad and course.drop_tops:
            pchunks, gchunks = teleport_triggers(level_dff, god, course.pad, course.drop_tops[-1], packet)
            level += b''.join(pchunks)
            god += b''.join(gchunks)
            print('teleport: a trigger on the pad to the 20 m tower (its task: IsNamedEntityInTrigger, '
                  'TeleportNamedObjectToNamedPoint)')
        chunks = ladder_triggers(pak, course.ladders, packet)
        level += b''.join(chunks)
        print('ladders: %d LadderTriggers (%s\'s) on the ladder towers' % (len(chunks), LADDER_LEVEL))
    if not a.no_artillery:
        guns, tasks = [], []
        chunks = artillery_triggers(level_dff, matrix, y, packet, guns, tasks)
        if chunks:
            level += b''.join(chunks)
            zone = course.zone(0.0, ZONE_V)
            god += b''.join(alfa.god_record(ttmpl, t, gun_task(TASK_ID + 40 + i, zone, ZONE_SPREAD,
                                                                         'TESTFLAT_Artillery%d' % (i + 1)))
                            for i, t in enumerate(tasks))
            print('artillery: %d generators 90 m ahead, aimed at the zone 60 m ahead' % len(chunks))
        else:
            print('artillery: %s has no artillery generator' % a.level)
    if a.gallery:
        chunks, gchunks, ids = death_gallery(level_dff, god, course, packet, ttmpl, a.level)
        if chunks:
            level += b''.join(chunks)
            god += b''.join(gchunks)
            course.text(0.0, GALLERY_V + 250.0, 'DEATHS', 14.0)
            print('death gallery: %d gimps 15 m ahead, %d death performances, %.0f s each (%d to %d)'
                  % (len(chunks), len(ids), GALLERY_SECONDS, ids[0], ids[-1]))
        else:
            print('death gallery: %s has no gimp or hit-death lookup' % a.level)
    if not a.no_mg:
        chunks, target = mg_range(level_dff, matrix, y, packet)
        if chunks:
            level += b''.join(chunks)
            god += alfa.god_record(ttmpl, MG_TASK, gun_task(TASK_ID + 50, target, MG_SPREAD, 'TESTFLAT_MachineGun'))
            course.text(MG_U, MG_V - 400.0, 'MG RANGE', 14.0)
            print('machine gun range: %d gimps, a machine gun 30 m before them' % (len(chunks) - 1))
        else:
            print('machine gun range: %s has no gimp or machine gun generator' % a.level)
    # (the script tasks: a SpawnChild task for each spawner, the guns', the teleport's and the
    # vehicles' own, past the 125 the level's CPoolSizes allows)
    level = with_pools(level, {9: TASK_POOL_EXTRA})
    (out / 'LEVEL.DFF').write_bytes(level)
    if not a.keep_scripts:
        god = without_unused_scripts(god, level)
    god = with_debug_names(god, pak)
    (out / 'GODDATA.DFF').write_bytes(god)
    if not a.no_extra_anims:
        (out / 'ANIMPACKS.TXT').write_text('# extra animation packs (the port loads them past the six; make_flat.py)\n'
                                           + ''.join(n + '\n' for n in EXTRA_ANIM_PACKS))
        print('extra animation packs: %s (ANIMPACKS.TXT)' % ', '.join(EXTRA_ANIM_PACKS))
        (out / 'SOUNDBANKS.TXT').write_text('# extra sound banks: id, number (the port loads them past the six; '
                                            'make_flat.py)' + chr(10)
                                            + ''.join('%08X %08X %d' % b + chr(10) for b in EXTRA_SOUND_BANKS))
        print('extra sound banks: %s (SOUNDBANKS.TXT)' % ', '.join('XBX_%04d' % b[2] for b in EXTRA_SOUND_BANKS))
    else:
        for name in ('ANIMPACKS.TXT', 'SOUNDBANKS.TXT'):
            if (out / name).exists():
                (out / name).write_text('')
    (out / 'SECTIONS' / 'S_1.RWS').write_bytes(floor(x, y, z, a.size, a.cells, course))
    print('player start (%.0f, %.0f, %.0f); floor %.0f wide, %d cells' % (x, y, z, a.size, a.cells))
    print('kept %d entities: %s' % (len(kept), ', '.join(sorted(set(kept)))))
    print('wrote', out)


if __name__ == '__main__':
    main()
