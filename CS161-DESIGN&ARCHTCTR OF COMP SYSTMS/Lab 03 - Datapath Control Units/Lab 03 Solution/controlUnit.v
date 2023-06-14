module controlUnit  (
    input  wire [5:0] instr_op, 
    output wire       reg_dst,   
    output wire       branch,     
    output wire       mem_read,  
    output wire       mem_to_reg,
    output wire [1:0] alu_op,        
    output wire       mem_write, 
    output wire       alu_src,    
    output wire       reg_write 
    );

// ------------------------------
// Insert your solution below
// ------------------------------ 
reg [8:0] control_wires;

always @ (instr_op) begin
    case (instr_op)
        6'b000000: control_wires = 9'b100100010;
        6'b100011: control_wires = 9'b011110000;
        6'b101011: control_wires = 9'bx1x001000;
        6'b000100: control_wires = 9'bx0x000101;
        6'b001000: control_wires = 9'b110100010;
    endcase
end

assign {reg_dst, 
        alu_src, 
        mem_to_reg, 
        reg_write, 
        mem_read, 
        mem_write, 
        branch, 
        alu_op} = control_wires;

endmodule
