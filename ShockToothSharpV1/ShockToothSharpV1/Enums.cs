
namespace Core.Enums {

	/*
	 * NOTE: There are two forms for every struct the first being it in LSB/LSb form
	 * and the other type being MSB/MSb and are distiguished by the SUFFIX on the end of the
	 * struct name
	 * 
	 * D_0 is LSb to D_7 MSb
	 * format in bracket for P(acket)ID<MSb:LSb> in docs but should be flipped when sent
	 * LSB byte order
	 * 
	 * 
	 * ALL COMMENTS FOLLOW SPECIAL FORMATS THAT RELATE TO THE USB SPEC TABLE FORMAT
	 * 
	 * READ THEM!
	 * 
	 */

	#region LSB_FORMS
	//Style with Smallest on the left

	//4 bits (WITH 4 BIT COMPLEMENT for a total of 1 byte) with coding format TYPE,NAME,VALUE
	public struct PACKET_ID_LSb {
		enum Token {
			OUT = 1000,
			IN = 1001,
			SOF = 1010,
			SETUP = 1011
		}
		enum Data {
			DATA0 = 1100,
			DATA1 = 1101,
			DATA2 = 1110,
			MDATA = 1111
		}
		enum Handshake {
			ACK = 0100,
			NAK = 0101,
			STALL = 0111,
			NYET = 0110
		}
		enum Special {
			PRE = 0011, //TOKEN
			ERR = 0011, //HANDSHAKE
			SPLIT = 0001, //TOKEN
			PING = 0010, //TOKEN
			Reserved = 0000
		}
	}

	public struct FUNCTION_EP_FIELDS_LSb {
		//six bits for ADDR
		//two bits for EP ADDR
	}
	//MSB on the rightmost ? (specs have a B on the right end after the 8 digits)(EDIT: YES)
	public struct USB_STANDR_DEVICE_RQST_LSB {
		struct SDR_bmRequestType {
			enum Flowdir {

			}
		}
	}
	
	#endregion
	#region MSB_FORMS
	//Human style with the biggest on the left
	#endregion
}