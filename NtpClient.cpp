#include "Ethernet.h"
#include "EthernetUdp.h"
#include "NtpClient.h"


bool NtpClientClass::Init()
{
	bool is_init_success = true;
	// Open serial communications and wait for port to open:
	timeServer = IPAddress(132, 163, 4, 101);
	EthernetClient client;
	byte mac[] = { 0xFA, 0xCC, 0xFA, 0xCC, 0xFA, 0xCC };
	

	// start Ethernet and UDP
	if (Ethernet.begin(mac) == 0) {
		Serial.println(F("Failed to configure Ethernet"));
		is_init_success = false;		
	}
	Udp.begin(localPort);
	Serial.println(Ethernet.localIP());

	return is_init_success;
}

unsigned long NtpClientClass::GetTime()
{
	unsigned long epoch;
	sendNTPpacket(timeServer); // send an NTP packet to a time server

	// wait to see if a reply is available
	//delay(1000);
	if (Udp.parsePacket()) {
		// We've received a packet, read the data from it
		Udp.read(packetBuffer_, NTP_PACKET_SIZE);  // read the packet into the buffer

		//the timestamp starts at byte 40 of the received packet and is four bytes,
		// or two words, long. First, extract the two words:

		unsigned long highWord = word(packetBuffer_[40], packetBuffer_[41]);
		unsigned long lowWord = word(packetBuffer_[42], packetBuffer_[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;
		// now convert NTP time into everyday time:
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		epoch = secsSince1900 - seventyYears;
		// print Unix time:
	}
	return (epoch);
}

// send an NTP request to the time server at the given address 
unsigned long NtpClientClass::sendNTPpacket(IPAddress& address)
{
	// set all bytes in the buffer to 0
	memset(packetBuffer_, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer_[0] = B11100011;   // LI, Version, Mode
	packetBuffer_[1] = 0;     // Stratum, or type of clock
	packetBuffer_[2] = 6;     // Polling Interval
	packetBuffer_[3] = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer_[12] = 49;
	packetBuffer_[13] = 0x4E;
	packetBuffer_[14] = 49;
	packetBuffer_[15] = 52;

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:         
	Udp.beginPacket(address, 123); //NTP requests are to port 123
	Udp.write(packetBuffer_, NTP_PACKET_SIZE);
	Udp.endPacket();
}