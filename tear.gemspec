$:.unshift(File.dirname(__FILE__) + "/lib")
require "tear/version"

Gem::Specification.new do |s|
    s.name = "Tear"
    s.version = Tear::VERSION
    s.platform = Gem::Platform::RUBY
    s.extra_rdoc_files = ["README.md"]
    s.summary = "Simplistic ripping of Audiobook CDs"
    s.description = s.summary
    s.author = "Graham Cox"
    s.email = "graham@grahamcox.co.uk"
    s.homepage = "http://grahamcox.co.uk/tear"

    s.add_dependency "gtk2"

    s.add_development_dependency "rdoc"
    s.add_development_dependency "sdoc"
    s.add_development_dependency "rake"

    s.add_development_dependency "rspec_junit_formatter"
    s.add_development_dependency "rspec-core", "~> 2.8.0"
    s.add_development_dependency "rspec-expectations", "~> 2.8.0"
    s.add_development_dependency "rspec-mocks", "~> 2.8.0"

    s.bindir = "bin"
    s.executables = "tear"
    s.require_path = "lib"
    s.files = %w(Rakefile README.md) + Dir.glob("{distro,lib,tasks,spec}/**/*")
end
