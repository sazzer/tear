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
            @configWindow.show
            Gtk.main
        end
    end
end
