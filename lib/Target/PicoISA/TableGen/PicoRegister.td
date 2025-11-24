// PicoRegister.td - my basic registers for PicoISA
// Author: Gulshan Nanda, 2025-11-24

class PicoReg<string n, int num> { string Name = n; int Num = num; }

def R0 : PicoReg<"r0", 0>;
def R1 : PicoReg<"r1", 1>;
def R2 : PicoReg<"r2", 2>;
def R3 : PicoReg<"r3", 3>;
def R4 : PicoReg<"r4", 4>;
def R5 : PicoReg<"r5", 5>;
def R6 : PicoReg<"r6", 6>;
def R7 : PicoReg<"r7", 7>;
def SP : PicoReg<"sp", 8>;
def FP : PicoReg<"fp", 9>;
def PC : PicoReg<"pc", 10>;

// Simple register class. I will refine later.
class PicoRegClass<string cname> { string ClassName = cname; }
def GPR : PicoRegClass<"GPR">;
