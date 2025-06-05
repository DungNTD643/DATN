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
	scl_1,
	sda_1,
	scl_2,
	sda_2,
	scl_3,
	sda_3,
	pio_0_external_connection_export,
	pio_1_external_connection_export);	

	input		clk_clk;
	output	driver1_0_conduit_end_pto;
	output	driver1_0_conduit_end_1_motor_dir;
	output	driver1_1_conduit_end_pto;
	output	driver1_1_conduit_end_1_motor_dir;
	output	driver1_2_conduit_end_pto;
	output	driver1_2_conduit_end_1_motor_dir;
	input		reset_reset_n;
	input		uart_0_external_connection_rxd;
	output	uart_0_external_connection_txd;
	input		pio_0_external_connection_export;	
	input		pio_1_external_connection_export;	
	
	inout wire scl_1;
	inout wire sda_1;
	inout wire scl_2;
	inout wire sda_2;
	inout wire scl_3;
	inout wire sda_3;

	wire i2c_0_serial_sda_in;
	wire i2c_0_serial_sda_oe;
	wire i2c_0_serial_scl_in;
	wire i2c_0_serial_scl_oe;
	
	wire i2c_1_serial_sda_in;
	wire i2c_1_serial_sda_oe;
	wire i2c_1_serial_scl_in;
	wire i2c_1_serial_scl_oe;
	
	wire i2c_2_serial_sda_in;
	wire i2c_2_serial_sda_oe;
	wire i2c_2_serial_scl_in;
	wire i2c_2_serial_scl_oe;
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
		.pio_0_external_connection_export  (pio_0_external_connection_export),
		.pio_1_external_connection_export  (pio_1_external_connection_export),
		.i2c_0_i2c_serial_sda_in           (i2c_0_serial_sda_in),           //           i2c_0_i2c_serial.sda_in
		.i2c_0_i2c_serial_scl_in           (i2c_0_serial_scl_in),           //                           .scl_in
		.i2c_0_i2c_serial_sda_oe           (i2c_0_serial_sda_oe),           //                           .sda_oe
		.i2c_0_i2c_serial_scl_oe           (i2c_0_serial_scl_oe),            //                           .scl_oe

		.i2c_1_i2c_serial_sda_in           (i2c_1_serial_sda_in),           //           i2c_0_i2c_serial.sda_in
		.i2c_1_i2c_serial_scl_in           (i2c_1_serial_scl_in),           //                           .scl_in
		.i2c_1_i2c_serial_sda_oe           (i2c_1_serial_sda_oe),           //                           .sda_oe
		.i2c_1_i2c_serial_scl_oe           (i2c_1_serial_scl_oe),            //                           .scl_oe

		.i2c_2_i2c_serial_sda_in           (i2c_2_serial_sda_in),           //           i2c_0_i2c_serial.sda_in
		.i2c_2_i2c_serial_scl_in           (i2c_2_serial_scl_in),           //                           .scl_in
		.i2c_2_i2c_serial_sda_oe           (i2c_2_serial_sda_oe),           //                           .sda_oe
		.i2c_2_i2c_serial_scl_oe           (i2c_2_serial_scl_oe)            //                           .scl_oe
	);
	
	assign i2c_0_serial_scl_in = scl_1;
	assign scl_1 = i2c_0_serial_scl_oe ? 1'b0 : 1'bz;
	
	assign i2c_0_serial_sda_in = sda_1;
	assign sda_1 = i2c_0_serial_sda_oe ? 1'b0 : 1'bz;
	
	assign i2c_1_serial_scl_in = scl_2;
	assign scl_2 = i2c_1_serial_scl_oe ? 1'b0 : 1'bz;
	
	assign i2c_1_serial_sda_in = sda_2;
	assign sda_2 = i2c_1_serial_sda_oe ? 1'b0 : 1'bz;
	
	assign i2c_2_serial_scl_in = scl_3;
	assign scl_3 = i2c_2_serial_scl_oe ? 1'b0 : 1'bz;
	
	assign i2c_2_serial_sda_in = sda_3;
	assign sda_3 = i2c_2_serial_sda_oe ? 1'b0 : 1'bz;
	
endmodule
