require "tear/formats/mp3"
require "tear/formats/wav"

module Tear
    module Formats
        def self.formats
            [MP3.new, WAV.new]
        end
    end
end
