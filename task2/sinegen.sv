module sinegen #(
    parameter   A_WIDTH = 8,
    parameter   D_WIDTH = 8
)(
    //interface signals
    input logic                 clk,
    input logic                 rst,
    input logic                 en,
    input logic [A_WIDTH-1:0]   phase,
    input logic                 incr,   //increment for output counter
    output logic [D_WIDTH-1:0]  dout1,    //output data
    output logic [D_WIDTH-1:0]  dout2
);

    logic [A_WIDTH-1:0]         address; //interconnect wire

counter addrCounter (
    .clk (clk),
    .rst (rst),
    .en (en),
    .incr (incr),
    .count (address)
);

rom sinRom (
    .clk (clk),
    .addr1 (address),
    .dout1 (dout1),
    .addr2 (address + phase),
    .dout2 (dout2)
);

endmodule
