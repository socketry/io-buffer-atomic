# frozen_string_literal: true

# Released under the MIT License.
# Copyright, 2026, by Samuel Williams.

require_relative "environment"

Warning[:experimental] = false

require "covered/sus"
include Covered::Sus
