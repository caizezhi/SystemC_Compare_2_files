#pragma once
#ifndef _MATCH_H
#define _MATCH_H
#include"systemc.h"
SC_MODULE(match) {
	sc_out<bool>WE;
	sc_out < sc_uint<32>> addr;
	sc_out<bool> CE;
	sc_in<sc_uint<8>> data;
	SC_CTOR(match) {
		SC_THREAD(p1);
	}
	void p1() {
		wait(2, SC_NS);
		ofstream output("F://MisMatch_list.txt");
		ifstream input1;            
		input1.open("F://T1.txt");
		int addr1;
		int file_data;
		sc_uint<8> data_1;
		for (int i = 0;i<1040;i++) {
			input1 >> dec >> addr1;
			input1 >> hex >> file_data;
			WE = 0;CE = 1;
			addr = addr1;
			wait(1, SC_NS);
			if (data.read().to_int() != file_data)
				output << "MISSMATCH:  " << dec << addr1 << "   " << hex << file_data << "    " << data.read().to_string(SC_HEX) << endl;
			wait(1, SC_NS);
		}
		input1.close();
		wait(10, SC_NS);
		cout << "T1 && T2" << endl;
		ifstream input2;              
		input2.open("F://T2.txt");
		int addr2;
		int file_data_2;
		sc_uint<8> data_2;
		for (int j = 0;j<131;j++) {
			input2 >> dec >> addr2;
			input2 >> hex >> file_data_2;
			WE = 1;       
			addr = addr2;
			wait(1, SC_NS);
			WE = 0;      
			wait(1, SC_NS);
			if (data.read().to_int() != file_data_2)
				output << "MISSMATCH:  " << dec << addr2 << "   " << hex << file_data_2 << "    " << data.read().to_string(SC_HEX) << endl;
			wait(1, SC_NS);
		}
		input2.close();
		output.close();
		sc_stop();
	};
};
#endif