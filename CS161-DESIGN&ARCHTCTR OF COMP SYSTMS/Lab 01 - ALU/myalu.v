//=========================================================================
// Name & Email must be EXACTLY as in Gradescope roster!
// Name: Aidan Lopez
// Email: alope396@ucr.edu
// 
// Assignment name: Lab 1
// Lab section: 021
// TA: Quan Fan
// 
// I hereby certify that I have not received assistance on this assignment,
// or used code, from ANY outside source other than the instruction team
// (apart from what was provided in the starter file).
//
//=========================================================================

`timescale 1ns / 1ps

//  Constant definitions 

module myalu # ( parameter NUMBITS = 16 ) (
    input wire clk, 
    input wire reset ,  
    input  wire[NUMBITS-1:0] A, 
    input  wire[NUMBITS-1:0] B, 
    input wire [2:0]opcode, 
    output reg [NUMBITS-1:0] result,  
    output reg carryout ,
    output reg overflow , 
    output reg zero  );

// ------------------------------
// Insert your solution below
// ------------------------------ 

    wire A_sign, B_sign;
    assign A_sign = A[NUMBITS-1];
    assign B_sign = B[NUMBITS-1];

    always @(posedge clk)
    begin
        carryout = 0;
        overflow = 0;

        if (reset)
        begin 
            result = 0;
        end
        else
        begin
            case (opcode)
            3'b000:
            begin
                {carryout, result} = A + B;
            end
			3'b001: //signed add
            begin
				result  = A + B;
				overflow = (~A_sign & ~B_sign &  result[NUMBITS-1]) | 
				           ( A_sign &  B_sign & ~result[NUMBITS-1]);
			end
			3'b010:     //unsigned sub
            begin
				result = A - B;
				carryout = B > A;
			end
			3'b011:     //signed sub
            begin
				result  = A - B;
				overflow = (~A_sign &  B_sign &  result[NUMBITS-1]) |
				           ( A_sign & ~B_sign & ~result[NUMBITS-1]);
			end
			3'b100: 
            begin
                result = A &  B;    //bitwise and
            end
			3'b101:
            begin
                result = A |  B;    //bitwise OR
            end
			3'b110:
            begin
                result = A ^  B;    //bitwise XOR
            end
			3'b111:
            begin
                result = A >> 1;    //divide A by 2
            end
            endcase
        end
        zero = result == 0;
    end
endmodule
