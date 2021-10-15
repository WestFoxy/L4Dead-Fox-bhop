#pragma once
#include "IVEngineClient.h"
#include "IClientEntityList.h"
#include "CUserCmd.h"

namespace FoxApi
{
  extern IVEngineClient* g_EngineClient;
  extern IClientEntityList* g_EntityList;

  void initApi();
}