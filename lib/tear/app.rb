require "tear/version"
require "tear/logger"
require "tear/ui/config"

class Tear::Application
    def run
        $log.info("Starting Tear #{Tear::VERSION}")
        Gtk.init
        @configWindow = UI::Config.new
        @configWindow.show
        Gtk.main
    end
end
