/*++

Module Name:

    Internal.h

Abstract:

    This module contains the local type definitions for the
    driver.

Environment:

    Windows User-Mode Driver Framework 2

--*/

//
// Define the tracing flags.
//
// Tracing GUID - 923c8000-6480-4809-b4fa-fe4679be6d94
//

#define WPP_CONTROL_GUIDS                                              \
    WPP_DEFINE_CONTROL_GUID(                                           \
        ShockToothV1TraceGuid, (923c8000,6480,4809,b4fa,fe4679be6d94),                  \
                                                                       \
        WPP_DEFINE_BIT(ShockToothV1_ALL_INFO)                              \
        WPP_DEFINE_BIT(TRACE_DRIVER)                                   \
        WPP_DEFINE_BIT(TRACE_DEVICE)                                   \
        WPP_DEFINE_BIT(TRACE_QUEUE)                                    \
        )                             

#define WPP_FLAG_LEVEL_LOGGER(flag, level)                             \
    WPP_LEVEL_LOGGER(flag)

#define WPP_FLAG_LEVEL_ENABLED(flag, level)                            \
    (WPP_LEVEL_ENABLED(flag) &&                                        \
     WPP_CONTROL(WPP_BIT_ ## flag).Level >= level)

#define WPP_LEVEL_FLAGS_LOGGER(lvl,flags)                              \
           WPP_LEVEL_LOGGER(flags)
               
#define WPP_LEVEL_FLAGS_ENABLED(lvl, flags)                            \
           (WPP_LEVEL_ENABLED(flags) && WPP_CONTROL(WPP_BIT_ ## flags).Level >= lvl)

//
// This comment block is scanned by the trace preprocessor to define our
// Trace function.
//
// begin_wpp config
// FUNC Trace{FLAG=ShockToothV1_ALL_INFO}(LEVEL, MSG, ...);
// FUNC TraceEvents(LEVEL, FLAGS, MSG, ...);
// end_wpp

//
//
// Driver specific #defines
//
#if UMDF_VERSION_MAJOR == 2 && UMDF_VERSION_MINOR == 0
    #define ShockToothV1_TRACING_ID      L"Microsoft\\UMDF2.0\\ShockToothV1 V1.0"
#endif