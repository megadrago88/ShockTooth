//
// Define below GUIDs
//
#include <initguid.h>

//
// Device Interface GUID.
// Used by all WinUsb devices that this application talks to.
// Must match "DeviceInterfaceGUIDs" registry value specified in the INF file.
// a4eb8159-f995-4614-be33-12d8e98f7540
//
DEFINE_GUID(GUID_DEVINTERFACE_ShockToothV2CycleTestApp,
	0xa4eb8159, 0xf995, 0x4614, 0xbe, 0x33, 0x12, 0xd8, 0xe9, 0x8f, 0x75, 0x40);

typedef struct _DEVICE_DATA {

	BOOL                    HandlesOpen;
	WINUSB_INTERFACE_HANDLE WinusbHandle;
	HANDLE                  DeviceHandle;
	TCHAR                   DevicePath[MAX_PATH];

} DEVICE_DATA, *PDEVICE_DATA;

HRESULT
OpenDevice(
	_Out_     PDEVICE_DATA DeviceData,
	_Out_opt_ PBOOL        FailureDeviceNotFound
);

VOID
CloseDevice(
	_Inout_ PDEVICE_DATA DeviceData
);
