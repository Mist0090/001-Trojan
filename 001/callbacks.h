#pragma once
#include "001.h"

extern POINT msgBoxPoint;

BOOL CALLBACK MonitorEnumProc( HMONITOR hMonitor, HDC hdcMonitor, PRECT prcBounds, LPARAM lParam );
LRESULT CALLBACK msgBoxHook( INT nCode, WPARAM wParam, LPARAM lParam );