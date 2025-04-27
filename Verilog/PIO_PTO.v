module PIO_PTO(
    input [3:0] address,
    input chipselect,
    input clk,
    input reset_n,
    input write,
	 input read,
    input [31:0] writedata,
	 
	 output wire pto_out,
	 output reg motor_direction,
    output reg [31:0] readdata	//tín hiệu đầu ra của module, đóng vai trò phản hồi khi nios gửi tín hiệu đọc
);

	
reg [31:0] pulse_start, pulse_end, pulse_stop;  // Ba thanh ghi để lưu trữ giá trị xung
reg reset_conduit;	//reset module
wire program_end;		//tín hiệu kết thúc quá trình chạy servo
PTO_test u1(.clk(clk), .rst(reset_conduit), .pto_out(pto_out), .pulse_start(pulse_start), .pulse_stop(pulse_stop), .pulse_end(pulse_end), .program_end(program_end));
always @(posedge clk or negedge reset_n)
begin
    if (!reset_n)  // Reset bất đồng bộ, reset_n = 0 thì reset tất cả thanh ghi về 0
    begin
        pulse_start <= 32'b0;
        pulse_stop <= 32'b0;
        pulse_end <= 32'b0;
        readdata <= 32'b0;
    end
    else if (chipselect && write)  // Nếu chip được chọn và tín hiệu ghi write = 1
    begin
        case (address)  
            4'b0000: reset_conduit <= writedata;		  
            4'b0001: pulse_start <= writedata;
            4'b0010: pulse_stop <= writedata;
				4'b0011: pulse_end <= writedata;
				4'b0100: motor_direction <= writedata;
        endcase
    end
    else if (chipselect && read)  // Nếu chip được chọn và đang đọc dữ liệu
    begin
        case (address)
            4'b0000: readdata <= {31'b0, program_end};
				4'b0001: readdata <= pulse_start;
            4'b0010: readdata <= pulse_stop;
				4'b0011: readdata <= pulse_end;
        endcase
    end
	 else
	 begin
		readdata <= 32'b0;
	 end
end

endmodule
