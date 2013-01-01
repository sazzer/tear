require File.dirname(__FILE__) + "/lib/tear/version"

require "rubygems"
require "rubygems/package_task"
require "rdoc/task"
require "./tasks/rspec.rb"

GEM_NAME = "tear"

spec = eval(File.read("tear.gemspec"))

Gem::PackageTask.new(spec) do |pkg|
    pkg.gem_spec = spec
end

begin
    require 'sdoc'

    Rake::RDocTask.new do |rdoc|
        rdoc.title = "Tear Audiobook Ripper"
        rdoc.main = "README.rdoc"
        rdoc.options << '--fmt' << 'shtml' # explictly set shtml generator
        rdoc.template = 'direct' # lighter template
        rdoc.rdoc_files.include("README.rdoc", "LICENSE", "lib/**/*.rb")
        rdoc.rdoc_dir = "rdoc"
      end
rescue LoadError
  puts "sdoc is not available. (sudo) gem install sdoc to generate rdoc documentation."
end

task :install => :package do
    sh %{gem install pkg/#{GEM_NAME}-#{Tear::VERSION} --no-rdoc --no-ri}
end

task :uninstall do
    sh %{gem uninstall #{GEM_NAME} -x -v #{Tear::VERSION} }
end
