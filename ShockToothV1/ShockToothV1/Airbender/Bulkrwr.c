/*
MIT License

Copyright (c) 2017 Benjamin "Nefarius" H�glinger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "Driver.h"
#include "L2CAP.h"

#include "bulkrwr.tmh"


_IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
AirBenderConfigContReaderForBulkReadEndPoint(
    _In_ PDEVICE_CONTEXT DeviceContext
) {
    WDF_USB_CONTINUOUS_READER_CONFIG contReaderConfig;
    NTSTATUS status;

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Entry with Param PDEVICE_CONTEXT: TODO");
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Entry with Param PDEVICE_CONTEXT: TODO");
#endif // _VERB2INFO

    WDF_USB_CONTINUOUS_READER_CONFIG_INIT(&contReaderConfig,
        AirBenderEvtUsbBulkReadPipeReadComplete,
        DeviceContext,    // Context
        BULK_IN_BUFFER_LENGTH);   // TransferLength

    contReaderConfig.EvtUsbTargetPipeReadersFailed = AirBenderEvtUsbBulkReadReadersFailed;

    //
    // Reader requests are not posted to the target automatically.
    // Driver must explictly call WdfIoTargetStart to kick start the
    // reader.  In this sample, it's done in D0Entry.
    // By defaut, framework queues two requests to the target
    // endpoint. Driver can configure up to 10 requests with CONFIG macro.
    //
    status = WdfUsbTargetPipeConfigContinuousReader(DeviceContext->BulkReadPipe,
        &contReaderConfig);

    if (!NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_BULKRWR,
            "OsrFxConfigContReaderForInterruptEndPoint failed %x\n",
            status);
        return status;
    }

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Exited with status %!STATUS!", status);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Exited with status %!STATUS!", status);
#endif // _VERB2INFO

    return status;
}

NTSTATUS WriteBulkPipe(
    PDEVICE_CONTEXT Context,
    PVOID Buffer,
    ULONG BufferLength,
    PULONG BytesWritten) {
    NTSTATUS                        status;
    WDF_MEMORY_DESCRIPTOR           memDesc;

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Entry with Params PDEVICE_CONTEXT: TODO PVOID: %p ULONG: %lu PULONG: %p",
        Buffer, BufferLength, BytesWritten);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Entry with Params PDEVICE_CONTEXT: TODO PVOID: %p ULONG: %lu PULONG: %p",
        Buffer, BufferLength, BytesWritten);
#endif // _VERB2INFO

    WDF_MEMORY_DESCRIPTOR_INIT_BUFFER(
        &memDesc,
        Buffer,
        BufferLength
    );

    status = WdfUsbTargetPipeWriteSynchronously(
        Context->BulkWritePipe,
        NULL,
        NULL,
        &memDesc,
        BytesWritten
    );

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Exited with status %!STATUS!", status);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Exited with status %!STATUS!", status);
#endif // _VERB2INFO

    return status;
}

NTSTATUS
HID_Command(
    PDEVICE_CONTEXT Context,
    BTH_HANDLE Handle,
    L2CAP_CID Channel,
    PVOID Buffer,
    ULONG BufferLength
) {
    NTSTATUS status;
    PUCHAR buffer;

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Entry with Params PDEVICE_CONTEXT: TODO BTH_HANDLE: %hu %hu L2CAP_CID: %hu %hu "
        "PVOID: %p ULONG: %lu", Handle.Lsb, Handle.Msb, Channel.Lsb, Channel.Msb, Buffer, BufferLength);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Entry with Params PDEVICE_CONTEXT: TODO BTH_HANDLE: %hu %hu L2CAP_CID: %hu %hu "
        "PVOID: %p ULONG: %lu", Handle.Lsb, Handle.Msb, Channel.Lsb, Channel.Msb, Buffer, BufferLength);
#endif // _VERB2INFO

#ifndef _KERNEL_MODE
    buffer = malloc(BufferLength+8);
#else
    // TODO: implement
#endif

    buffer[0] = Handle.Lsb;
    buffer[1] = Handle.Msb;
    buffer[2] = (BYTE) ((BufferLength+4)%256);
    buffer[3] = (BYTE) ((BufferLength+4)/256);
    buffer[4] = (BYTE) (BufferLength%256);
    buffer[5] = (BYTE) (BufferLength/256);
    buffer[6] = Channel.Lsb;
    buffer[7] = Channel.Msb;

    RtlCopyMemory(&buffer[8], Buffer, BufferLength);

    status = WriteBulkPipe(Context, buffer, BufferLength+8, NULL);

#ifndef _KERNEL_MODE
    free(buffer);
#else
    // TODO: implement
#endif

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Exited with status %!STATUS!", status);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Exited with status %!STATUS!", status);
#endif // _VERB2INFO

    return status;
}

VOID
AirBenderEvtUsbBulkReadPipeReadComplete(
    WDFUSBPIPE  Pipe,
    WDFMEMORY   Buffer,
    size_t      NumBytesTransferred,
    WDFCONTEXT  Context
) {
    NTSTATUS                        status;
    PDEVICE_CONTEXT                 pDeviceContext = Context;
    PUCHAR                          buffer;
    BTH_HANDLE                      clientHandle;
    PBTH_DEVICE                     pClientDevice;
    L2CAP_SIGNALLING_COMMAND_CODE   code;

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Entry with Params WDFUSBPIPE: %p WDFMEMORY: %p size_t: %I64u WDFCONTEXT: %s",
        Pipe, Buffer, NumBytesTransferred, Context);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Entry with Params WDFUSBPIPE: %p WDFMEMORY: %p size_t: %I64u WDFCONTEXT: %s",
        Pipe, Buffer, NumBytesTransferred, Context);
#endif // _VERB2INFO

    static BYTE CID = 0x01;

    UNREFERENCED_PARAMETER(Pipe);

    if (NumBytesTransferred==0) {
        TraceEvents(TRACE_LEVEL_WARNING, TRACE_BULKRWR,
            "!FUNC! Zero length read "
            "occurred on the Interrupt Pipe's Continuous Reader"
        );
        return;
    }

    buffer = WdfMemoryGetBuffer(Buffer, NULL);

    BTH_HANDLE_FROM_BUFFER(clientHandle, buffer);

    pClientDevice = BTH_DEVICE_LIST_GET_BY_HANDLE(&pDeviceContext->ClientDeviceList, &clientHandle);

    if (pClientDevice==NULL) {
        TraceEvents(TRACE_LEVEL_WARNING, TRACE_BULKRWR, "PBTH_DEVICE not found");
        return;
    }

    if (L2CAP_IS_CONTROL_CHANNEL(buffer)) {
        if (L2CAP_IS_SIGNALLING_COMMAND_CODE(buffer)) {
            code = L2CAP_GET_SIGNALLING_COMMAND_CODE(buffer);

            switch (code) {
                case L2CAP_Command_Reject:
                    {
                        PL2CAP_SIGNALLING_COMMAND_REJECT data = (PL2CAP_SIGNALLING_COMMAND_REJECT) &buffer[8];

                        TraceEvents(TRACE_LEVEL_ERROR, TRACE_BULKRWR, ">> L2CAP_Command_Reject: 0x%04X", data->Reason);

                        break;
                    }

                #pragma region L2CAP_Connection_Request

                case L2CAP_Connection_Request:

                    status = Ds3ConnectionRequest(
                        pDeviceContext,
                        pClientDevice,
                        buffer,
                        &CID);

                    break;

                #pragma endregion

                #pragma region L2CAP_Connection_Response

                case L2CAP_Connection_Response:

                    status = Ds3ConnectionResponse(
                        pDeviceContext,
                        pClientDevice,
                        buffer,
                        &CID);

                    break;

                #pragma endregion

                #pragma region L2CAP_Configuration_Request

                case L2CAP_Configuration_Request:

                    status = Ds3ConfigurationRequest(
                        pDeviceContext,
                        pClientDevice,
                        buffer);

                    break;

                #pragma endregion

                #pragma region L2CAP_Configuration_Response

                case L2CAP_Configuration_Response:

                    status = Ds3ConfigurationResponse(
                        pDeviceContext,
                        pClientDevice,
                        buffer,
                        &CID);

                    break;

                #pragma endregion

                #pragma region L2CAP_Disconnection_Request

                case L2CAP_Disconnection_Request:

                    status = Ds3DisconnectionRequest(
                        pDeviceContext,
                        pClientDevice,
                        buffer);

                    break;

                #pragma endregion

                #pragma region L2CAP_Disconnection_Response

                case L2CAP_Disconnection_Response:

                    status = Ds3DisconnectionResponse(
                        pDeviceContext,
                        pClientDevice);

                    break;

                #pragma endregion

                default:
                    TraceEvents(TRACE_LEVEL_WARNING, TRACE_BULKRWR, "Unknown L2CAP command: 0x%02X", code);
                    break;
            }
        }
    } else if (L2CAP_IS_HID_INPUT_REPORT(buffer)) {
        switch (pClientDevice->DeviceType) {
            case DualShock3:

                status = Ds3ProcessHidInputReport(pClientDevice, buffer);

                break;
            default:
                break;
        }
    } else {
        status = Ds3InitHidReportStage(
            pDeviceContext,
            pClientDevice,
            &CID);
    }

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Exited");
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Exited");
#endif // _VERB2INFO

}

BOOLEAN
AirBenderEvtUsbBulkReadReadersFailed(
    _In_ WDFUSBPIPE Pipe,
    _In_ NTSTATUS Status,
    _In_ USBD_STATUS UsbdStatus
) {
    WDFDEVICE device = WdfIoTargetGetDevice(WdfUsbTargetPipeGetIoTarget(Pipe));
    PDEVICE_CONTEXT pDeviceContext = DeviceGetContext(device);

    UNREFERENCED_PARAMETER(pDeviceContext);

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Entry with Params WDFUSBPIPE: %p NTSTATUS: %!STATUS! USBD_STATUS: %X",
        Pipe, Status, UsbdStatus);
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Entry with Params WDFUSBPIPE: %p NTSTATUS: %!STATUS! USBD_STATUS: %X",
        Pipe, Status, UsbdStatus);
#endif // _VERB2INFO

    TraceEvents(TRACE_LEVEL_ERROR, TRACE_BULKRWR, "Status: 0x%X, USBD_STATUS: 0x%X", Status, UsbdStatus);

#ifdef _VERB2INFO
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_BULKRWR, "%!FUNC! Exited");
#else
    TraceEvents(TRACE_LEVEL_VERBOSE, TRACE_BULKRWR, "%!FUNC! Exited");
#endif // _VERB2INFO

    return TRUE;
}
