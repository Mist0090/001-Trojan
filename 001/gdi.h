#pragma once
#include "001.h"

void SaveImageFile( HBITMAP hBmp, WCHAR* filename );

HBITMAP GetHBITMAPFromImageFile( WCHAR* pFilePath );

int GetEncoderClsid( const WCHAR* format, CLSID* pClsid );

//32bit color table
typedef union tagRGBCOLOR32 {
	COLORREF rgb;
	struct {
		byte b;         //8bit
		byte g;         //16bit
		byte r;          // 24bit
		byte unused; // 32bit
	};
} RGBCOLOR, * PRGBCOLOR;

//24bit color table
typedef struct tagRGBCOLOR24 {
		byte b;         //8bit
		byte g;         //16bit
		byte r;          // 24bit
} RGBCOLOR24, * PRGBCOLOR24;

typedef struct tagHSLCOLOR {
	float h;
	float s;
	float l;
} HSLCOLOR;

typedef struct tagHSVCOLOR {
	float h;
	float s;
	float v;
} HSVCOLOR;