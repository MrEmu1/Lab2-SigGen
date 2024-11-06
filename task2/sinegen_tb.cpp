#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    Vsinegen* top = new Vsinegen;
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("sinegen.vcd");

    //initialise Vbuddy
    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 2 SigGen");

    //initialise simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;
    top->incr = 1;
    top->phase = 0;

    //run simulation for many clock cycles
    for (i=0; i<1000000; i++){

        //dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump (2*i*clk);
            top->clk = !top->clk;
            top->eval ();
        } 

        //top->incr = vbdValue();
        top->phase = vbdValue(); // Setting to 64 makes them 90 degrees out of phase (so one sin and one cosine)

        // Send output value to Vbuddy
        vbdPlot(int(top->dout1), 0, 255);
        vbdPlot(int(top->dout2), 0, 255);
        vbdCycle(clk);
        // end of Vbuddy output


        top->rst = (i <2) | (i == 15);
        top->en = (i>4);
        if(Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}