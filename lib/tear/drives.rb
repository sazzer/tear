module Tear
    class Drive
        attr_accessor :name, :drive

        def initialize(name, drive)
            @name = name
            @drive = drive
        end
    end

    module Drives
        def self.drives
            [Drive.new("HL-DT-ST DVD+-RW GT10N : A104", "/dev/sr0")]
        end
    end
end
