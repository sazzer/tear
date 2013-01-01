require "gtk2"
require "tear/logger"

module Tear 
    module UI
        # Wrapper around the configuration dialog
        class Config
            def initialize
                @dialog = Gtk::Dialog.new "Tear - Config", 
                    nil, 
                    nil, 
                    [Gtk::Stock::OK, Gtk::Dialog::RESPONSE_OK], 
                    [Gtk::Stock::CANCEL, Gtk::Dialog::RESPONSE_CANCEL]

                @dialog.set_deletable false
                @grid = Gtk::Table.new(3, 2)
                @dialog.vbox.add @grid

                @baseDirEntry = Gtk::Entry.new
                addLabelledWidget("Base Dir", @baseDirEntry, 0);

                @filenameEntry = Gtk::Entry.new
                addLabelledWidget("Filename", @filenameEntry, 1);

                @dialog.signal_connect("response") { |dialog, response|
                    if response == Gtk::Dialog::RESPONSE_OK
                        onSave
                    else
                        onCancel
                    end
                }
            end

            # Show the dialog
            def show
                @dialog.show_all
            end

            private 
            # Handle when the Save button is pressed
            def onSave
                $log.info "Saving config changes"
            end

            # Handle when the Cancel button is pressed
            def onCancel
                $log.info "Cancelling config changes"
            end

            # Helper to add a labelled widget to the dialog
            def addLabelledWidget(labelText, field, row)
                label = Gtk::Label.new(labelText)
                @grid.attach(label, 0, 1, row, row + 1)
                @grid.attach(field, 1, 2, row, row + 1)
            end
        end
    end
end
