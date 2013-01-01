require "tear/version"
require "tear/logger"
require "tear/ui/config"
require "tear/ui/mainwindow"
require "tear/config"
require "tear/formats"
require "tear/drives"

module Tear
    class Application
        def run
            $log.info("Starting Tear #{Tear::VERSION}")
            configFile = File.expand_path("~/.tear")
            config = Config.new configFile

            @formats = Tear::Formats::formats
            @drives = Tear::Drives::drives

            Gtk.init
            @mainWindow = Tear::UI::MainWindow.new
            @mainWindow.set_formats @formats
            @mainWindow.set_drives @drives
            @mainWindow.events.listen(:closed) do
                Gtk.main_quit
            end

            @configWindow = Tear::UI::Config.new config
            @configWindow.events.listen(:save) do 
                config.save
                @mainWindow.show
            end
            @configWindow.events.listen(:cancel) do
                if !config.loaded
                    @configWindow.show
                else
                    @mainWindow.show
                end
            end

            if !config.loaded
                @configWindow.show
            else
                @mainWindow.show
            end
            Gtk.main
        end
    end
end
