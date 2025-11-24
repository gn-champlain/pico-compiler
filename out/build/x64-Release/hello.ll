; ModuleID = 'pico_module'
source_filename = "pico_module"

@fmt = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr @fmt, i32 100)
  %1 = call i32 (ptr, ...) @printf(ptr @fmt, i32 42)
  %2 = call i32 (ptr, ...) @printf(ptr @fmt, i32 7)
  ret i32 0
}
