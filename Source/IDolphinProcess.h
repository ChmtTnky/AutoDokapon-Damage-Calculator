// Interface to perform operations in Dolphin's process
#pragma once

#include <cstddef>

#include "CommonTypes.h"

namespace DolphinComm
{
class IDolphinProcess
{
public:
  virtual ~IDolphinProcess()
  {
  }
  virtual bool findPID() = 0;
  virtual bool obtainEmuRAMInformations() = 0;
  virtual bool readFromRAM(const u32 offset, char* buffer, const size_t size,
                           const bool withBSwap) = 0;
  virtual bool writeToRAM(const u32 offset, const char* buffer, const size_t size,
                          const bool withBSwap) = 0;

  int getPID() const
  {
    return m_PID;
  };
  u64 getEmuRAMAddressStart() const
  {
    return m_emuRAMAddressStart;
  };
  bool isMEM2Present() const
  {
    return m_MEM2Present;
  };
  u64 getMEM2AddressStart() const
  {
    return m_MEM2AddressStart;
  };
  u32 getMEM1ToMEM2Distance() const
  {
    if (!m_MEM2Present)
      return 0;
    return m_MEM2AddressStart - m_emuRAMAddressStart;
  };

protected:
  int m_PID = -1;
  u64 m_emuRAMAddressStart = 0;
  u64 m_MEM2AddressStart = 0;
  bool m_MEM2Present = false;
};
} // namespace DolphinComm
