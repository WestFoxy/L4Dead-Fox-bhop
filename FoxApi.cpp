#include "FoxApi.h"
#include "Utils.h"
#include <stdexcept>

namespace FoxApi
{
  extern IVEngineClient* g_EngineClient = nullptr;
  extern IClientEntityList* g_EntityList = nullptr;
}

void FoxApi::initApi()
{
  foxassert(FoxApi::g_EntityList = FoxUtils::ValveGetInterface<IClientEntityList>("client.dll", "VClientEntityList003"));
  foxassert(FoxApi::g_EngineClient = FoxUtils::ValveGetInterface<IVEngineClient>("engine.dll", "VEngineClient013"));
  PRINTFOXPTR(FoxApi::g_EntityList);
  PRINTFOXPTR(FoxApi::g_EngineClient);

  //TODO: find ClientCmd_Unrestricted vmt index ([114] is bad)
  /*FoxApi::g_EngineClient->ClientCmd("toggleconsole");
  FoxApi::g_EngineClient->ClientCmd("clear");
  FoxApi::g_EngineClient->ClientCmd("echo \"foxy bhop successfully loaded\"");*/
}
