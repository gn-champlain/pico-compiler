// M88kTargetInfo.h
// Week 6 - small helper for my M88k backend description.
// I am using this just to keep some basic M88k information
// in one place and to print it for screenshots.

#ifndef M88K_TARGET_INFO_H
#define M88K_TARGET_INFO_H

#include <string>

namespace pico {

	std::string getM88kTriple();      // e.g. "m88k-unknown-elf"
	std::string getM88kDataLayout();  // simple 32-bit layout string

	// For quick tests and screenshots.
	void printM88kSummary();

} // namespace pico

#endif // M88K_TARGET_INFO_H
