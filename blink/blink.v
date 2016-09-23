
//yosys -p 'synth_ice40 -top blink -blif blink.blif' blink.v
//
module blink(input wire clk, output wire blinker);
assign clk=iCE_CLK;
reg [17:0] counter;
always @(posedge clk) counter <= counter + 1;
assign blinker = counter[17];
endmodule
