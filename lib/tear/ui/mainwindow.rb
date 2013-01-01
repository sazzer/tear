require "gtk2"
require "ruby_events"
require "tear/logger"

module Tear 
    module UI
        # Wrapper around the configuration dialog
        class MainWindow
            def initialize
                @window = Gtk::Window.new
                @window.set_title "Tear"
                @window.set_window_position Gtk::Window::POS_CENTER

                @grid = Gtk::Table.new(6, 2)
                @window.add @grid

                @drivesModel = Gtk::ListStore.new(Integer, String)
                @driveEntry = Gtk::ComboBox.new @drivesModel
                cellRenderer = Gtk::CellRendererCombo.new
                @driveEntry.pack_start cellRenderer, true
                @driveEntry.add_attribute cellRenderer, "text", 1
                addLabelledWidget("Drive", @driveEntry, 0)

                @authorEntry = Gtk::Entry.new
                addLabelledWidget("Author", @authorEntry, 1)

                @titleEntry = Gtk::Entry.new
                addLabelledWidget("Title", @titleEntry, 2)

                @discEntry = Gtk::SpinButton.new 0, 100, 1
                @discEntry.value = 1
                addLabelledWidget("Disc", @discEntry, 3)

                @formatsModel = Gtk::ListStore.new(Integer, String)
                @formatEntry = Gtk::ComboBox.new @formatsModel
                cellRenderer = Gtk::CellRendererCombo.new
                @formatEntry.pack_start cellRenderer, true
                @formatEntry.add_attribute cellRenderer, "text", 1
                addLabelledWidget("Format", @formatEntry, 4)

                @window.signal_connect("destroy") { |dialog, response|
                    events.fire(:closed)
                }
            end

            def set_drives(drives)
                @drives = drives
                @drivesModel.clear
                drives.each_with_index do |value, index|
                    iter = @drivesModel.append
                    iter.set_value 0, index
                    iter.set_value 1, "#{value.name} (#{value.drive})"
                end
                @driveEntry.set_active 0
            end

            def set_formats(formats)
                @formats = formats
                @formatsModel.clear
                formats.each_with_index do |value, index|
                    iter = @formatsModel.append
                    iter.set_value 0, index
                    iter.set_value 1, value.name
                end
                @formatEntry.set_active 0
            end

            def show
                @window.show_all
            end

            private
            # Helper to add a labelled widget to the dialog
            def addLabelledWidget(labelText, field, row)
                label = Gtk::Label.new(labelText)
                @grid.attach(label, 0, 1, row, row + 1)
                @grid.attach(field, 1, 2, row, row + 1)
            end
        end
    end
end
    
