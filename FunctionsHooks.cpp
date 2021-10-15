#include "FunctionsHooks.h"
#include "Utils.h"
#include "TrFoxHooker.h"
#include <stdexcept>
#include "FoxApi.h"
#include "Bhop.h"

#include "CUserCmd.h"

void FoxHooks::installHooks()
{
  void* CreateMoveFn = (void*)FoxUtils::FindPattern("client.dll", "55 8B EC 6A FF ?? ?? ?? ?? ?? 83 C4 04 85 C0 75 06 B0 01 5D C2 08 00 8B 4D 0C D9 45 08 8B 10 8B 92 04 04 00 00 51 51 8B C8 D9 1C 24 FF D2");
  foxassert(CreateMoveFn);
  PRINTFOXPTR(CreateMoveFn);

  FoxHooks::oCreateMove = (tCreateMove)TrFoxHooker::TrampHook32((char*)CreateMoveFn, (char*)hkCreateMove, 5);
  foxassert(FoxHooks::oCreateMove);
  PRINTFOXPTR(FoxHooks::oCreateMove);
}

FoxHooks::tCreateMove FoxHooks::oCreateMove = nullptr;
void __stdcall FoxHooks::hkCreateMove(float flInputSampleTime, CUserCmd* cmd)
{
  if (cmd != nullptr && FoxApi::g_EngineClient->V_IsInGame() && FoxApi::g_EngineClient->V_IsConnected())
  {
    FoxBhop::doBhop(cmd);
  }

  FoxHooks::oCreateMove(flInputSampleTime, cmd);
}
