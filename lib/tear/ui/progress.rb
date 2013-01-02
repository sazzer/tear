require "gtk2"
require "ruby_events"
require "tempfile"
require "tear/logger"
require "tear/cdparanoia/cdripper"
require "tear/filename"

module Tear 
    module UI
        # Wrapper around the configuration dialog
        class Progress
            attr_accessor :title, :author, :disc, :drive, :format

            def initialize(config)
                @config = config

                @window = Gtk::Window.new
                @window.set_title "Tear - Progress"
                @window.set_window_position Gtk::Window::POS_CENTER
                @window.set_deletable false

                @grid = Gtk::Table.new(5, 2)
                @window.add @grid

                @readProgress = Gtk::ProgressBar.new
                addLabelledWidget("Reading", @readProgress, 0)

                @writeProgress = Gtk::ProgressBar.new
                addLabelledWidget("Writing", @writeProgress, 1)

                @encodeProgress = Gtk::ProgressBar.new
                addLabelledWidget("Encoding", @encodeProgress, 2)

                @progressLabel = Gtk::Label.new("Starting...")
                @grid.attach(@progressLabel, 0, 2, 3, 4)

                @timeLabel = Gtk::Label.new("Starting...")
                @grid.attach(@timeLabel, 0, 2, 4, 5)
            end

            def start
                @window.show_all
                filename = Filename.new(@config, @title, @author, @disc, @format).build_filename

                startTime = Time.now

                tempfile = Tempfile.new(["tear", ".wav"])
                tempfile.close
                $log.info "Ripping CD to temporary file #{tempfile.path}"
                cdripper = Tear::Cdparanoia::Cdripper.new @drive.drive, tempfile.path
                cdripper.events.listen(:read_progress) do |e|
                    @readProgress.fraction = e[:percentage]
                    @progressLabel.text = "Reading track #{e[:track].track}"
                    updateTimer startTime
                end
                cdripper.events.listen(:write_progress) do |e|
                    @writeProgress.fraction = e[:percentage]
                    @progressLabel.text = "Writing track #{e[:track].track}"
                    updateTimer startTime
                end
                cdripper.events.listen(:finished) do
                    @format.events.listen(:progress) do |e|
                        @encodeProgress.fraction = e[:percentage]
                        updateTimer startTime
                    end

                    @format.events.listen(:finished) do
                        $log.info "Finished encoding"
                        tempfile.unlink
                        @window.hide
                        events.fire(:finished)
                    end

                    $log.info "Encoding to #{filename} with #{@format}"
                    @progressLabel.text = "Encoding file"
                    @format.encode tempfile.path, filename, @title, @author, @disc
                end
                @progressLabel.text = "About to rip #{cdripper.cdinfo.tracks.size} tracks"
                thread = Thread.new {
                    cdripper.start
                }
            end

            private
            # Helper to add a labelled widget to the dialog
            def addLabelledWidget(labelText, field, row)
                label = Gtk::Label.new(labelText)
                @grid.attach(label, 0, 1, row, row + 1)
                @grid.attach(field, 1, 2, row, row + 1)
            end

            def updateTimer(startTime)
                endTime = Time.now
                elapsed = (endTime - startTime).to_i
                
                elapsedMinutes = elapsed / 60
                elapsedSeconds = elapsed % 60
                elapsedTime = "#{elapsedMinutes}:#{elapsedSeconds.to_s.rjust(2, '0')}"

                @timeLabel.text = "#{elapsedTime}"
            end
        end
    end
end
    

