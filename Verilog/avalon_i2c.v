module avalon_i2c(
	input wire clk,
	input wire reset_n,
	
	
	inout wire sda,
	inout wire scl
);
	wire i2c_serial_sda_in;
	wire i2c_serial_sda_oe;
	wire i2c_serial_scl_in;
	wire i2c_serial_scl_oe;
	i2c u0 (
		.clk_clk                 (clk),                 //              clk.clk
		.reset_reset_n           (reset_n),           //            reset.reset_n
		.i2c_0_i2c_serial_sda_in (i2c_serial_sda_in), // i2c_0_i2c_serial.sda_in
		.i2c_0_i2c_serial_scl_in (i2c_serial_scl_in), //                 .scl_in
		.i2c_0_i2c_serial_sda_oe (i2c_serial_sda_oe), //                 .sda_oe
		.i2c_0_i2c_serial_scl_oe (i2c_serial_scl_oe)  //                 .scl_oe
	);
	
	assign i2c_serial_scl_in = scl;
	assign scl = i2c_serial_scl_oe ? 1'b0 : 1'bz;
	
	assign i2c_serial_sda_in = sda;
	assign sda = i2c_serial_sda_oe ? 1'b0 : 1'bz;

endmodule