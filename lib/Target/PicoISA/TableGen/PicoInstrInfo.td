// PicoInstrInfo.td - my sample instructions
// Author: Gulshan Nanda, 2025-11-24

class PicoInst<string opc, InstFormat F> { string OpcodeName = opc; InstFormat Format = F; }

def ADD   : PicoInst<"ADD",   FrmR>;
def SUB   : PicoInst<"SUB",   FrmR>;
def LOAD  : PicoInst<"LOAD",  FrmI>;
def STORE : PicoInst<"STORE", FrmI>;
