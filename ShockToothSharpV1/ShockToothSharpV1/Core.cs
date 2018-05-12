using MadWizard.WinUSBNet;
namespace Core {
	public partial class CoreClass {

		public byte[] ControlInTransfer(USBDevice device, byte requestType, byte request, int value, int index, int length) {
			return device.ControlIn(requestType, request, value, index, length);
		}
	}
}