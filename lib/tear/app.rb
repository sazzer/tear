require "tear/version"
require "tear/logger"
require "tear/ui/config"
require "tear/ui/mainwindow"
require "tear/ui/progress"
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
            @configWindow = Tear::UI::Config.new config
            @progressWindow = Tear::UI::Progress.new config

            @mainWindow.set_formats @formats
            @mainWindow.set_drives @drives

            @mainWindow.events.listen(:closed) do
                Gtk.main_quit
            end
            @mainWindow.events.listen(:config) do
                @mainWindow.hide
                @configWindow.show
            end
            @mainWindow.events.listen(:go) do
                |e|
                $log.info "About to rip: #{e}"
                @progressWindow.author=e[:author]
                @progressWindow.title=e[:title]
                @progressWindow.disc=e[:disc]
                @progressWindow.drive=e[:drive]
                @progressWindow.format=e[:format]
                @mainWindow.hide
                @progressWindow.start
            end
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
            @progressWindow.events.listen(:finished) do
                @mainWindow.show
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
