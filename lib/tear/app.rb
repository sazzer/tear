require "tear/version"
require "tear/logger"
require "tear/ui/config"
require "tear/config"

module Tear
    class Application
        def run
            $log.info("Starting Tear #{Tear::VERSION}")
            configFile = File.expand_path("~/.tear")
            config = Config.new configFile

            Gtk.init
            @configWindow = Tear::UI::Config.new config
            @configWindow.events.listen(:save) do 
                config.save
            end
            @configWindow.events.listen(:cancel) do
                if !config.loaded
                    @configWindow.show
                end
            end

            @configWindow.show
            Gtk.main
        end
    end
end
