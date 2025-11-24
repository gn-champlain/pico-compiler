# PicoISA Backend (Week 4 TableGen) - Gulshan

This is my Week 4 work where I use TableGen to define a tiny backend for a fictional CPU called **PicoISA**.
I kept it simple and clean so I can explain it in class and also extend later. It builds as a small library and
shows how TableGen generates the `.inc` files that my C++ classes use.

## How I built and tested it

1. I added this backend folder into my project and then ran CMake with my LLVM paths.
2. CMake calls `llvm-tblgen` to generate:
   - `PicoGenRegisterInfo.inc`
   - `PicoGenInstrInfo.inc`
   - `PicoGenSubtargetInfo.inc`
   - `PicoGenCallingConv.inc`
3. Then it builds `LLVMPicoISA` static library and registers the target info, MC layer, and target machine.
4. I used `tests/ir/simple.ll` for a quick smoke test to make sure everything links and the pipeline is ok.

### Windows (my setup)

```bat
cmake -S . -B build ^
  -DLLVM_DIR="C:\path\to\llvm\lib\cmake\llvm" ^
  -DLLVM_TABLEGEN_EXE="C:\path\to\bin\llvm-tblgen.exe"
cmake --build build -v
```

### Linux or macOS

```bash
cmake -S . -B build   -DLLVM_DIR=/path/to/llvm/lib/cmake/llvm   -DLLVM_TABLEGEN_EXE=/path/to/bin/llvm-tblgen
cmake --build build -v
```

After build, I checked that the generated files are in:
```
build/include/PicoISA/Gen/
```

## What is inside

- `lib/Target/PicoISA/TableGen/` TableGen files for registers, formats, instructions, calling conv and sched
- `lib/Target/PicoISA/TargetInfo/` target info registration
- `lib/Target/PicoISA/TargetDesc/` MC asm info and target desc
- `include/Target/PicoISA/` headers that include the generated `.inc` files
- `tests/ir/simple.ll` a tiny IR test
- `docs/Week4_Report.md` my short report for submission
- Top level `CMakeLists.txt` to build out of tree

## Why this matches my lecture and rubric

- **Records and Classes:** I defined registers, instruction formats, and sample instructions in TableGen.
- **Integration:** I included the generated headers in my C++ classes and registered the target.
- **Testing:** I built with CMake and used a tiny IR file for a smoke test and build log verification.
- **Quality:** I wrote clean comments in beginner friendly style and kept files organized.

If the grader needs screenshots, I will add build logs and short screenshots from my system in the Canvas submission.
