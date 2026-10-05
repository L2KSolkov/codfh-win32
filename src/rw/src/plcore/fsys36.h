/*
 * codfh-match: RenderWare 3.6's file access goes through RwGlobals' file
 * function table (fileFuncs, filled by sub_2AB700 in unit_2AB6C0.c), not
 * the 3.7 file system toolkit (rtfsyst): the image's streams, image loader
 * and 2D fonts call through 0x5201A4 ... 0x5201CC.
 */
#ifndef FSYS36_H
#define FSYS36_H

#define RwFexist(_name)          (RWSRCGLOBAL(fileFuncs).rwfexist((_name)))
#define RwFopen(_name, _access)  (RWSRCGLOBAL(fileFuncs).rwfopen((_name), (_access)))
#define RwFclose(_fptr)          (RWSRCGLOBAL(fileFuncs).rwfclose((_fptr)))
#define RwFread(_addr, _size, _count, _fptr) \
    (RWSRCGLOBAL(fileFuncs).rwfread((_addr), (_size), (_count), (_fptr)))
#define RwFwrite(_addr, _size, _count, _fptr) \
    (RWSRCGLOBAL(fileFuncs).rwfwrite((_addr), (_size), (_count), (_fptr)))
#define RwFgets(_buffer, _maxLen, _fptr) \
    (RWSRCGLOBAL(fileFuncs).rwfgets((_buffer), (_maxLen), (_fptr)))
#define RwFputs(_buffer, _fptr)  (RWSRCGLOBAL(fileFuncs).rwfputs((_buffer), (_fptr)))
#define RwFeof(_fptr)            (RWSRCGLOBAL(fileFuncs).rwfeof((_fptr)))
#define RwFseek(_fptr, _offset, _origin) \
    (RWSRCGLOBAL(fileFuncs).rwfseek((_fptr), (_offset), (_origin)))
#define RwFflush(_fptr)          (RWSRCGLOBAL(fileFuncs).rwfflush((_fptr)))
#define RwFtell(_fptr)           (RWSRCGLOBAL(fileFuncs).rwftell((_fptr)))

#endif /* FSYS36_H */
