require "tear/cdrdao/scanbus"

module Tear
    class Drive
        attr_accessor :name, :drive

        def initialize(name, drive)
            @name = name
            @drive = drive
        end
    end

    module Drives
        def self.drives
            scanbus = Tear::Cdrdao::ScanBus.new
            result = []
            scanbus.entries.each { |entry|
                result.push Drive.new(entry.name, entry.drive)
            }
            result
        end
    end
end
