require "fileutils"
require "tear/logger"

module Tear
    module Formats
        class WAV
            attr_accessor :name, :ext
            def initialize
                @name = "Wave"
                @ext = "wav"
            end

            def encode(source, target, title, author, disc)
                $log.info "Copying source #{source} to #{target}"
                FileUtils.mkdir_p File.dirname(target)

                size = File.size(source)
                offset = 0
                readsize = 1024
                File.open(source, "rb") do |r|
                    File.open(target, "wb") do |w|
                        while offset < size do
                            buffer = r.sysread(readsize)
                            w.syswrite(buffer)
                            offset += readsize
                            if (size - offset < readsize)
                                readsize = size - offset
                            end
                            percentage = Float(offset) / size
                            events.fire(:progress, {:percentage => percentage})
                        end
                    end
                end
                events.fire(:finished)
            end
        end
    end
end

