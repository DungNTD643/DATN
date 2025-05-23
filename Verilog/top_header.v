module top_header (
	clk_clk,
	driver1_0_conduit_end_pto,
	driver1_0_conduit_end_1_motor_dir,
	driver1_1_conduit_end_pto,
	driver1_1_conduit_end_1_motor_dir,
	driver1_2_conduit_end_pto,
	driver1_2_conduit_end_1_motor_dir,
	reset_reset_n,
	uart_0_external_connection_rxd,
	uart_0_external_connection_txd,
	scl,
	sda,);	

	input		clk_clk;
	output		driver1_0_conduit_end_pto;
	output		driver1_0_conduit_end_1_motor_dir;
	output		driver1_1_conduit_end_pto;
	output		driver1_1_conduit_end_1_motor_dir;
	output		driver1_2_conduit_end_pto;
	output		driver1_2_conduit_end_1_motor_dir;
	input		reset_reset_n;
	input		uart_0_external_connection_rxd;
	output		uart_0_external_connection_txd;
	inout wire scl;
	inout wire sda;

	wire i2c_serial_sda_in;
	wire i2c_serial_sda_oe;
	wire i2c_serial_scl_in;
	wire i2c_serial_scl_oe;
	PTO u0 (
		.clk_clk                           (clk_clk),                           //                        clk.clk
		.driver1_0_conduit_end_pto         (driver1_0_conduit_end_pto),         //      driver1_0_conduit_end.pto
		.driver1_0_conduit_end_1_motor_dir (driver1_0_conduit_end_1_motor_dir), //    driver1_0_conduit_end_1.motor_dir
		.driver1_1_conduit_end_pto         (driver1_1_conduit_end_pto),         //      driver1_1_conduit_end.pto
		.driver1_1_conduit_end_1_motor_dir (driver1_1_conduit_end_1_motor_dir), //    driver1_1_conduit_end_1.motor_dir
		.driver1_2_conduit_end_pto         (driver1_2_conduit_end_pto),         //      driver1_2_conduit_end.pto
		.driver1_2_conduit_end_1_motor_dir (driver1_2_conduit_end_1_motor_dir), //    driver1_2_conduit_end_1.motor_dir
		.reset_reset_n                     (reset_reset_n),                     //                      reset.reset_n
		.uart_0_external_connection_rxd    (uart_0_external_connection_rxd),    // uart_0_external_connection.rxd
		.uart_0_external_connection_txd    (uart_0_external_connection_txd),    //                           .txd
		.i2c_0_i2c_serial_sda_in           (i2c_serial_sda_in),           //           i2c_0_i2c_serial.sda_in
		.i2c_0_i2c_serial_scl_in           (i2c_serial_scl_in),           //                           .scl_in
		.i2c_0_i2c_serial_sda_oe           (i2c_serial_sda_oe),           //                           .sda_oe
		.i2c_0_i2c_serial_scl_oe           (i2c_serial_scl_oe)            //                           .scl_oe
	);
	
	assign i2c_serial_scl_in = scl;
	assign scl = i2c_serial_scl_oe ? 1'b0 : 1'bz;
	
	assign i2c_serial_sda_in = sda;
	assign sda = i2c_serial_sda_oe ? 1'b0 : 1'bz;
	
endmodule
