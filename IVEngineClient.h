#pragma once
#include "Utils.h"

class IVEngineClient
{
public:
  int V_GetLocalPlayer(void)
  {
    typedef int(*fnGetLocalPlayer)(void*);
    return FoxUtils::getFoxVMTFunc<fnGetLocalPlayer>(this, 12)(this);
  }

  bool V_IsInGame(void)
  {
    typedef bool(*fnIsInGame)(void*);
    return FoxUtils::getFoxVMTFunc<fnIsInGame>(this, 26)(this);
  }

  bool V_IsConnected(void)
  {
    typedef bool(*fnIsConnected)(void*);
    return FoxUtils::getFoxVMTFunc<fnIsConnected>(this, 27)(this);
  }

  void ClientCmd(const char* szCmdString)
  {
    typedef void(__thiscall *fnClientCmd)(void*, const char*);
    FoxUtils::getFoxVMTFunc<fnClientCmd>(this, 7)(this, szCmdString);
  }
};