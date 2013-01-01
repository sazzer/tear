require "tear/version"
require "tear/logger"
require "tear/ui/config"

module Tear
    class Application
        def run
            $log.info("Starting Tear #{Tear::VERSION}")
            Gtk.init
            @configWindow = UI::Config.new
            @configWindow.show
            Gtk.main
        end
    end
end
