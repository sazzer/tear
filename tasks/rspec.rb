require 'rubygems'
require 'rake'

TEAR_ROOT = File.join(File.dirname(__FILE__), "..")

begin
  require 'rspec/core/rake_task'

  task :default => :spec

  desc "Run all specs in spec directory"
  RSpec::Core::RakeTask.new(:spec) do |t|
    t.rspec_opts = ['--options', "\"#{TEAR_ROOT}/.rspec\""]
    t.pattern = FileList['spec/**/*_spec.rb']
  end

  namespace :spec do
    desc "Run all specs in spec directory with RCov"
    RSpec::Core::RakeTask.new(:rcov) do |t|
      t.rspec_opts = ['--options', "\"#{TEAR_ROOT}/spec/spec.opts\""]
      t.pattern = FileList['spec/**/*_spec.rb']
      t.rcov = true
      t.rcov_opts = lambda do
        IO.readlines("#{TEAR_ROOT}/spec/rcov.opts").map {|l| l.chomp.split " "}.flatten
      end
    end

    desc "Print Specdoc for all specs"
    RSpec::Core::RakeTask.new(:doc) do |t|
      t.rspec_opts = ["--format", "specdoc", "--dry-run"]
      t.pattern = FileList['spec/**/*_spec.rb']
    end
  end
rescue LoadError
  STDERR.puts "\n*** RSpec not available. (sudo) gem install rspec to run unit tests. ***\n\n"
end
