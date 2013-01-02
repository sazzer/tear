require "open3"
require "tear/logger"

module Tear
    module Cdparanoia
        class Track
            attr_accessor :track, :length, :track_start, :track_end
        end

        class Cdinfo
            attr_accessor :tracks

            def initialize(drive)
                stdin, stdout, stderr = Open3.popen3("cdparanoia -d #{drive} -Q -e")
                lines = stderr.readlines
                total = 0
                @tracks = []

                lines.each { |line|
                    line.scan(/^\s*(\d+)\.\s*(\d+)/).collect { |strack, slength|
                        track = Track.new

                        track.track = Integer(strack)
                        track.length = Integer(slength)

                        track.track_start = total
                        track.track_end = total + track.length
                        total += track.length

                        @tracks.push track
                        $log.info "Found track #{track.track} of length #{track.length}, ranging from #{track.track_start} to #{track.track_end}"
                    }
                }
            end
        end
    end
end
