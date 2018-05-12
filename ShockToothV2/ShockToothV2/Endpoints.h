#pragma once
/*TODO: Set up endpoints for the usb dongle

     Name     | Interface # | Alternate Setting | Suggested Endpoint Addr | Endpoint Type | Suggested Max PKT SZ
--------------|-------------|-------------------|-------------------------|---------------|---------------------
HCI CMDs      | 0           | 0                 | 0x00                    | Control       | 8/16/32/64
--------------|-------------|-------------------|-------------------------|---------------|---------------------
HCI EVTs      | 0           | 0                 | 0x81                    | Interrupt(IN) | 16
--------------|-------------|-------------------|-------------------------|---------------|---------------------
ACL Data      | 0           | 0                 | 0x82                    | Bulk (IN)     | 32/64 
              | 0           | 0                 | 0x02                    | Bulk (OUT)    | 32/64
--------------|-------------|-------------------|-------------------------|---------------|---------------------
NO VOICE FOR  | 1           | 0                 | 0x83                    | Isoch (IN)    | 0
USB COMPLIANCE| 1           | 0                 | 0x03                    | Isoch (OUT)   | 0
--------------|-------------|-------------------|-------------------------|---------------|---------------------
https://camo.githubusercontent.com/8d124106494e2ff772382cfdebc81b7b18f2d3ee/687474703a2f2f626c6f672e746b6a656c656374726f6e6963732e646b2f77702d636f6e74656e742f75706c6f6164732f4843492d41434c2d446174612d5061636b65742e6a7067
1. Set up the usb dongle using HCI
	a. Set up usb communications
	b. Set up HCI commands
	c. Send the commands

2. Wait for incoming request

3. Upon arrival accept then switch the roles

4. Listen on BulkIn for L2CAP connection request for the HCI Control channel PSM: 0x11

5. Respond with connection response (pending then success)

6. Send configuration request

6.1. Controller responds with a configuration request

7. Respond (then the controller will respond) and thats the channel successfully set up

Repeat 4-7 for HID Interrupt but using PSM: 0x13

Send special command to make the controller send back reports

Send a Set Feature Report (0x53) with a report ID (0xF4) and the following data:

0x42, 0x03, 0x00, 0x00

Finally just listen in on the bulkin endpoint and watch the bytes changing!

*/

//#include <wdfusb.h>
//#include <wdftypes.h>

