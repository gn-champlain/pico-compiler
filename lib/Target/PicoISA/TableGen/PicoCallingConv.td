// PicoCallingConv.td - minimal calling convention
// Author: Gulshan Nanda, 2025-11-24

class CallingConv<string name> { string Name = name; }
def CC_PicoC : CallingConv<"cc_pico_c">;
