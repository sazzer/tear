require "yaml"
require "yaml/store"

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

        def save
            store = YAML::Store.new @configFile
            store.transaction do
                store["filename"] = @filename
                store["baseDir"] = @baseDir
            end
            @loaded = true
        end
    end
end
