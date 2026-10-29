module calculator(
	input  logic [8:0] SW,
	output logic [7:0] LEDG
);
	logic [3:0] res1, res2;
	
	adder_4bit add(
		.A(SW[3:0]),
		.B(SW[7:4]),
		.cin(1'b0),
		.S(res1),
		.cout()
	);
	
	subtractor_4bit sub(
		.A(SW[3:0]),
		.B(SW[7:4]),
		.D(res2)
	);
	
	assign LEDG[3:0] = SW[8] ? res2 : res1;

endmodule
