/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    driver and application

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_ShockToothV1,
    0x4f9f7c7f,0x2ede,0x4906,0xaf,0x36,0xd5,0x6a,0x86,0xea,0x25,0x89);
// {4f9f7c7f-2ede-4906-af36-d56a86ea2589}
