// First Counter example  
// asic-world.com

#include "systemc.h"

SC_MODULE (first_counter)
{
	sc_in_clk clock;	// Clock input of the design
	sc_in<bool> reset;	// Active high, synchronous reset input
	sc_in<bool> enable;	// Active high enable signal for counter
	sc_out<sc_uint<4>> counter_out;	// 4 bit vector output of counter
	//-----Local Variables------
	sc_uint<4> count;

	//-----Counter Description-----
	void incr_count()
	{
		if (reset.read() == 1)
		{
			count = 0;
			counter_out.write(count);
		}
		else if (enable.read() == 1)
		{
			count = count + 1;
			counter_out.write(count);
			cout<<"@"<<sc_time_stamp()<<" :: Incremented Counter " << counter_out.read()<<endl;
		}
	}			// End of incr_count

// Constructor for first_counter
SC_CTOR(first_counter)
{
	cout<<"Executing new"<<endl;
	SC_METHOD(incr_count);
	sensitive << reset;
	sensitive << clock.pos();	// Positive Edge triggerred
}				// End of constructor

};			// End of module first_counter
