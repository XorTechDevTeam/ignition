/**
 * @file XtCall.h
 * @author Rabbitlancer
 * @date 17 Aug 2017
 *
 * Defines function calling convention for AngelScript.
 * If run on windows, XTCALL is __stdcall, otherwise - __cdecl (that is, default).
 */

#pragma once

#if defined(XT_WINDOWS)
#define XTCALL __stdcall
#define asXTCALL asCALL_STDCALL
#else
#define XTCALL /**/
#define asXTCALL asCALL_CDECL
#endif
