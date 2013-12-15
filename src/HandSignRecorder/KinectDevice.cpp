#include "KinectDevice.h"

KinectDevice::KinectDevice(){
	m_isOpen = false;
}

KinectDevice::~KinectDevice(){
	Close();
}

bool KinectDevice::Open(){
	const XnUSBConnectionString *paths;
	XnUInt32 count;
	XnStatus res;

	// Init OpenNI USB
	res = xnUSBInit();
	if (res != XN_STATUS_OK)
	{
		xnPrintError(res, "xnUSBInit failed");
		return false;
	}

	// Open all "Kinect motor" USB devices
	res = xnUSBEnumerateDevices(0x045E /* VendorID */, 0x02B0 /*ProductID*/, &paths, &count);
	if (res != XN_STATUS_OK){
		xnPrintError(res, "xnUSBEnumerateDevices failed");
		return false;
	}

	// Open devices
	for (XnUInt32 index = 0; index < count; ++index){
		res = xnUSBOpenDeviceByPath(paths[index], &m_devs[index]);
		if (res != XN_STATUS_OK) {
			xnPrintError(res, "xnUSBOpenDeviceByPath failed");
			return false;
		}
	}

	m_num = count;
	XnUChar buf[1]; // output buffer

	// Init motors
	for (XnUInt32 index = 0; index < m_num; ++index){
		res = xnUSBSendControl(m_devs[index], (XnUSBControlType) 0xc0, 0x10, 0x00, 0x00, buf, sizeof(buf), 0);
		if (res != XN_STATUS_OK) {
			xnPrintError(res, "xnUSBSendControl failed");
			Close();
			return false;
		}

		res = xnUSBSendControl(m_devs[index], XN_USB_CONTROL_TYPE_VENDOR, 0x06, 0x01, 0x00, NULL, 0, 0);
		if (res != XN_STATUS_OK) {
			xnPrintError(res, "xnUSBSendControl failed");
			Close();
			return false;
		}
	}

	ChangeLED(LED_OFF);
	m_isOpen = true;

	return true;
}

void KinectDevice::Close(){
	if (m_isOpen) {
		for (XnUInt32 index = 0; index < m_num; ++index) {
			xnUSBCloseDevice(m_devs[index]);
		}
		m_isOpen = false;
	}
}

bool KinectDevice::Move(int angle){
	XnStatus res;

	if(angle>=-25 && angle<=25){
		// Send move control requests
		for (XnUInt32 index = 0; index < m_num; ++index)
		{
			res = xnUSBSendControl(m_devs[index], XN_USB_CONTROL_TYPE_VENDOR, 0x31, angle, 0x00, NULL, 0, 0);
			if (res != XN_STATUS_OK)
			{
				xnPrintError(res, "xnUSBSendControl failed");
				return false;
			}
		}
		m_angle = angle;
		return true;
	}
	return false;
}

bool KinectDevice::ChangeLED(LED_OPTION option){
	int res;

	if(option>=LED_OFF && option <= LED_BLINK_RED_YELLOW){
		for (XnUInt32 index = 0; index < m_num; ++index)
		{
			res = xnUSBSendControl(m_devs[index], XN_USB_CONTROL_TYPE_VENDOR, 0x06, option, 0x00, NULL, 0, 0);
			if (res != XN_STATUS_OK)
			{
				xnPrintError(res, "xnUSBSendControl failed");
				return false;
			}
		}
		m_led = option;
		return true;
	}
	return false;
}

int KinectDevice::GetAngle(){
	return m_angle;
}

int KinectDevice::GetLEDColor(){
	return m_led;
}

/* Sample Usage
int main(int argc, char *argv[])
{
	KinectMotors motors;

	if (!motors.Open()) // Open motor devices
		return 1;

	motors.Move(31); // Move them up to 31 degree

	pause_();

	motors.Move(-31); // Move them down to 31 degree.

	pause_();

	motors.Move(0);
	return 0;
}*/

