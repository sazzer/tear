require "yaml"

module Tear
    class Config
        attr_accessor :filename, :baseDir, :loaded, :configFile

        def initialize(file)
            @configFile = file
            if File.exist?(file)
                @loaded = true
                config = YAML::load_file(file)
                @filename = config['filename']
                @baseDir = config['baseDir']
            else
                @loaded = false
                @filename = "%a/%t/%d.%e"
                @baseDir = "/home/graham/Audiobooks"
            end
        end
    end
end
