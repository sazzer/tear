module Tear
    class Format
        attr_accessor :name
    end

    module Formats
        class MP3 < Tear::Format
            def initialize
                @name = "MP3"
            end
        end

        class Ogg < Tear::Format
            def initialize
                @name = "Ogg Vorbis"
            end
        end

        class FLAC < Tear::Format
            def initialize
                @name = "FLAC"
            end
        end

        class WAV < Tear::Format
            def initialize
                @name = "Wave"
            end
        end

        def self.formats
            [MP3.new, Ogg.new, FLAC.new, WAV.new]
        end
    end
end
