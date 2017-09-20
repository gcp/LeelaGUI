#include <Windows.h>
#include <imagehlp.h>

struct DumpState {
  int state;
  CONTEXT *context;
};

bool safeReadDword(void *addr, DWORD &dest)
{
  __try {
    dest = *(DWORD*)addr;
    return true;
  } __except(1) {
    return false;
  }
}

bool safeTestReadAccess(void *addr)
{
  __try {
    __asm {
      mov eax, addr
      mov eax, [eax]
    }
    return true;
  } __except(1) {
    return false;
  }
}

BOOL WINAPI MiniDumpCallback(PVOID CallbackParam,
                             const PMINIDUMP_CALLBACK_INPUT CallbackInput,
                             PMINIDUMP_CALLBACK_OUTPUT CallbackOutput)
{
  static const unsigned STACK_SEARCH_SIZE = 0x400;
  static const unsigned MEM_BLOCK_SIZE    = 0x400;

  if (CallbackInput->CallbackType == MemoryCallback) {
    // Called to get user defined blocks of memory to write until
    // callback returns FALSE or CallbackOutput->MemorySize == 0.

    DumpState *ds = (DumpState*)CallbackParam;
    switch(ds->state) {
      // Save memory referenced by registers.
      case 0: CallbackOutput->MemoryBase = ds->context->Edi; ds->state++; break;
      case 1: CallbackOutput->MemoryBase = ds->context->Esi; ds->state++; break;
      case 2: CallbackOutput->MemoryBase = ds->context->Ebx; ds->state++; break;
      case 3: CallbackOutput->MemoryBase = ds->context->Edx; ds->state++; break;
      case 4: CallbackOutput->MemoryBase = ds->context->Ecx; ds->state++; break;
      case 5: CallbackOutput->MemoryBase = ds->context->Eax; ds->state++; break;
      case 6: CallbackOutput->MemoryBase = ds->context->Eip; ds->state++; break;
      case 7: CallbackOutput->MemoryBase = ds->context->Esp; ds->state++; break;

      // Save memory referenced by values in stack.
      default:
        if (ds->state < 0x1000)
          ds->state = 0x1000;

        DWORD addr;
        do {
          if (ds->state > 0x1000 + STACK_SEARCH_SIZE)
            return FALSE;

          if (!safeReadDword((void*)((ds->context->Esp & ~3) + ds->state - 0x1000), addr))
            return FALSE;

          ds->state += 4;
        } while(addr < 0x1000 || !safeTestReadAccess((void*)addr));

        CallbackOutput->MemoryBase = addr;
        break;
    }

    if (CallbackOutput->MemoryBase >= MEM_BLOCK_SIZE / 2)
      CallbackOutput->MemoryBase -= MEM_BLOCK_SIZE / 2;
    CallbackOutput->MemorySize = MEM_BLOCK_SIZE;

    // No need to perform additional checks here, the minidump engine
    // safely clips the addresses to valid memory pages only.
    // Also seems to apply for overlapped areas etc.
  }

  return TRUE;
}

BOOL WriteMiniDumpHelper(HANDLE hDump, LPEXCEPTION_POINTERS param) {
    MINIDUMP_EXCEPTION_INFORMATION exception = {};
    exception.ThreadId = GetCurrentThreadId();
    exception.ExceptionPointers = param;
    exception.ClientPointers = FALSE;
    DumpState ds;
    ds.state = 0;
    ds.context = param->ContextRecord;
    MINIDUMP_CALLBACK_INFORMATION mci;
    mci.CallbackRoutine = &MiniDumpCallback;
    mci.CallbackParam = (void*)&ds;
    return MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDump,  (MINIDUMP_TYPE)(MiniDumpWithUnloadedModules), &exception, NULL, &mci);
}
