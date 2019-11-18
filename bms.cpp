/**
 * @inputTSFile bms.cpp
 *
 * @brief This is main for BMS project Demultiplexing and analysis of DVBT transport stream
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

// Common definitions
#include "common.h"

// Common libraries
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

/**
 * Function for opening input .ts file from stdin
 * @param sting filename
 * Output file will be named same as input file
 * Make file a txt file as project description require
 * Open inputfile for Writing
 */
void inputStreamReader::openTS_Stream(string filename) {
	inputTSFile.open(filename, ios::binary);
	size_t eof = filename.find_last_of(".");
	string outputfile = filename.substr(0, eof).append(".txt");
	outputTSFile.open(outputfile);
}

int main(int argc, char **argv) {
	if (argc <= 1) {
		cerr << "File missing" << endl;
		return 1;
	}
	inputStreamReader stream;
	stream.openTS_Stream(argv[1]);
}
