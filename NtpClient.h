// NtpClient.h
#ifndef _NTPCLIENT_h
#define _NTPCLIENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SPI.h>         
#include <Ethernet.h>
#include <EthernetUdp.h>


class NtpClientClass
{
private:
	// Enter a MAC address for your controller below.
	// Newer Ethernet shields have a MAC address printed on a sticker on the shield
	
	IPAddress timeServer; // time-a.timefreq.bldrdoc.gov NTP server
	// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov NTP server
	// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov NTP server
	static const unsigned NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

	unsigned int localPort = 8888;      // local port to listen for UDP packets
	unsigned char packetBuffer_[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets 

	// A UDP instance to let us send and receive packets over UDP
	EthernetUDP Udp;

public:
	void Init();
	unsigned long GetTime();
	unsigned long sendNTPpacket(IPAddress& address);
};
#endif

