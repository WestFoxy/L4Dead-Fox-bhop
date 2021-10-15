#pragma once
#include <Windows.h>
#include "CUserCmd.h"

namespace FoxHooks
{
  void installHooks();

  typedef void(__stdcall* tCreateMove)(float, CUserCmd*);
  extern tCreateMove oCreateMove;
  void __stdcall hkCreateMove(float flInputSampleTime, CUserCmd* cmd);
}