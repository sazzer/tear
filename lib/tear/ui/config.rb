require "gtk2"

module UI
    class Config < Gtk::Window
        def initialize
            super

            set_title "Tear - Config"
            set_default_size 250, 200
            set_window_position Gtk::Window::POS_CENTER
        end
    end
end
