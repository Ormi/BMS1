/**
 * @inputTSFile bms.cpp
 *
 * @brief This is main for BMS project Demultiplexing and analysis of DVB-T transport stdoutStream
 *
 * @date Nov 2019
 *
 * @author Michal Ormos
 * xormos00@stud.fit.vutbr.cz
 *
 * VUT FIT
 * BMS 2019/2020
 *
 */

#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "common.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;


Demultiplexor::Demultiplexor() : NITPid(NIT), analyzeNetworkInformation(false), analyzeProgramAssociation (false), analyzeServiceDescription(false),
  packets(0), newServiceDescriptorTable(false), packetParser(false) {
	  
  }

/**
 * This calculation was adopt from source https://dveo.com/broadcast/bit-rate-calculation-for-COFDM-modulation.shtml
 * Author of this source has credit for this citation
 * Dveo copyright 2005
 * @param none
 */
void Demultiplexor::calculateBitrate() {
	// Packet length can be either 188 bytes or 204 bytes
	double secondPacketLength = 204;
	double packetTS = packetLength / secondPacketLength;
	long double A = 54000000 * packetTS;
	// Bandwidth is defined as 8MHz = 1
	long double bandwidth = getBandwidthValue() / 8;
	long double B = A * bandwidth;
	// Modulation QPSL 1/4
	long double C = B * getModulationScheme();
	// FEC Code rate can be define as 3/4
	long double D = C * getCodeRateValue();
	// Guad interval is defined as 1/16 = 16/17
	totalBitrate = D * getGuardValue();
}

void Demultiplexor::printFinalResults(ostream& stdoutStream) {
#ifdef DEBUGMODE
	cout << "Network name: " << networkName << endl
		<< "Network ID: " << networkID << endl
		<< "Bandwidth: " << getBandwidth() << endl
		<< "Constellation: " << getConstellation() << endl
		<< "Guard interval: " << getGuardInterval() << endl
		<< "Code rate: " << getCodeRate() << endl;
	cout << endl;
	for(auto &program: programs)
		cout << "0x" << hex << setw(4) << setfill('0') << program.PID
		<< "-" << program.serviceProviderName << "-" << program.serviceName
		<< ": " << fixed << setprecision(2) << program.bitrate << " Mbps"
		<< endl;
#else
	stdoutStream << "Network name: " << networkName << endl
		<< "Network ID: " << networkID << endl
		<< "Bandwidth: " << getBandwidth() << endl
		<< "Constellation: " << getConstellation() << endl
		<< "Guard interval: " << getGuardInterval() << endl
		<< "Code rate: " << getCodeRate() << endl;
	stdoutStream << endl;
	for(auto &program: programs)
		stdoutStream << "0x" << hex << setw(4) << setfill('0') << program.PID
		<< "-" << program.serviceProviderName << "-" << program.serviceName
		<< ": " << fixed << setprecision(2) << program.bitrate << " Mbps"
		<< endl;
#endif	
}