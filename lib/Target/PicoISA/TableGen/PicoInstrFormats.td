// PicoInstrFormats.td - my small formats
// Author: Gulshan Nanda, 2025-11-24

class InstFormat<string fmt> { string Fmt = fmt; }

def FrmR : InstFormat<"R">; // dst = op s1, s2
def FrmI : InstFormat<"I">; // op dst, [base+imm]
