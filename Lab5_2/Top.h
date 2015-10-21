#pragma once
#ifndef _TOP_H
#define _TOP_H
#include "systemc.h"
#include "Match.h"
#include "ram.h"
SC_MODULE(top) {
	sc_signal<bool> CE;
	sc_signal<bool> WE;
	sc_signal<sc_uint<32>> addr;
	sc_signal<sc_uint<8>>data;
	//sc_signal<sc_uint<DATA_WIDTH>>que1;
	match mt;
	ram ram;
	SC_CTOR(top) : mt("mt"), ram("ram", 2048) {
		mt.addr(addr);
		mt.WE(WE);
		mt.CE(CE);
		mt.data(data);
		ram.addr(addr);
		ram.WE(WE);
		ram.data(data);
		ram.CE(CE);
	}
};
#endif