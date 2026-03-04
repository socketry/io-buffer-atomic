# Getting Started

This guide explains how to use `io-buffer-atomic` for atomic operations on `IO::Buffer` instances.

## Installation

Add the gem to your project:

```bash
$ bundle add io-buffer-atomic
```

## Core Concepts

`io-buffer-atomic` extends `IO::Buffer` with atomic operations that are safe for concurrent access across threads and processes. When multiple threads or processes share memory (via `IO::Buffer`), you need atomic operations to prevent race conditions and ensure data consistency.

**Important**: Atomic operations work on raw memory bytes in host endian (native byte order). Both `:u32` and `:U32` map to the same atomic operation since they operate on the same raw memory bytes. The endianness distinction only affects how Ruby's `get_value`/`set_value` interpret bytes, not atomic operations.

Use atomic operations when you need:
- **Thread-safe counters**: Multiple threads updating shared counters without locks.
- **Process-safe coordination**: Multiple processes coordinating via shared memory.
- **Lock-free data structures**: Building concurrent data structures without mutexes.
- **Performance-critical sections**: Avoiding mutex overhead in hot paths.

## Usage

### Basic Atomic Operations

Atomic operations ensure that read-modify-write operations complete atomically, preventing race conditions:

```ruby
require "io/buffer/atomic"

# Create a shared buffer for inter-process communication:
buffer = IO::Buffer.new(64)

# Initialize a counter at offset 0:
buffer.set_value(:u32, 0, 0)

# Atomically increment the counter (default increment by 1):
result = buffer.atomic_increment(:u32, 0)
# => 1

# Atomically increment by a specific value:
result = buffer.atomic_increment(:u32, 0, 10)
# => 11

# Atomically decrement:
result = buffer.atomic_decrement(:u32, 0, 5)
# => 6

# Atomically add a value:
result = buffer.atomic_add(:u32, 0, 20)
# => 26

# Atomically subtract:
result = buffer.atomic_subtract(:u32, 0, 10)
# => 16
```

### Bitwise Operations

Atomic bitwise operations are useful for managing flags and bitmasks in shared memory:

```ruby
# Set up a flags field:
buffer.set_value(:u32, 0, 0b1010)

# Atomically perform bitwise AND:
result = buffer.atomic_and(:u32, 0, 0b1111)
# => 0b1010

# Atomically perform bitwise OR:
result = buffer.atomic_or(:u32, 0, 0b0101)
# => 0b1111

# Atomically perform bitwise XOR:
result = buffer.atomic_xor(:u32, 0, 0b1111)
# => 0b0000
```

### Atomic Load

Atomic load operations ensure you read a complete, consistent value from shared memory, preventing torn reads:

```ruby
# Set a value:
buffer.set_value(:u32, 0, 42)

# Atomically read the value (ensures no torn reads):
result = buffer.atomic_load(:u32, 0)
# => 42
```

Use `atomic_load` instead of `get_value` when reading values that may be modified by other threads or processes, as it provides memory ordering guarantees and prevents data races.

### Atomic Store

Atomic store operations ensure you write a complete value atomically to shared memory:

```ruby
# Atomically write a value:
buffer.atomic_store(:u32, 0, 42)

# Read it back:
result = buffer.atomic_load(:u32, 0)
# => 42
```

Use `atomic_store` instead of `set_value` when writing values that may be read by other threads or processes, as it provides memory ordering guarantees and prevents torn writes.

**Note**: `atomic_load` and `atomic_store` work on raw bytes in host endian, matching the atomic operations themselves. Both `:u32` and `:U32` are equivalent for atomic operations.

### Compare and Swap

Compare-and-swap operations enable lock-free algorithms and optimistic concurrency:

```ruby
# Set an initial value:
buffer.set_value(:u32, 0, 10)

# Atomically swap if current value matches expected:
swapped = buffer.atomic_compare_and_swap(:u32, 0, 10, 20)
# => true
buffer.atomic_load(:u32, 0)
# => 20

# If value doesn't match, swap fails:
swapped = buffer.atomic_compare_and_swap(:u32, 0, 10, 30)
# => false (value is now 20, not 10)
```

## Supported Operations

- `atomic_load(type, offset)` - Atomically read a value (prevents torn reads).
- `atomic_store(type, offset, value)` - Atomically write a value (prevents torn writes).
- `atomic_increment(type, offset, value = 1)` - Atomically increment a value.
- `atomic_decrement(type, offset, value = 1)` - Atomically decrement a value.
- `atomic_add(type, offset, value)` - Atomically add a value.
- `atomic_subtract(type, offset, value)` - Atomically subtract a value.
- `atomic_and(type, offset, value)` - Atomically perform bitwise AND.
- `atomic_or(type, offset, value)` - Atomically perform bitwise OR.
- `atomic_xor(type, offset, value)` - Atomically perform bitwise XOR.
- `atomic_compare_and_swap(type, offset, expected, desired)` - Atomically compare and swap.
