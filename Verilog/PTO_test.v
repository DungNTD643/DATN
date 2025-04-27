module PTO_test(
	input wire rst,
	input wire clk,
	input wire [31:0] pulse_end,
	input wire [31:0] pulse_stop,
	input wire [31:0] pulse_start,
	
	output reg program_end,
	output reg pto_out
//	output reg flag,
//	output reg [31:0] counter_clk,
//	output reg [31:0] counter_us,
//	output reg [31:0] counter_timeout,
//	output reg [31:0] pulse_count
);
	localparam period_max_us = 100;
	localparam T_hold_us = 15000;
	localparam period_min_us = 50;
	localparam step = 2;
	
//	localparam pulse_start = 10000;
//	localparam pulse_stop = 390000;
//	localparam pulse_end = 400000;
	
	reg rerun = 0;
	reg pre_rerun = 0;
//	reg program_end = 0;
	
	reg [31:0] period_us;			
	reg [31:0] timeout_us;		
	reg [1:0] direction;
	reg [7:0] remainder;
	
	reg [31:0] pulse_count;
	reg flag;
	reg [31:0] counter_clk;
	reg [31:0] counter_us;
	reg [31:0] counter_timeout;

	reg [31:0] previous_timeout;
	reg [31:0] previous_period;
	
	always @(posedge clk or negedge rst)
	begin
		if(rst == 0)
		begin
			counter_clk <= 0;
			counter_us <= 0;
			counter_timeout <= 0;
			previous_timeout <= T_hold_us;
			previous_period <= period_max_us;
			pto_out <= 0;
			flag <= 0;
			pulse_count <= 0;
			period_us <= period_max_us;
			timeout_us <= T_hold_us;
			direction <= 0;
			rerun <= 0;
			pre_rerun <= 0;
			program_end <= 0;
		end
		else if(rst == 1)
		begin
			if(pulse_count == pulse_end || program_end == 1)
			begin
				counter_clk <= 0;
				counter_us <= 0;
				counter_timeout <= 0;
				previous_timeout <= 0;
				previous_period <= 0;
				pto_out <= 0;
				flag <= 0;
				pulse_count <= 0;
				rerun <= 0;
				pre_rerun <= 0;
			end
			
			else
			begin
				if((previous_timeout != timeout_us) || (previous_period != period_us) || (pre_rerun != rerun))
				begin
					remainder = T_hold_us % previous_period;
					if(remainder == 0)
					begin
						pulse_count <= pulse_count + 1;
					end
					else if((remainder * 2) < previous_period)
					begin
						pulse_count <= pulse_count - 1;
					end	
					else
					begin
						pulse_count <= pulse_count;
					end
					previous_timeout <= timeout_us;
					previous_period <= period_us;
					pre_rerun <= rerun;
					counter_clk <= 3;
					counter_us <= 0;
					counter_timeout <= 0;
					pto_out <= 0;
					flag <= 0;
				end
			
				else 
				begin
					if(flag == 1)
					begin
						if(pulse_count < pulse_start)
						begin
							direction <= 0;
						end
					
						else if((pulse_count >= pulse_start) && (pulse_count < pulse_stop))
						begin
							direction <= 1;
						end
					
						else if((pulse_count >= pulse_stop) && (pulse_count < pulse_end))
						begin
							direction <= 2;
						end
						else if(pulse_count >= pulse_end)
						begin
							direction <= 3;
						end
					
						case (direction)
							0: 
							begin
								if(period_us > period_min_us)
									period_us <= period_us - step;		
								else 
								begin
									period_us <= period_min_us;
									rerun <= rerun + 1;
								end
							end
							1:
								begin
									period_us <= period_min_us;
									rerun <= rerun + 1;
								end
								
							2: 
							begin
								if(period_us < period_max_us)
									period_us <= period_us + step;
								else
								begin
									period_us <= period_max_us;
									rerun <= rerun + 1;
								end
							end
							3: 
							begin
								program_end = 1;
							end
							default: 
							begin
								period_us <= period_us;
								rerun <= rerun + 1;
							end
						endcase
					end

					else
					begin
						counter_clk = counter_clk + 1;
						if(counter_clk == 51)
						begin
							counter_clk = 1;
							counter_us = counter_us + 1;
							counter_timeout = counter_timeout + 1;
						end
					
						if(counter_timeout == timeout_us)
						begin
							counter_clk = 0;
							counter_us = 0;
							counter_timeout = 0;
							pto_out = 0;
							flag = 1;
						end
			
						if(counter_us == (period_us/2))
						begin
							pto_out = 1;
						end
			
						if(counter_us == period_us)
						begin
							pto_out = 0;
							counter_us = 0;
							pulse_count = pulse_count + 1;
							if(pulse_count == pulse_end)
							begin
								program_end = 1;
							end
						end
					end			
				end
			end
		end
	end
endmodule