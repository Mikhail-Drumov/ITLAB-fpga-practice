module adder_4bit (
	input  logic [3:0] A, B,
	input  logic		 cin,
	output logic [3:0] S,
	output logic		 cout
);
	// verilator lint_off UNOPTFLAT
	logic [4:0] carry;
	// verilator lint_on UNOPTFLAT
	assign carry[0] = cin;
	assign cout = carry[4];
	
	genvar i;
	generate
		for (i = 0; i < 4; i++) begin : full_adders
			full_adder fa_inst(
				.a(A[i]), .b(B[i]), .cin(carry[i]),
				.sum(S[i]), .cout(carry[i + 1])
			);
		end
	endgenerate
endmodule