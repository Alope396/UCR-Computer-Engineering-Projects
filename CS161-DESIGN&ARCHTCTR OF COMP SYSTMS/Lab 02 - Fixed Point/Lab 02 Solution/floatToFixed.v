`timescale 1ns / 1ps

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

`define MANTISSA_SIZE 23
`define BIAS 127

module floatToFixed(
  input wire clk, 
  input wire rst , 
  input wire[31:0] float, 
  input wire[4:0] fixpointpos , 
  output reg[31:0] result );

wire [31:0] fixedresult ; 

// Your  Implementation 
reg [7:0] exp;

// -------------------------------------------	
// Register the results 
// -------------------------------------------

always @ ( * ) begin
	result[23] = 1'b1;
	result[22:0] = float[22:0];
	
	exp = float[30:23] - `BIAS;
	result = result >> (`MANTISSA_SIZE - (exp + fixpointpos));
	
	if (float[31]) begin
		result = ~result + 32'h00000001;
	end
	
end 
endmodule
