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
            end

            if @filename.nil?
                @filename = "%a/%t/%d.%e"
            end

            if @baseDir.nil?
                @baseDir = File.expand_path("~/Audiobooks")
            end
        end
    end
end
