/**
 * @file common.h
 *
 * @brief Common variables and functions definitions for BMS project Demultiplexing and analysis of DVBT transport stream
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

class inputStreamReader {
	public:
		void openTS_Stream(string);
		void readTS_Stream();
	private:
		ifstream inputTSFile;
		ofstream outputTSFile;
};

#endif