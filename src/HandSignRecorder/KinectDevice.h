#include <XnUSB.h>

/**
* Class to control Kinect's motor.
*/
class KinectDevice
{
public:
	enum { MaxDevs = 16 };
	typedef enum { LED_OFF=0, LED_GREEN, LED_RED, LED_YELLOW, LED_BLINK_YELLOW, LED_BLINK_GREEN, LED_BLINK_RED_YELLOW } LED_OPTION;

public:
	KinectDevice();
	virtual ~KinectDevice();

	/**
	* Open device.
	* @return true if succeeded, false - overwise
	*/
	bool Open();

	/**
	* Close device.
	*/
	void Close();

	/**
	* Move motor up or down to specified angle value.
	* @param angle angle value
	* @return true if succeeded, false - overwise
	*/
	bool Move(int angle);

	bool ChangeLED(LED_OPTION option);
	
	int GetAngle();

	int GetLEDColor();

private:
	XN_USB_DEV_HANDLE m_devs[MaxDevs];
	XnUInt32 m_num;
	int m_angle;
	LED_OPTION m_led;
	bool m_isOpen;
};