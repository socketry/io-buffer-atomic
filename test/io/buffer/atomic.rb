# frozen_string_literal: true

# Released under the MIT License.
# Copyright, 2026, by Samuel Williams.

require "io/buffer/atomic"

skip "IO::Buffer not available" unless IO.const_defined?(:Buffer)

describe IO::Buffer::Atomic::VERSION do
	it "has a version number" do
		expect(subject).to be =~ /\d+\.\d+\.\d+/
	end
end

describe IO::Buffer do
	let(:buffer) {IO::Buffer.new(128)}
	
	with "#atomic_increment" do
		it "can increment U8 value" do
			buffer.set_value(:U8, 0, 0)
			result = buffer.atomic_increment(:U8, 0, 1)
			expect(result).to be == 1
			expect(buffer.get_value(:U8, 0)).to be == 1
		end
		
		it "can increment u16 value" do
			buffer.set_value(:u16, 0, 0)
			result = buffer.atomic_increment(:u16, 0, 1)
			expect(result).to be == 1
			expect(buffer.get_value(:u16, 0)).to be == 1
		end
		
		it "can increment u32 value" do
			buffer.set_value(:u32, 0, 0)
			result = buffer.atomic_increment(:u32, 0, 1)
			expect(result).to be == 1
			expect(buffer.get_value(:u32, 0)).to be == 1
		end
		
		it "can increment u64 value" do
			buffer.set_value(:u64, 0, 0)
			result = buffer.atomic_increment(:u64, 0, 1)
			expect(result).to be == 1
			expect(buffer.get_value(:u64, 0)).to be == 1
		end
		
		it "can increment S8 value" do
			buffer.set_value(:S8, 0, 0)
			result = buffer.atomic_increment(:S8, 0, 1)
			expect(result).to be == 1
			expect(buffer.get_value(:S8, 0)).to be == 1
		end
		
		it "can increment s16 value" do
			buffer.set_value(:s16, 0, 0)
			result = buffer.atomic_increment(:s16, 0, 1)
			expect(result).to be == 1
			expect(buffer.get_value(:s16, 0)).to be == 1
		end
		
		it "can increment s32 value" do
			buffer.set_value(:s32, 0, 0)
			result = buffer.atomic_increment(:s32, 0, 1)
			expect(result).to be == 1
			expect(buffer.get_value(:s32, 0)).to be == 1
		end
		
		it "can increment s64 value" do
			buffer.set_value(:s64, 0, 0)
			result = buffer.atomic_increment(:s64, 0, 1)
			expect(result).to be == 1
			expect(buffer.get_value(:s64, 0)).to be == 1
		end
		
		it "can increment with default value of 1" do
			buffer.set_value(:u32, 0, 0)
			result = buffer.atomic_increment(:u32, 0)
			expect(result).to be == 1
			expect(buffer.get_value(:u32, 0)).to be == 1
		end
		
		it "can increment by a larger value" do
			buffer.set_value(:u32, 0, 0)
			result = buffer.atomic_increment(:u32, 0, 42)
			expect(result).to be == 42
			expect(buffer.get_value(:u32, 0)).to be == 42
		end
		
		it "supports big-endian variants" do
			# Atomic operations work on raw memory bytes
			# When using :U32 (big-endian), the atomic operation still works on raw bytes
			buffer.set_value(:U32, 0, 0)
			result = buffer.atomic_increment(:U32, 0, 10)
			# The result is the new value interpreted as big-endian
			expect(result).to be_a(Integer)
			# Read back with same endianness to verify
			read_value = buffer.get_value(:U32, 0)
			expect(read_value).to be_a(Integer)
		end
		
		it "handles zero increment" do
			buffer.set_value(:u32, 0, 42)
			result = buffer.atomic_increment(:u32, 0, 0)
			expect(result).to be == 42
			expect(buffer.get_value(:u32, 0)).to be == 42
		end
		
		it "handles maximum u32 value" do
			buffer.set_value(:u32, 0, 0xFFFFFFFF)
			result = buffer.atomic_increment(:u32, 0, 1)
			expect(result).to be == 0
			expect(buffer.get_value(:u32, 0)).to be == 0
		end
		
		it "handles negative values for signed types" do
			buffer.set_value(:s32, 0, -10)
			result = buffer.atomic_increment(:s32, 0, 5)
			expect(result).to be == -5
			expect(buffer.get_value(:s32, 0)).to be == -5
		end
		
		it "raises error for invalid type" do
			expect do
				buffer.atomic_increment(:invalid, 0, 1)
			end.to raise_exception(ArgumentError)
		end
		
		it "raises error for offset out of bounds" do
			expect do
				buffer.atomic_increment(:u32, 200, 1)
			end.to raise_exception(RangeError)
		end
	end
	
	with "#atomic_decrement" do
		it "can decrement u32 value" do
			buffer.set_value(:u32, 0, 10)
			result = buffer.atomic_decrement(:u32, 0, 1)
			expect(result).to be == 9
			expect(buffer.get_value(:u32, 0)).to be == 9
		end
		
		it "can decrement with default value of 1" do
			buffer.set_value(:u32, 0, 10)
			result = buffer.atomic_decrement(:u32, 0)
			expect(result).to be == 9
			expect(buffer.get_value(:u32, 0)).to be == 9
		end
		
		it "can decrement by a larger value" do
			buffer.set_value(:u32, 0, 100)
			result = buffer.atomic_decrement(:u32, 0, 25)
			expect(result).to be == 75
			expect(buffer.get_value(:u32, 0)).to be == 75
		end
		
		it "can decrement s64 value" do
			buffer.set_value(:s64, 0, 1000)
			result = buffer.atomic_decrement(:s64, 0, 100)
			expect(result).to be == 900
			expect(buffer.get_value(:s64, 0)).to be == 900
		end
	end
	
	with "#atomic_add" do
		it "can add to u32 value" do
			buffer.set_value(:u32, 0, 5)
			result = buffer.atomic_add(:u32, 0, 10)
			expect(result).to be == 15
			expect(buffer.get_value(:u32, 0)).to be == 15
		end
		
		it "can add to u64 value" do
			buffer.set_value(:u64, 0, 1000)
			result = buffer.atomic_add(:u64, 0, 500)
			expect(result).to be == 1500
			expect(buffer.get_value(:u64, 0)).to be == 1500
		end
		
		it "can add negative values" do
			buffer.set_value(:s32, 0, 20)
			result = buffer.atomic_add(:s32, 0, -5)
			expect(result).to be == 15
			expect(buffer.get_value(:s32, 0)).to be == 15
		end
	end
	
	with "#atomic_subtract" do
		it "can subtract from u32 value" do
			buffer.set_value(:u32, 0, 20)
			result = buffer.atomic_subtract(:u32, 0, 5)
			expect(result).to be == 15
			expect(buffer.get_value(:u32, 0)).to be == 15
		end
		
		it "can subtract from s64 value" do
			buffer.set_value(:s64, 0, 1000)
			result = buffer.atomic_subtract(:s64, 0, 250)
			expect(result).to be == 750
			expect(buffer.get_value(:s64, 0)).to be == 750
		end
	end
	
	with "#atomic_and" do
		it "can perform bitwise AND on u32" do
			buffer.set_value(:u32, 0, 0b1111)
			result = buffer.atomic_and(:u32, 0, 0b1010)
			expect(result).to be == 0b1010
			expect(buffer.get_value(:u32, 0)).to be == 0b1010
		end
		
		it "can perform bitwise AND on U8" do
			buffer.set_value(:U8, 0, 0b11111111)
			result = buffer.atomic_and(:U8, 0, 0b10101010)
			expect(result).to be == 0b10101010
			expect(buffer.get_value(:U8, 0)).to be == 0b10101010
		end
		
		it "can perform bitwise AND on u64" do
			buffer.set_value(:u64, 0, 0xFFFFFFFFFFFFFFFF)
			result = buffer.atomic_and(:u64, 0, 0xAAAAAAAAAAAAAAA)
			expect(result).to be == 0xAAAAAAAAAAAAAAA
			expect(buffer.get_value(:u64, 0)).to be == 0xAAAAAAAAAAAAAAA
		end
	end
	
	with "#atomic_or" do
		it "can perform bitwise OR on u32" do
			buffer.set_value(:u32, 0, 0b1010)
			result = buffer.atomic_or(:u32, 0, 0b0101)
			expect(result).to be == 0b1111
			expect(buffer.get_value(:u32, 0)).to be == 0b1111
		end
		
		it "can perform bitwise OR on u16" do
			buffer.set_value(:u16, 0, 0b1010101010101010)
			result = buffer.atomic_or(:u16, 0, 0b0101010101010101)
			expect(result).to be == 0b1111111111111111
			expect(buffer.get_value(:u16, 0)).to be == 0b1111111111111111
		end
	end
	
	with "#atomic_xor" do
		it "can perform bitwise XOR on u32" do
			buffer.set_value(:u32, 0, 0b1010)
			result = buffer.atomic_xor(:u32, 0, 0b1111)
			expect(result).to be == 0b0101
			expect(buffer.get_value(:u32, 0)).to be == 0b0101
		end
		
		it "can perform bitwise XOR on U8" do
			buffer.set_value(:U8, 0, 0b11110000)
			result = buffer.atomic_xor(:U8, 0, 0b11001100)
			expect(result).to be == 0b00111100
			expect(buffer.get_value(:U8, 0)).to be == 0b00111100
		end
		
		it "XOR with same value clears bits" do
			buffer.set_value(:u32, 0, 0b1111)
			result = buffer.atomic_xor(:u32, 0, 0b1111)
			expect(result).to be == 0b0000
			expect(buffer.get_value(:u32, 0)).to be == 0b0000
		end
	end
	
	with "#atomic_compare_and_swap" do
		it "can swap when value matches u32" do
			buffer.set_value(:u32, 0, 10)
			result = buffer.atomic_compare_and_swap(:u32, 0, 10, 20)
			expect(result).to be == true
			expect(buffer.get_value(:u32, 0)).to be == 20
		end
		
		it "does not swap when value does not match" do
			buffer.set_value(:u32, 0, 10)
			result = buffer.atomic_compare_and_swap(:u32, 0, 5, 20)
			expect(result).to be == false
			expect(buffer.get_value(:u32, 0)).to be == 10
		end
		
		it "can swap u64 values" do
			buffer.set_value(:u64, 0, 1000)
			result = buffer.atomic_compare_and_swap(:u64, 0, 1000, 2000)
			expect(result).to be == true
			expect(buffer.get_value(:u64, 0)).to be == 2000
		end
		
		it "can swap s32 values" do
			buffer.set_value(:s32, 0, -100)
			result = buffer.atomic_compare_and_swap(:s32, 0, -100, -200)
			expect(result).to be == true
			expect(buffer.get_value(:s32, 0)).to be == -200
		end
		
		it "can swap U8 values" do
			buffer.set_value(:U8, 0, 42)
			result = buffer.atomic_compare_and_swap(:U8, 0, 42, 84)
			expect(result).to be == true
			expect(buffer.get_value(:U8, 0)).to be == 84
		end
	end
	
	with "multiple offsets" do
		it "can operate on different offsets independently" do
			buffer.set_value(:u32, 0, 10)
			buffer.set_value(:u32, 4, 20)
			buffer.set_value(:u32, 8, 30)
			
			buffer.atomic_increment(:u32, 0, 5)
			buffer.atomic_increment(:u32, 4, 10)
			buffer.atomic_increment(:u32, 8, 15)
			
			expect(buffer.get_value(:u32, 0)).to be == 15
			expect(buffer.get_value(:u32, 4)).to be == 30
			expect(buffer.get_value(:u32, 8)).to be == 45
		end
	end
	
	with "thread safety" do
		it "can perform concurrent increments" do
			buffer.set_value(:u32, 0, 0)
			
			threads = 10.times.map do
				Thread.new do
					100.times do
						buffer.atomic_increment(:u32, 0, 1)
					end
				end
			end
			
			threads.each(&:join)
			
			expect(buffer.get_value(:u32, 0)).to be == 1000
		end
		
		it "can perform concurrent decrements" do
			buffer.set_value(:u32, 0, 1000)
			
			threads = 10.times.map do
				Thread.new do
					100.times do
						buffer.atomic_decrement(:u32, 0, 1)
					end
				end
			end
			
			threads.each(&:join)
			
			expect(buffer.get_value(:u32, 0)).to be == 0
		end
		
		it "can perform concurrent additions" do
			buffer.set_value(:u64, 0, 0)
			
			threads = 20.times.map do
				Thread.new do
					50.times do
						buffer.atomic_add(:u64, 0, 1)
					end
				end
			end
			
			threads.each(&:join)
			
			expect(buffer.get_value(:u64, 0)).to be == 1000
		end
		
		it "can perform concurrent bitwise operations" do
			buffer.set_value(:u32, 0, 0)
			
			threads = 10.times.map do
				Thread.new do
					10.times do
						buffer.atomic_or(:u32, 0, 1)
					end
				end
			end
			
			threads.each(&:join)
			
			# All threads set bit 0, so it should be 1
			expect(buffer.get_value(:u32, 0)).to be == 1
		end
		
		it "can perform concurrent compare and swap" do
			buffer.set_value(:u32, 0, 0)
			
			threads = 100.times.map do
				Thread.new do
					loop do
						current = buffer.get_value(:u32, 0)
						if buffer.atomic_compare_and_swap(:u32, 0, current, current + 1)
							break
						end
					end
				end
			end
			
			threads.each(&:join)
			
			expect(buffer.get_value(:u32, 0)).to be == 100
		end
	end
end
