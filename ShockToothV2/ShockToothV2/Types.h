#pragma once
#include <basetsd.h> //remove later

//NOTE EVERYTHING IN HERE SHOULD EVENTUALLY BE MOVED TO DIFFRENT HEADERS!

/*
Info: Device's Bluetooth Address
Size: UINT8[6]
*/
typedef struct _BD_ADDR {

	UINT8 Address[6];

}BD_ADDR, *PBD_ADDR;

typedef struct _BD_HANDLE {
	//TODO
}BD_HANDLE, *PBD_HANDLE;

typedef struct _B_DEVICE {
	//TODO
}B_DEVICE, *PB_DEVICE;


//Check to see if const should be used at some point
typedef const enum _DEVICE_TYPE {
	unk
};

template <class gtype> constexpr auto checkSize(gtype a) {
	return sizeof(a);
}

template <class gtype> constexpr auto checkAlign(gtype a) {
	return alignof(a);
}