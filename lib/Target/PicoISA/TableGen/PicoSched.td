// PicoSched.td - minimal scheduling model
// Author: Gulshan Nanda, 2025-11-24

class ProcModel<string name> { string Name = name; }
def PicoProc : ProcModel<"pico-generic">;
