#include "systemc.h"
#include "Top.h"
int sc_main(int argc, char*argv[]) {
	top top("top");
	sc_start();
	return 0;
}