# frozen_string_literal: true

# Released under the MIT License.
# Copyright, 2026, by Samuel Williams.

require_relative "atomic/version"

# Check if Ruby itself provides atomic operations
if IO.const_defined?(:Buffer) && IO::Buffer.instance_methods.include?(:atomic_increment)
	# Ruby provides atomic operations, use them
else
	# Load native extension (required for shared memory support)
	begin
		require "IO_Buffer_Atomic"
	rescue LoadError => error
		warn "Could not load native atomic operations: #{error.message}"
		warn "Atomic operations will not be available."
	end
end
