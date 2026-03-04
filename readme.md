# IO::Buffer::Atomic

Provides atomic operations for `IO::Buffer` instances, including increment, decrement, add, subtract, and bitwise operations.

[![Development Status](https://github.com/socketry/io-buffer-atomic/workflows/Test/badge.svg)](https://github.com/socketry/io-buffer-atomic/actions?workflow=Test)

## Features

  - **Atomic Operations**: Thread-safe atomic operations on `IO::Buffer` values.
  - **Multiple Types**: Supports `:u8`, `:u16`, `:u32`, `:u64`, `:i8`, `:i16`, `:i32`, `:i64`.
  - **Native Extension**: Uses C11 atomic operations when available for maximum performance.

## Usage

Please see the [project documentation](https://socketry.github.io/io-buffer-atomic/) for more details.

  - [Getting Started](https://socketry.github.io/io-buffer-atomic/guides/getting-started/index) - This guide explains how to use `io-buffer-atomic` for atomic operations on `IO::Buffer` instances.

## Releases

Please see the [project releases](https://socketry.github.io/io-buffer-atomic/releases/index) for all releases.

### v0.1.0

## Contributing

We welcome contributions to this project.

1.  Fork it.
2.  Create your feature branch (`git checkout -b my-new-feature`).
3.  Commit your changes (`git commit -am 'Add some feature'`).
4.  Push to the branch (`git push origin my-new-feature`).
5.  Create new Pull Request.

### Developer Certificate of Origin

In order to protect users of this project, we require all contributors to comply with the [Developer Certificate of Origin](https://developercertificate.org/). This ensures that all contributions are properly licensed and attributed.

### Community Guidelines

This project is best served by a collaborative and respectful environment. Treat each other professionally, respect differing viewpoints, and engage constructively. Harassment, discrimination, or harmful behavior is not tolerated. Communicate clearly, listen actively, and support one another. If any issues arise, please inform the project maintainers.
