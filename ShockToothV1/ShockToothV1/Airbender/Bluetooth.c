/*
MIT License

Copyright(c) 2017 Benjamin "Nefarius" Höglinger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Driver.h"
#include "Bluetooth.tmh"
#include "L2CAP.h"

_Use_decl_annotations_
VOID
AirBenderBulkWriteEvtTimerFunc(
    WDFTIMER  Timer
) {
    NTSTATUS                status;
    PBTH_DEVICE_CONTEXT     pBluetoothCtx;
    PBTH_DEVICE             pBthDevice;
    PDEVICE_CONTEXT         pDeviceContext;
    L2CAP_CID               scid;
    PVOID                   buffer;
    size_t                  bufferLength;

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BLUETOOTH, "%!FUNC! Entry");
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BLUETOOTH, "%!FUNC! Entry");
#endif // _VERB2INFO

    pBluetoothCtx = BluetoothDeviceGetContext(Timer);
    pDeviceContext = DeviceGetContext(pBluetoothCtx->HostDevice);
    pBthDevice = pBluetoothCtx->Device;

#ifndef _VERB2INFO //changed to ifndef from ifdef
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BLUETOOTH,
        "%!FUNC! ClientAddress: %02X:%02X:%02X:%02X:%02X:%02X",
        pBluetoothCtx->Device->ClientAddress.Address[0],
        pBluetoothCtx->Device->ClientAddress.Address[1],
        pBluetoothCtx->Device->ClientAddress.Address[2],
        pBluetoothCtx->Device->ClientAddress.Address[3],
        pBluetoothCtx->Device->ClientAddress.Address[4],
        pBluetoothCtx->Device->ClientAddress.Address[5]);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BLUETOOTH,
        "%!FUNC! ClientAddress: %02X:%02X:%02X:%02X:%02X:%02X",
        pBluetoothCtx->Device->ClientAddress.Address[0],
        pBluetoothCtx->Device->ClientAddress.Address[1],
        pBluetoothCtx->Device->ClientAddress.Address[2],
        pBluetoothCtx->Device->ClientAddress.Address[3],
        pBluetoothCtx->Device->ClientAddress.Address[4],
        pBluetoothCtx->Device->ClientAddress.Address[5]);
#endif // _VERB2INFO

    buffer = WdfMemoryGetBuffer(pBthDevice->HidOutputReportMemory, &bufferLength);

    L2CAP_DEVICE_GET_SCID_FOR_TYPE(
        pBthDevice,
        L2CAP_PSM_HID_Command,
        &scid);

    status = HID_Command(
        pDeviceContext,
        pBthDevice->HCI_ConnectionHandle,
        scid,
        buffer,
        (ULONG) bufferLength);

    if (!NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_ERROR,
            TRACE_BLUETOOTH,
            "HID_Command failed with status %!STATUS!", status);
    }

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BLUETOOTH, "%!FUNC! Exited with status %!STATUS!", status);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BLUETOOTH, "%!FUNC! Exited with status %!STATUS!", status);
#endif // _VERB2INFO

}
