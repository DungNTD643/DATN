module nios_uart(
	input wire clk,
	input wire reset_n,
	input wire rxd,
	output wire txd
);


	uart u0 (
		.clk_clk                        (clk),                        //                        clk.clk
		.reset_reset_n                  (reset_n),                  //                      reset.reset_n
		.uart_0_external_connection_rxd (rxd), // uart_0_external_connection.rxd
		.uart_0_external_connection_txd (txd)  //                           .txd
	);
endmodule
