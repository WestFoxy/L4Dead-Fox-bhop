#pragma once
class IClientEntity;

class IClientEntityList
{
public:
  IClientEntity* V_GetClientEntity(int entNum)
  {
    typedef IClientEntity*(__thiscall *fnGetClientEntity)(void*, int);
    return FoxUtils::getFoxVMTFunc<fnGetClientEntity>(this, 3)(this, entNum);
  }
};