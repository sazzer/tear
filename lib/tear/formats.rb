require "tear/formats/mp3"
require "tear/formats/wav"

module Tear
    module Formats
        def self.formats
            [WAV.new]
        end
    end
end
