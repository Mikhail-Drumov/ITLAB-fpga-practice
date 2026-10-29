module full_adder(
	input logic a,
	input logic b,
	input logic cin,
	output logic cout,
	output logic sum
);
	assign cout = a & (b | cin) | b & cin;
	assign sum = a ^ b ^ cin;
endmodule