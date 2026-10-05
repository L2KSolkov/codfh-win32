/*
 * Xbox (NV2A) vertex shaders to HLSL (docs/WIN32_PORT.md W2.4): the microcode the driver and the
 * game create shaders from, and the assembler text the skin pipeline generates, translated to
 * vs_4_0 source the device back end compiles.
 */
#ifndef PORT_XVSH_H
#define PORT_XVSH_H

#include <string>

/* A translated shader: its HLSL, and the vertex registers it reads (bit n: vn). */
struct XvshResult
{
    std::string hlsl;
    unsigned inputs;
    bool ok;
};

/* From microcode: the header dword (count in bits 16-23) and four dwords per instruction.
   declared: the registers the vertex declaration supplies (others read as 0,0,0,1). */
XvshResult xvsh_from_microcode(const unsigned *program, unsigned declared);

/* From the Xbox assembler's text (vs.1.1 with the Xbox's registers). */
XvshResult xvsh_from_text(const char *text, size_t length, unsigned declared);

#endif
