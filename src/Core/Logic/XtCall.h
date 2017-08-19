//
// Created by rabbitlancer on 8/18/17.
//

#pragma once

#if defined(XT_WINDOWS)
#define XTCALL __stdcall
#define asXTCALL asCALL_STDCALL
#else
#define XTCALL /**/
#define asXTCALL asCALL_CDECL
#endif
