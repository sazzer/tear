require "open3"
require "tear/logger"

module Tear
    module Cdrdao
        class BusEntry
            attr_accessor :name, :drive
        end

        class ScanBus
            attr_accessor :entries

            def initialize
                @entries = []

                stdin, stdout, stderr = Open3.popen3("cdrdao scanbus -v 0")
                lines = stderr.readlines
                lines.each { |line|
                    entry = BusEntry.new
                    line.scan(/(.*) : (.*)/).collect { |drive, name|
                        $log.info "Read drive #{drive} with name #{name}"
                        entry.name = name
                        entry.drive = drive
                    }
                    @entries.push entry
                }
            end
        end
    end
end
