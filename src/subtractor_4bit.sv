module subtractor_4bit (
	input  logic [3:0] A, B,
	output logic [3:0] D
);
	adder_4bit sub_inst(
		.A(A),
		.B(~B),
		.cin(1'b1),
		.S(D),
		.cout()
	);
endmodule
