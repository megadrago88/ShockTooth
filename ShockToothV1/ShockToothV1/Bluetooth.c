#include "Bluetooth.h"

/*
1. Set up dongle using hci and acl packets
2. Wait for ps3 controller to send a request to connect
3. Accept the request and switch roles
4. Then you listen on the Bulkin endpoint. The controller will then send a L2CAP connection request, for the HCI Control channel (PSM: 0x11).
5. You respond by sending an connection response. First with the result: pending, and then with the result success.
6. Then you have to send a configuration request. The controller will then respond with a configuration request as well.
7. You then respond, and the controller will then respond, that the channel have been successfully established.
8. The program then repeats the steps from 4-7, but this time it sets up the HID Interrupt (PSM: 0x13) channel.
9. Just like for USB connection, the host has to send a special command to make the Dualshock 3 send buttons reports ect. back.
It is a little different for bluetooth. This time you have to send a Set Feature Report (0x53) with
a report ID (0xF4) and the following data: 0x42, 0x03, 0x00, 0x00.
10. Then just listen on the bulkin endpoint, and you will see the bytes changing, when you push a button, use the joysticks etc.
*/