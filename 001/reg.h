#pragma once
#include "001.h"

void _001 reg_add(
	HKEY HKey,
	LPCWSTR Subkey,
	LPCWSTR ValueName,
	unsigned long Type,
	unsigned int Value
);

void _001 reg_add(
	HKEY HKey,
	LPCWSTR Subkey,
	LPCWSTR ValueName,
	unsigned long Type,
	LPCWSTR Value
);