#pragma once
#ifndef _RAM_H
#define _RAM_H
#include"systemc.h"
#include <fstream>
#include <iostream>
SC_MODULE(ram) {
	sc_in<bool> WE;
	sc_in<bool> CE;
	sc_in < sc_uint<32>> addr;
	sc_inout<sc_uint<8>> data;
	void write() {
		if (WE) {
			if (CE) {
				ram_data[addr.read().to_int()] = data;
			}
		}
		else {
			SC_REPORT_ERROR("<ERROR 002>", "writing out of range");
		}
	};
	void read() {
		if (!WE) {
			if (CE) {
				data = ram_data[addr.read().to_int()];
			}
			else {
				data = 0xff;
			}
		}
		else {
			SC_REPORT_ERROR("<ERROR 001>", "reading out of range");
		}
		};
	void inform() {
		if (WE) {
			w_event.notify();
		}
		if (!WE) {
			r_event.notify();
		}
		if (addr.read().to_int() >= _size) {
			SC_REPORT_ERROR("<ERROR 003>", "Hint");
		}
	};
	ram(sc_module_name _nm, int size) :sc_module(_nm), _size(size) {
		ram_data = new sc_uint<8>[_size];
		ifstream input;
		input.open("F://T1.txt");
		if (!input)cout << "No Such File" << endl;
		int x = 0;
		sc_uint<8>  mem_data;
		int file_data;
		for (int i = 0;i < 1040;i++) {
			if (i >= size)break;
			input >> dec >> x;
			input >> hex >> file_data;
			mem_data = file_data;
			ram_data[x] = mem_data;
		}
		input.close();
		SC_METHOD(write);
		sensitive << w_event;
		dont_initialize();
		SC_METHOD(read);
		sensitive << r_event;
		dont_initialize();
		SC_METHOD(inform);
		sensitive << CE << WE << addr << data;
		dont_initialize();
	}
	SC_HAS_PROCESS(ram);
	~ram() { delete[]ram_data; }
	sc_event w_event;
	sc_event r_event;
	int _size;
	sc_uint<8> *ram_data;
};
#endif