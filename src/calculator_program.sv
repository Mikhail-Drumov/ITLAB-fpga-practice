module calculator_program(
	input  logic       rst,
	input  logic       clk,
	input  logic [3:0] KEY,
	input  logic [9:0] SW,
	output logic [7:0] LEDG,
	output logic [9:0] LEDR
);
	logic [3:0] A_reg, B_reg;
	logic operation;
	
	always @(posedge clk) begin
		if (rst) begin
			A_reg <= 4'b0;
			B_reg <= 4'b0;
			operation <= 1'b0;
		end else begin
			if (~KEY[0]) A_reg <= SW[3:0];
			if (~KEY[1]) B_reg <= SW[3:0];
			if (~KEY[2]) operation <= 1'b0;
			if (~KEY[3]) operation <= 1'b1;
		end
	end

	calculator calc(
		.SW({operation, B_reg, A_reg}),
		.LEDG(LEDG)
	);
	
	assign LEDR[3:0] = A_reg;
	assign LEDR[7:4] = B_reg;
endmodule