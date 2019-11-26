/**
 * @file common.h
 *
 * @brief Common variables and functions definitions for BMS project Demultiplexing and analysis of DVBT transport stdoutStream
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

// Shared libraries
#include <stdint.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;

#ifndef COMMON_H
#define COMMON_H

// Define constants from ETSI EN 300 468 norm
// source taken from https://www.etsi.org/deliver/etsi_en/300400_300499/300468/01.13.01_40/en_300468v011301o.pdf
// Digital Video Broadcasting (DVB);
// Specification for Service Information (SI) in DVB systems 
// Start here

// Taken from Table 1, page 20
const uint8_t PAT = 0x00;
const uint8_t CAT = 0x01; // not needed
const uint8_t NIT = 0x10;
const uint8_t SDT = 0x11;

// Taken from Table 2, page 20
const uint8_t PAS = 0x00;
const uint8_t CAS = 0x01; // not needed
const uint8_t PMS = 0x02;
const uint8_t NIS = 0x40;
const uint8_t SDS = 0x42;

// Taken from Table 12, page 32
const uint8_t NETWORK_NAME_DESCRIPTOR = 0x40;
const uint8_t SERVCE_DESCRIPTOR = 0x48;
const uint8_t TERRESTRIAL_DELIVERY_SYSTEM_DESCRIPTOR = 0x5A;

// Taken from table 26, page 40
const uint8_t VIDEO_STREAM = 0x02; // not needed
const uint8_t AUDIO_STREAM = 0x03; // not needed
// Ends here

// This magic number was taken from VUT FIT BMS Forum and documentation to project
static const int packetLength = 188;

class Packet {
	public:
		Packet();
		Packet(uint8_t *data, int n);
		vector<uint8_t> payload;
		bool readPacketLine(ifstream &in);
		bool packetParser();

		bool isEmpty() { 
			return packetHeader.PID == 0x1FFF; 
		}		
		bool packetError() { 
			return packetHeader.packetError; 
		}
		uint16_t getPID() { 
			return packetHeader.PID; 
		}
		bool getPayloadStart() { 
			return packetHeader.payloadBeginning == 1; 
		}
		uint8_t getContinuity() { 
			return packetHeader.continuityCounter; 
		}
	private:
		// Based on table 108
		// Number of bits
		struct Header {
			uint8_t synchronizationByte : 8;
			uint8_t packetError;
			uint8_t payloadBeginning: 1;
			uint8_t transportPriority: 1;
			uint16_t PID: 13;
			uint8_t transportScrambling : 2;
			uint8_t adaptationFieldDataDescriptor : 2;
			uint8_t continuityCounter : 4;
		};
		vector<uint8_t> rawData;
		Header packetHeader;
		vector<uint8_t> adaptationFieldDataDescriptor;
		string networkName;
	};

// Most information was taken from https://www.etsi.org/deliver/etsi_en/300400_300499/300468/01.13.01_40/en_300468v011301o.pdf
class Demultiplexor {
	public:
		Demultiplexor();
		void calculateBitrate();
		bool parseNetworkInformationTable(Packet &packet);
		bool parseProgramAssociationTable (Packet &packet);
		bool parseServiceDescriptionTable(Packet &packet);
		bool parseProgramMapTable(Packet &packet);

		// Check in PAT table if there is packet
		bool isPacketProgramMapTable (uint16_t PID);
		// Print info about transport stdoutStream
		void printFinalResults(ostream& stdoutStream);
		// Used for bind tables
		void bindMaps();
		uint16_t NITPid;
		bool analyzeNetworkInformation;
		bool analyzeProgramAssociation ;
		bool analyzeServiceDescription;
		// PID, packets
		map<uint16_t, uint32_t> packetsCounter;
		// From PMT packets
		map<uint16_t, set<uint16_t>> programElementary;
		// Total packets
		uint32_t packets;
	private:
		bool parseDescriptors(Packet &packet, uint8_t offset, uint16_t length);
		void parseServiceDescriptor(uint16_t offset, uint16_t length, uint16_t serviceID);
	};

class inputStreamReader {
	public:
		void openTS_Stream(string);
		void readTS_Stream();
	private:
		ifstream inputTSFile;
		ofstream outputTSFile;
		uint8_t buffer[packetLength];
		Demultiplexor dmx;
};

#endif