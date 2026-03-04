#!/usr/bin/env ruby
# frozen_string_literal: true

# Released under the MIT License.
# Copyright, 2026, by Samuel Williams.

return if RUBY_DESCRIPTION =~ /jruby/

require "mkmf"

gem_name = File.basename(__dir__)
extension_name = "IO_Buffer_Atomic"

append_cflags(["-Wall", "-Wno-unknown-pragmas", "-std=c11"])

if ENV.key?("RUBY_DEBUG")
	$stderr.puts "Enabling debug mode..."
	
	append_cflags(["-DRUBY_DEBUG", "-O0"])
end

$srcs = ["io/buffer/atomic.c"]
$VPATH << "$(srcdir)/io/buffer"

have_header("ruby/io/buffer.h")
have_header("ruby/atomic.h")

# Check for atomic operations support
# Ruby's atomic.h handles platform detection, but we also need stdatomic.h for typed operations
if have_header("stdatomic.h")
	have_func("atomic_fetch_add", "stdatomic.h")
elsif have_func("__atomic_add_fetch", "stdint.h")
	# GCC built-in atomics are available
elsif have_func("_InterlockedExchangeAdd", "intrin.h")
	# MSVC intrinsics are available
else
	$stderr.puts "Warning: Atomic operations may not be available."
end

if ENV.key?("RUBY_SANITIZE")
	$stderr.puts "Enabling sanitizers..."
	
	# Add address and undefined behaviour sanitizers:
	append_cflags(["-fsanitize=address", "-fsanitize=undefined", "-fno-omit-frame-pointer"])
	$LDFLAGS << " -fsanitize=address -fsanitize=undefined"
end

create_header

# Generate the makefile to compile the native binary into `lib`:
create_makefile(extension_name)
