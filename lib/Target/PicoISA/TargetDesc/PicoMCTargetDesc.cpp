/*
  File: PicoMCTargetDesc.cpp
  Purpose: Minimal MC init stub (TargetMC only). Target init lives in PicoTarget.cpp.
*/

extern "C" void LLVMInitializePicoISATargetMC() {
	// no-op for now; add real MC registration later
}
