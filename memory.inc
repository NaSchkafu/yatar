' Based on memory.inc from XProfanX2 help

$H H:\Devel\XProfanX2\Include\windows.ph
Def &HEAP_ZERO_MEMORY 0x8
Def CopyMemory(3) !"Kernel32","RtlMoveMemory"

Class Vector = Vector@, Free@, Size@, Get@, Set@, Add@, Clear@, \
              -hMem%%, -size%, -eSize%, -hHeap%%, -allocated%

Proc Vector.Vector
  Parameters initial%, elementSize%
  .eSize% = elementSize%
  .allocated% = initial%
  .size% = 0
  .hHeap%% = ~GetProcessHeap()
  .hMem%% = ~HeapAlloc(.hHeap%%, &HEAP_ZERO_MEMORY, .allocated% * .eSize%)
EndProc

Proc Vector.Size
  Return .Size%
EndProc

Proc Vector.Get
  Parameters idx%
  If idx% < .size%
    Return .hMem%% + idx% * .eSize%
  EndIf
  Return 0
EndProc

Proc Vector.Set
  Parameters idx%, element%%
  If idx% < .size%
    CopyMemory(.hMem%% + idx%*.eSize%, element%%, .eSize%)
    Return 1
  EndIf
  Return 0
EndProc

Proc Vector.Add
  Parameters element%%
  If .size% >= .allocated%
    .allocated% = .allocated% * 2
    .hMem%% = ~HeapReAlloc(.hHeap%%, &HEAP_ZERO_MEMORY, .hMem%%, .allocated% * .eSize%)
  EndIf
  .size% = .Size% + 1
  Return .Set(.size% - 1, element%%)
EndProc

Proc Vector.Free
  .Size% = 0
  .Allocated% = 0
  ~HeapFree(.hHeap%%, 0, .hMem%%)
  .hMem%% = 0
  .hHeap%% = 0
EndProc

Proc Vector.Clear
  .Size% = 0
EndProc



'-Begin-----------------------------------------------------------------
'-ExternalFunctions---------------------------------------------------



'
'Class Stack = -Size%, -Allocated%, -Start%%, -hHeap%%, Push@, Peek@, Pop@, Stack@, Free@
'
'Proc Stack.Push
'  Parameters HANDLE e
'  If .Size% >= .Allocated%
'    .Allocated% *= 2
'    .Start%% = ~HeapReAlloc(.hHeap%%, &HEAP_ZERO_MEMORY, .Start%%, .Allocated% * SizeOf(.hHeap%%))
'  EndIf
'
'  Long .Start%%, .Size% * SizeOf(e) = e
'  Inc .Size%
'EndProc
'
'Proc Stack.Stack
'  .Size% = 0
'  .Allocated = 10
'  hHeap = ~GetProcessHeap()
'  .Start%% = ~HeapAlloc(hHeap, &HEAP_ZERO_MEMORY, .Allocated% * SizeOf(hHeap))
'EndProc
'
'Proc Stack.Pop
'  Case .Size% > 0: Dec .Size%
'EndProc
'
'Proc Stack.Peek
'  Case .Size% > 0: Return Long(.Start%%, .Size%*SizeOf(.hHeap%%))
'  Return &NULL
'EndProc
'
'Proc Stack.Free
'  Case .Allocated% > 0: ~HeapFree(.hHeap%%, 0, .Start%%)
'  .Start%% = &NULL
'  .Size% = 0
'  .Allocated% = 0
'EndProc
'
