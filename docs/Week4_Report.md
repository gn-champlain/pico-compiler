# Week 4 Report - TableGen for Backend (Gulshan)

## What I did
I created a small backend for a fictional target called PicoISA. I used TableGen to define basic registers,
simple instruction formats, and a few instructions. Then I generated the `.inc` files and included them
in my C++ classes. I also registered the target info, MC layer, and target machine so the build is clean.

## Why this helps me learn
Doing this made me understand how TableGen connects to the backend classes. I can now read the generated code
and see which parts I need to implement next. I kept it simple on purpose so I can build on it in next weeks.

## Steps I followed
1. Wrote `.td` files in `lib/Target/PicoISA/TableGen`.
2. Added CMake custom commands to call `llvm-tblgen`.
3. Included the generated `.inc` files inside my headers.
4. Built the library and checked the generated files under `build/include/PicoISA/Gen`.
5. Did a small smoke test with `tests/ir/simple.ll`.

## Challenges and lessons
- Matching the generated include paths required me to point include dirs to the build folder.
- It is easy to overcomplicate things, so I kept the formats and instructions small.
- I wrote more comments this week because I want it to read like a student project.

## Testing
I built with CMake and saw the four TableGen steps in the log. I kept the test IR tiny.
For the submission, I will add my build screenshots in Canvas (build log and folder view of the generated files).

## Next steps
- Add real register classes, encoding, and proper MC layer pieces.
- Add a pass pipeline and hook a simple instruction selector later.
