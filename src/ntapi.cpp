////////////////////////////////////////////////////////////////////////////////
//
//  Visual Leak Detector - Global NT API Function Pointers
//  Copyright (c) 2005-2014 VLD Team
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  See COPYING.txt for the full terms of the GNU Lesser General Public License.
//
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifndef VLDBUILD
#define VLDBUILD
#endif

#include "ntapi.h"

// Global function pointers for explicit dynamic linking with NT APIs that can't
// be load-time linked (there is no import library available for these).
LdrLoadDll_t LdrLoadDll;
LdrLoadDllWin8_t LdrLoadDllWin8;
RtlAllocateHeap_t RtlAllocateHeap;
RtlFreeHeap_t RtlFreeHeap;
RtlReAllocateHeap_t RtlReAllocateHeap;

LdrGetDllHandle_t LdrGetDllHandle;
LdrGetProcedureAddress_t LdrGetProcedureAddress;
LdrUnloadDll_t LdrUnloadDll;
LdrLockLoaderLock_t LdrLockLoaderLock;
LdrUnlockLoaderLock_t LdrUnlockLoaderLock;

#if _WIN32_WINNT < 0x0600
USHORT WINAPI RtlCaptureStackBackTrace(__in ULONG FramesToSkip, __in ULONG FramesToCapture, __out PVOID * BackTrace,
                                       __out_opt PULONG BackTraceHash)
                                       {
   RtlCaptureStackBackTrace_t func =
    (RtlCaptureStackBackTrace_t)(GetProcAddress(LoadLibrary(L"kernel32.dll"), "RtlCaptureStackBackTrace"));

   if(func == NULL)
       return; // WOE 29.SEP.2010

   // Quote from Microsoft Documentation:
   // ## Windows Server 2003 and Windows XP:  
   // ## The sum of the FramesToSkip and FramesToCapture parameters must be less than 63.
   const int kMaxCallers = 62; 

   void* callers[kMaxCallers];
   int count = (func)(0, kMaxCallers, callers, NULL);
   for(i = 0; i < count; i++)
      printf(TraceFile, "*** %d called from %016I64LX\n", i, callers[i]);
                                       }
#endif