module Tear
    module Formats
        class MP3
            attr_accessor :name, :ext

            def initialize
                @name = "MP3"
                @ext = "mp3"
            end

            def encode(source, target, title, author, disc)
            end
        end
    end
end

