/**
 * XorTech Source Code
 */
#include <XtCommon.h>
#include "XtEngine.h"

XT_ENTRY
{
    int exitCode = xt::XtEngine::getInstance()->run();
    xt::XtEngine::release();
    return exitCode;
}