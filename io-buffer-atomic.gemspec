# frozen_string_literal: true

require_relative "lib/io/buffer/atomic/version"

Gem::Specification.new do |spec|
	spec.name = "io-buffer-atomic"
	spec.version = IO::Buffer::Atomic::VERSION
	
	spec.summary = "Atomic operations for IO::Buffer instances."
	spec.authors = ["Samuel Williams"]
	spec.license = "MIT"
	
	spec.homepage = "https://github.com/socketry/io-buffer-atomic"
	
	spec.metadata = {
		"documentation_uri" => "https://socketry.github.io/io-buffer-atomic/",
		"funding_uri" => "https://github.com/sponsors/ioquatix",
		"source_code_uri" => "https://github.com/socketry/io-buffer-atomic.git",
	}
	
	spec.files = Dir["{ext,lib}/**/*", "*.md", base: __dir__]
	spec.require_paths = ["lib"]
	
	spec.extensions = ["ext/extconf.rb"]
	
	spec.required_ruby_version = ">= 3.2"
end
