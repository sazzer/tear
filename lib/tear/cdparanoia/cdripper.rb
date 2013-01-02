require "open3"
require "tear/logger"
require "tear/cdparanoia/cdinfo"
require "ruby_events"

module Tear
    module Cdparanoia
        CD_FRAMEWORDS = 1176
        FUNCTION_READ = "0"
        FUNCTION_WRITE = "-2"

        class Cdripper
            attr_accessor :cdinfo, :outfile

            def initialize(drive, outfile)
                @cdinfo = Cdinfo.new drive
                @drive = drive
                @outfile = outfile
            end

            def start
                err_r, err_w = IO.pipe
                Open3.popen3("cdparanoia -ew -d #{@drive} 1- #{@outfile}") do
                    |stdin, stdout, stderr|
                    stdin.close_write
                    begin
                        while (line = stderr.readline)
                            line.scan(/^##: ([0-9-]+).*@ (\d+)/).collect { |func, offset|
                                sector = Integer(offset) / CD_FRAMEWORDS
                                track = @cdinfo.track_from_sector sector
                                percentage = (Float(sector) / @cdinfo.total_sectors);
                                if (func == FUNCTION_READ)
                                    events.fire(:read_progress, {:sector => sector, :track => track, :percentage => percentage})
                                elsif (func == FUNCTION_WRITE)
                                    events.fire(:write_progress, {:sector => sector, :track => track, :percentage => percentage})
                                end
                            }
                        end
                    rescue EOFError
                        $log.info "Finished ripping from drive #{@drive}"
                        events.fire(:finished)
                    rescue => e
                        $log.error "Oops #{e}"
                    end
                end
            end
        end
    end
end
