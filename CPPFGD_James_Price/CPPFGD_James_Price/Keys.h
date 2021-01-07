#pragma once
#ifndef FILE_H
#define FILE_H

enum KeyStates {
	W = 0,
	A,
	S,
	D,
	E,
	SHIFT,
	MOUSELEFT,
	MOUSERIGHT,
	ENUM_COUNT
};

enum LootType {
	Empty = 0,
	Food,
	Water,
	Bolts,
	GunParts,
	ENUM_C
};
#endif