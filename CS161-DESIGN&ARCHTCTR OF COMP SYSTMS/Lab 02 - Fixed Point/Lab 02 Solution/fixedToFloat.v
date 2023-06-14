`timescale 1ns / 1ps

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

`define MANTISSA_SIZE 23
`define BIAS 127

module fixedToFloat(
  input wire clk, 
  input wire rst , 
  input wire[31:0] targetnumber, 
  input wire[4:0] fixpointpos , 
  output reg[31:0] result );

// Your  Implementation 
integer leadingoneindex;
reg[31:0] mask;

reg sign;
reg[7:0] biasedexponent;
reg[22:0] mantissa;
reg[31:0] fixednumber;

// -------------------------------------------	
// Register the results 
// -------------------------------------------

always @(*) begin 	

	sign = targetnumber[31];
	fixednumber = sign == 1'b1 ? ~targetnumber + 32'h00000001 : targetnumber;
	
	leadingoneindex = 32;
	while (leadingoneindex >=0 && fixednumber[leadingoneindex-1] == 1'b0)
		leadingoneindex = leadingoneindex - 1;
	
	biasedexponent = `BIAS + leadingoneindex - 1 - fixpointpos;
	mantissa = (leadingoneindex <= `MANTISSA_SIZE) ? fixednumber << (`MANTISSA_SIZE - leadingoneindex + 1) : fixednumber >> (leadingoneindex - 1 - `MANTISSA_SIZE);
	result = {sign, biasedexponent, mantissa};
end 
endmodule
