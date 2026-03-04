# Agent

## Context

This section provides links to documentation from installed packages. It is automatically generated and may be updated by running `bake agent:context:install`.

**Important:** Before performing any code, documentation, or analysis tasks, always read and apply the full content of any relevant documentation referenced in the following sections. These context files contain authoritative standards and best practices for documentation, code style, and project-specific workflows. **Do not proceed with any actions until you have read and incorporated the guidance from relevant context files.**

**Setup Instructions:** If the referenced files are not present or if dependencies have been updated, run `bake agent:context:install` to install the latest context files.

### agent-context

Install and manage context files from Ruby gems.

#### [Getting Started](.context/agent-context/getting-started.md)

This guide explains how to use `agent-context`, a tool for discovering and installing contextual information from Ruby gems to help AI agents.

### async

A concurrency framework for Ruby.

#### [Getting Started](.context/async/getting-started.md)

This guide shows how to add async to your project and run code asynchronously.

#### [Scheduler](.context/async/scheduler.md)

This guide gives an overview of how the scheduler is implemented.

#### [Tasks](.context/async/tasks.md)

This guide explains how asynchronous tasks work and how to use them.

#### [Best Practices](.context/async/best-practices.md)

This guide gives an overview of best practices for using Async.

#### [Debugging](.context/async/debugging.md)

This guide explains how to debug issues with programs that use Async.

#### [Thread safety](.context/async/thread-safety.md)

This guide explains thread safety in Ruby, focusing on fibers and threads, common pitfalls, and best practices to avoid problems like data corruption, race conditions, and deadlocks.

### async-container-supervisor

A supervisor for managing multiple container processes.

#### [Getting Started](.context/async-container-supervisor/getting-started.md)

This guide explains how to get started with `async-container-supervisor` to supervise and monitor worker processes in your Ruby applications.

#### [Memory Monitor](.context/async-container-supervisor/memory-monitor.md)

This guide explains how to use the <code class="language-ruby">Async::Container::Supervisor::MemoryMonitor</code> to detect and restart workers that exceed memory limits or develop memory leaks.

#### [Process Monitor](.context/async-container-supervisor/process-monitor.md)

This guide explains how to use the <code class="language-ruby">Async::Container::Supervisor::ProcessMonitor</code> to log CPU and memory metrics for your worker processes.

### async-http

A HTTP client and server library.

#### [Getting Started](.context/async-http/getting-started.md)

This guide explains how to get started with `Async::HTTP`.

#### [Testing](.context/async-http/testing.md)

This guide explains how to use `Async::HTTP` clients and servers in your tests.

### async-http-cache

Standard-compliant cache for async-http.

#### [Getting Started](.context/async-http-cache/getting-started.md)

This guide explains how to get started with `async-http-cache`, a cache middleware for `Async::HTTP` clients and servers.

### async-service

A service layer for Async.

#### [Getting Started](.context/async-service/getting-started.md)

This guide explains how to get started with `async-service` to create and run services in Ruby.

#### [Container Policies](.context/async-service/policies.md)

This guide explains how to configure container policies for your services and understand the default failure handling behavior.

#### [Service Architecture](.context/async-service/service-architecture.md)

This guide explains the key architectural components of `async-service` and how they work together to provide a clean separation of concerns.

#### [Best Practices](.context/async-service/best-practices.md)

This guide outlines recommended patterns and practices for building robust, maintainable services with `async-service`.

#### [Deployment](.context/async-service/deployment.md)

This guide explains how to deploy `async-service` applications using systemd and Kubernetes. We'll use a simple example service to demonstrate deployment configurations.

### bake

A replacement for rake with a simpler syntax.

#### [Getting Started](.context/bake/getting-started.md)

This guide gives a general overview of `bake` and how to use it.

#### [Command Line Interface](.context/bake/command-line-interface.md)

The `bake` command is broken up into two main functions: `list` and `call`.

#### [Project Integration](.context/bake/project-integration.md)

This guide explains how to add `bake` to a Ruby project.

#### [Gem Integration](.context/bake/gem-integration.md)

This guide explains how to add `bake` to a Ruby gem and export standardised tasks for use by other gems and projects.

#### [Input and Output](.context/bake/input-and-output.md)

`bake` has built in tasks for reading input and writing output in different formats. While this can be useful for general processing, there are some limitations, notably that rich object representations like `json` and `yaml` often don't support stream processing.

### bake-gem

Release management for Ruby gems.

#### [Getting Started](.context/bake-gem/getting-started.md)

This guide explains how to use `bake-gem` to release gems safely and efficiently.

### bake-releases

Releases document management.

#### [Getting Started](.context/bake-releases/getting-started.md)

This guide explains how to use `bake-releases` to manage release documentation for your Ruby gem.

### covered

A modern approach to code coverage.

#### [Getting Started](.context/covered/getting-started.md)

This guide explains how to get started with `covered` and integrate it with your test suite.

#### [Configuration](.context/covered/configuration.md)

This guide will help you to configure covered for your project's specific requirements.

### decode

Code analysis for documentation generation.

#### [Getting Started](.context/decode/getting-started.md)

This guide explains how to use `decode` for source code analysis.

#### [Documentation Coverage](.context/decode/documentation-coverage.md)

This guide explains how to test and monitor documentation coverage in your Ruby projects using the Decode gem's built-in bake tasks.

#### [Ruby Documentation](.context/decode/ruby-documentation.md)

This guide covers documentation practices and pragmas supported by the Decode gem for documenting Ruby code. These pragmas provide structured documentation that can be parsed and used to generate API documentation and achieve complete documentation coverage.

### falcon

A fast, asynchronous, rack-compatible web server.

#### [Getting Started](.context/falcon/getting-started.md)

This guide gives an overview of how to use Falcon for running Ruby web applications.

#### [Rails Integration](.context/falcon/rails-integration.md)

This guide explains how to host Rails applications with Falcon.

#### [Deployment](.context/falcon/deployment.md)

This guide explains how to deploy applications using the Falcon web server. It covers the recommended deployment methods, configuration options, and examples for different environments, including systemd and kubernetes.

#### [Performance Tuning](.context/falcon/performance-tuning.md)

This guide explains the performance characteristics of Falcon.

#### [WebSockets](.context/falcon/websockets.md)

This guide explains how to use WebSockets with Falcon.

#### [Interim Responses](.context/falcon/interim-responses.md)

This guide explains how to use interim responses in Falcon to send early hints to the client.

#### [How It Works](.context/falcon/how-it-works.md)

This guide gives an overview of how Falcon handles an incoming web request.

### io-endpoint

Provides a separation of concerns interface for IO endpoints.

#### [Getting Started](.context/io-endpoint/getting-started.md)

This guide explains how to get started with `io-endpoint`, a library that provides a separation of concerns interface for network I/O endpoints.

#### [Named Endpoints](.context/io-endpoint/named-endpoints.md)

This guide explains how to use `IO::Endpoint::NamedEndpoints` to manage multiple endpoints by name, enabling scenarios like running the same application on different protocols or ports.

### io-event

An event loop.

#### [Getting Started](.context/io-event/getting-started.md)

This guide explains how to use `io-event` for non-blocking IO.

### markly

CommonMark parser and renderer. Written in C, wrapped in Ruby.

#### [Getting Started](.context/markly/getting-started.md)

This guide explains now to install and use Markly.

#### [Abstract Syntax Tree](.context/markly/abstract-syntax-tree.md)

This guide explains how to use Markly's abstract syntax tree (AST) to parse and manipulate Markdown documents.

#### [Headings](.context/markly/headings.md)

This guide explains how to work with headings in Markly, including extracting them for navigation and handling duplicate heading text.

### memory

Memory profiling routines for Ruby 2.3+

#### [Getting Started](.context/memory/getting-started.md)

This guide explains how to get started with `memory`, a Ruby gem for profiling memory allocations in your applications.

### metrics

Application metrics and instrumentation.

#### [Getting Started](.context/metrics/getting-started.md)

This guide explains how to use `metrics` for capturing run-time metrics.

#### [Capture](.context/metrics/capture.md)

This guide explains how to use `metrics` for exporting metric definitions from your application.

#### [Testing](.context/metrics/testing.md)

This guide explains how to write assertions in your test suite to validate `metrics` are being emitted correctly.

### process-metrics

Provide detailed OS-specific process metrics.

#### [Getting Started](.context/process-metrics/getting-started.md)

This guide explains how to use the `process-metrics` gem to collect and analyze process metrics including processor and memory utilization.

### protocol-http

Provides abstractions to handle HTTP protocols.

#### [Getting Started](.context/protocol-http/getting-started.md)

This guide explains how to use `protocol-http` for building abstract HTTP interfaces.

#### [Message Body](.context/protocol-http/message-body.md)

This guide explains how to work with HTTP request and response message bodies using `Protocol::HTTP::Body` classes.

#### [Headers](.context/protocol-http/headers.md)

This guide explains how to work with HTTP headers using `protocol-http`.

#### [Middleware](.context/protocol-http/middleware.md)

This guide explains how to build and use HTTP middleware with `Protocol::HTTP::Middleware`.

#### [Streaming](.context/protocol-http/streaming.md)

This guide gives an overview of how to implement streaming requests and responses.

#### [Design Overview](.context/protocol-http/design-overview.md)

This guide explains the high level design of `protocol-http` in the context of wider design patterns that can be used to implement HTTP clients and servers.

### protocol-http1

A low level implementation of the HTTP/1 protocol.

#### [Getting Started](.context/protocol-http1/getting-started.md)

This guide explains how to get started with `protocol-http1`, a low-level implementation of the HTTP/1 protocol for building HTTP clients and servers.

### protocol-http2

A low level implementation of the HTTP/2 protocol.

#### [Getting Started](.context/protocol-http2/getting-started.md)

This guide explains how to use the `protocol-http2` gem to implement a basic HTTP/2 client.

### protocol-rack

An implementation of the Rack protocol/specification.

#### [Getting Started](.context/protocol-rack/getting-started.md)

This guide explains how to get started with `protocol-rack` and integrate Rack applications with `Protocol::HTTP` servers.

#### [Request and Response Handling](.context/protocol-rack/request-response.md)

This guide explains how to work with requests and responses when bridging between Rack and `Protocol::HTTP`, covering advanced use cases and edge cases.

### samovar

Samovar is a flexible option parser excellent support for sub-commands and help documentation.

#### [Getting Started](.context/samovar/getting-started.md)

This guide explains how to use `samovar` to build command-line tools and applications.

### sus

A fast and scalable test runner.

#### [Getting Started](.context/sus/getting-started.md)

This guide explains how to use the `sus` gem to write tests for your Ruby projects.

#### [Mocking](.context/sus/mocking.md)

This guide explains how to use mocking in sus to isolate dependencies and verify interactions in your tests.

#### [Shared Test Behaviors and Fixtures](.context/sus/shared-contexts.md)

This guide explains how to use shared test contexts and fixtures in sus to reduce duplication and ensure consistent test behavior across your test suite.

### traces

Application instrumentation and tracing.

#### [Getting Started](.context/traces/getting-started.md)

This guide explains how to use `traces` for tracing code execution.

#### [Context Propagation](.context/traces/context-propagation.md)

This guide explains how to propagate trace context between different execution contexts within your application using `Traces.current_context` and `Traces.with_context`.

#### [Testing](.context/traces/testing.md)

This guide explains how to test traces in your code.

#### [Capture](.context/traces/capture.md)

This guide explains how to use `traces` for exporting traces from your application. This can be used to document all possible traces.

### utopia

Utopia is a framework for building dynamic content-driven websites.

#### [Getting Started](.context/utopia/getting-started.md)

This guide explains how to set up a `utopia` website for local development and deployment.

#### [Middleware](.context/utopia/middleware.md)

This guide gives an overview of the different Rack middleware used by Utopia.

#### [Server Setup](.context/utopia/server-setup.md)

This guide explains how to deploy a `utopia` web application.

#### [Integrating with JavaScript](.context/utopia/integrating-with-javascript.md)

This guide explains how to integrate JavaScript into your Utopia application.

#### [What is XNode?](.context/utopia/what-is-xnode.md)

This guide explains the `xnode` view layer and how it can be used to build efficient websites.

#### [Updating Utopia](.context/utopia/updating-utopia.md)

This guide explains how to update existing `utopia` websites.

### utopia-project

A project documentation tool based on Utopia.

#### [Getting Started](.context/utopia-project/getting-started.md)

This guide explains how to use `utopia-project` to add documentation to your project.

#### [Documentation Guides](.context/utopia-project/documentation-guidelines.md)

This guide explains how to create and maintain documentation for your project using `utopia-project`.

#### [Mermaid Diagrams](.context/utopia-project/mermaid-diagrams.md)

This guide explains how to use Mermaid diagrams in your documentation to visualize complex relationships, flows, and architectures.

#### [GitHub Pages Integration](.context/utopia-project/github-pages-integration.md)

This guide shows you how to use `utopia-project` with GitHub Pages to deploy documentation.
