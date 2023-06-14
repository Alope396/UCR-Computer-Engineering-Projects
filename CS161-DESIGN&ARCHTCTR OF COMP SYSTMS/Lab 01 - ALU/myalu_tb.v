//=========================================================================
// Name & Email must be EXACTLY as in Gradescope roster!
// Name: Aidan Lopez
// Email: Alope396@ucr.edu
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

module myalu_tb;
    parameter NUMBITS = 8;

    // Inputs
    reg clk;
    reg reset;
    reg [NUMBITS-1:0] A;
    reg [NUMBITS-1:0] B;
    reg [2:0] opcode;

    // Outputs
    wire [NUMBITS-1:0] result;
    reg [NUMBITS-1:0] R;
    wire carryout;
    wire overflow;
    wire zero;

    // -------------------------------------------------------
    // Instantiate the Unit Under Test (UUT)
    // -------------------------------------------------------
    myalu #(.NUMBITS(NUMBITS)) uut (
        .clk(clk),
        .reset(reset) ,  
        .A(A), 
        .B(B), 
        .opcode(opcode), 
        .result(result), 
        .carryout(carryout), 
        .overflow(overflow), 
        .zero(zero)
    );

      initial begin 
    
     clk = 0; reset = 1; #50; 
     clk = 1; reset = 1; #50; 
     clk = 0; reset = 0; #50; 
     clk = 1; reset = 0; #50; 
         
     forever begin 
        clk = ~clk; #50; 
     end 
     
    end 
    
    integer totalTests = 0;
    integer failedTests = 0;
    initial begin // Test suite
        // Reset
        @(negedge reset); // Wait for reset to be released (from another initial block)
        @(posedge clk); // Wait for first clock out of reset 
        #10; // Wait 

        // Additional test cases
        // ---------------------------------------------
        // Testing unsigned additions 
        // --------------------------------------------- 
        $write("Test Group 1: Testing unsigned additions ... \n");
        opcode = 3'b000; 
        totalTests = totalTests + 1;
        $write("\tTest Case 1.1: Unsigned Add ... ");
        A = 8'hFF;
        B = 8'h01;
        R = 8'h00; 
        #100; // Wait 
        if (R != result || zero != 1'b1 || carryout != 1'b1) begin
            $write("failed\n");
            failedTests = failedTests + 1;
        end else begin
            $write("passed\n");
        end
        #10; // Wait 

        // ---------------------------------------------
        // Testing unsigned subs 
        // --------------------------------------------- 
        $write("Test Group 2: Testing unsigned subs ...\n");
        opcode = 3'b010; 
        totalTests = totalTests + 1;
        $write("\tTest Case 1.1: Unsigned Add ... ");
        A = 8'hFF;
        B = 8'h0F;  
        R = 8'hF0;  
        #100; // Wait 
        if (R != result || zero != 1'b0 || carryout != 1'b0) begin
            $write("failed\n");
            failedTests = failedTests + 1;
        end else begin
            $write("passed\n");
        end
        #10; // Wait 

        // ---------------------------------------------
        // Testing signed adds 
        // --------------------------------------------- 
        $write("Test Group 3: Testing signed adds ...\n");
        opcode = 3'b001; 
		totalTests = totalTests + 1;
        $write("\tTest Case 1.1: Unsigned Add ... ");
        A = 8'h09;
        B = 8'h04;
        R = 8'h0D; 
        #100; // Wait 
        if (R != result || zero != 1'b0 || overflow != 1'b0) begin
            $write("failed\n");
            failedTests = failedTests + 1;
        end else begin
            $write("passed\n");
        end
        #10; // Wait 

        // ---------------------------------------------
        // Testing signed subs 
        // --------------------------------------------- 
        $write("Test Group 4: Testing signed subs ...\n");
        opcode = 3'b011; 
                
		totalTests = totalTests + 1;
        $write("\tTest Case 1.1: Unsigned Add ... ");
        A = 8'h0F;
        B = 8'h0F;
        R = 8'h00; 
        #100; // Wait 
        if (R != result || zero != 1'b1 || overflow != 1'b0) begin
            $write("failed\n");
            failedTests = failedTests + 1;
        end else begin
            $write("passed\n");
        end
        #10; // Wait 

        // ---------------------------------------------
        // Testing ANDS 
        // --------------------------------------------- 
        $write("Test Group 5: Testing ANDs ...\n");
        opcode = 3'b100; 
                
		totalTests = totalTests + 1;
        $write("\tTest Case 1.1: Unsigned Add ... ");
        A = 8'hFF;
        B = 8'h01;
        R = 8'h01; 
        #100; // Wait 
        if (R != result || zero != 1'b0 || carryout != 1'b0 || overflow != 1'b0) begin
            $write("failed\n");
            failedTests = failedTests + 1;
        end else begin
            $write("passed\n");
        end
        #10; // Wait 

        // ----------------------------------------
        // ORs 
        // ---------------------------------------- 
        $write("Test Group 6: Testing ORs ...\n");
        opcode = 3'b101; 
        
		totalTests = totalTests + 1;
        $write("\tTest Case 1.1: Unsigned Add ... ");
        A = 8'hFE;
        B = 8'h01;
        R = 8'hFF; 
        #100; // Wait 
        if (R != result || zero != 1'b0 || carryout != 1'b0 || overflow != 1'b0) begin
            $write("failed\n");
            failedTests = failedTests + 1;
        end else begin
            $write("passed\n");
        end
        #10; // Wait 
        
        // ----------------------------------------
        // XORs 
        // ---------------------------------------- 
        $write("Test Group 7: Testing XORs ...\n");
        opcode = 3'b110; 
        
		totalTests = totalTests + 1;
        $write("\tTest Case 1.1: Unsigned Add ... ");
        A = 8'hFF;
        B = 8'h01;
        R = 8'hFE; 
        #100; // Wait 
        if (R != result || zero != 1'b0 || carryout != 1'b0 || overflow != 1'b0) begin
            $write("failed\n");
            failedTests = failedTests + 1;
        end else begin
            $write("passed\n");
        end
        #10; // Wait 
        
        // ----------------------------------------
        // Div 2 
        // ----------------------------------------
        $write("Test Group 8: Testing DIV 2 ...\n");
        opcode = 3'b111; 
        
		totalTests = totalTests + 1;
        $write("\tTest Case 1.1: Unsigned Add ... ");
        A = 8'hFE;
        R = 8'h7C; 
        #100; // Wait 
        if (R != result || zero != 1'b0 || carryout != 1'b0 || overflow != 1'b0) begin
            $write("failed\n");
            failedTests = failedTests + 1;
        end else begin
            $write("passed\n");
        end
        #10; // Wait 

        // -------------------------------------------------------
        // End testing
        // -------------------------------------------------------
        $write("\n-------------------------------------------------------");
        $write("\nTesting complete\nPassed %0d / %0d tests", totalTests-failedTests,totalTests);
        $write("\n-------------------------------------------------------");
    end
endmodule
