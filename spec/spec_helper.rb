$:.unshift File.expand_path("../..", __FILE__)

require "rubygems"
require "rspec/mocks"

$:.unshift(File.join(File.dirname(__FILE__), "..", "lib"))
$:.unshift(File.expand_path("../lib", __FILE__))
$:.unshift(File.dirname(__FILE__))

RSpec.configure do |config|
end
