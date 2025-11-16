; Week 3 - Class inheritance and virtual function example in LLVM IR
; Language idea:
;   class Animal { virtual void speak(); }
;   class Dog : Animal { override void speak(); }
;   main:
;       Animal a = Dog();
;       a.speak();   // virtual dispatch to Dog::speak

declare i32 @printf(i8*, ...)

@.dbg_dog_created = private unnamed_addr constant [70 x i8] c"[DEBUG] Dog object created... inherited from Animal and fully ready.\0A\00"
@.dbg_call_virtual = private unnamed_addr constant [80 x i8] c"[DEBUG] Calling speak() using virtual dispatch... checking actual object type.\0A\00"
@.dbg_dog_speaks  = private unnamed_addr constant [55 x i8] c"[DEBUG] Dog speaks... this is the overridden version.\0A\00"

; "Class" layout for Animal:
; struct Animal {
;   void* vtable;
; };
%Animal = type { i8* }

; Vtable is an array of function pointers taking (Animal*).
; Index 0: pointer to speak() implementation.
@Dog_vtable = global [1 x void (%Animal*)*] [ void (%Animal*)* @Dog_speak ]

; Helper: print a C string using printf
define void @print(i8* %msg) {
entry:
  call i32 (i8*, ...) @printf(i8* %msg)
  ret void
}

; Dog::speak(Animal* this)
define void @Dog_speaks_impl(%Animal* %this) {
entry:
  %msg_ptr = getelementptr [55 x i8], [55 x i8]* @.dbg_dog_speaks, i32 0, i32 0
  call void @print(i8* %msg_ptr)
  ret void
}

; For the vtable we need the function type exactly: void (%Animal*)*
define void @Dog_speak(%Animal* %this) {
entry:
  ; Just forward to the implementation, kept separate for clarity
  call void @Dog_speaks_impl(%Animal* %this)
  ret void
}

; run() is the entry point called from wrapper_main.c
define void @run() {
entry:
  ; Allocate Dog object on stack.
  ; We treat Dog as having the same layout as Animal (only vtable pointer).
  %dog_obj = alloca %Animal

  ; Set Dog's vtable
  %vtbl_gep = getelementptr [1 x void (%Animal*)*], [1 x void (%Animal*)*]* @Dog_vtable, i32 0, i32 0
  %vtbl_as_i8 = bitcast void (%Animal*)** %vtbl_gep to i8*
  %dog_vtbl_ptr = getelementptr %Animal, %Animal* %dog_obj, i32 0, i32 0
  store i8* %vtbl_as_i8, i8** %dog_vtbl_ptr

  ; Debug: Dog object created
  %msg_created = getelementptr [70 x i8], [70 x i8]* @.dbg_dog_created, i32 0, i32 0
  call void @print(i8* %msg_created)

  ; Treat dog_obj as an Animal* (upcast)
  %animal_ref = bitcast %Animal* %dog_obj to %Animal*

  ; Debug: about to call speak() using virtual dispatch
  %msg_call = getelementptr [80 x i8], [80 x i8]* @.dbg_call_virtual, i32 0, i32 0
  call void @print(i8* %msg_call)

  ; Load vtable pointer from Animal
  %vtbl_ptr_slot = getelementptr %Animal, %Animal* %animal_ref, i32 0, i32 0
  %vtbl_i8 = load i8*, i8** %vtbl_ptr_slot

  ; Cast it back to a pointer-to-function-pointer
  %vtbl_funcptrptr = bitcast i8* %vtbl_i8 to void (%Animal*)**

  ; Load speak() from vtable index 0
  %speak_func = load void (%Animal*)*, void (%Animal*)** %vtbl_funcptrptr

  ; Call via function pointer: virtual dispatch
  call void %speak_func(%Animal* %animal_ref)

  ret void
}