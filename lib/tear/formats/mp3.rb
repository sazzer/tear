require "tear/logger"
require "open3"
require "ruby_events"

module Tear
    module Formats
        class MP3
            attr_accessor :name, :ext

            def initialize
                @name = "MP3"
                @ext = "mp3"
            end

            def encode(source, target, title, author, disc)
                $log.info "Encoding source #{source} to #{target}"
                FileUtils.mkdir_p File.dirname(target)

                Open3.popen3("lame --ta \"#{author}\" --tt \"#{title} Disc #{disc}\" --tl \"#{title}\" --tn \"#{disc}\" --add-id3v2 \"#{source}\" \"#{target}\"") do
                    |stdin, stdout, stderr|

                    $log.info "Here we go"
                    stdin.close_write
                    begin
                        while (line = stderr.readline(""))
                            line.scan(/^\s*(\d+)\/(\d+)\s*\(/).collect { |current, total|
                                percentage = Float(current) / Float(total)
                                events.fire(:progress, {:percentage => percentage})
                            }
                        end
                    rescue EOFError
                        events.fire(:finished)
                    rescue => e
                        $log.error "Oops #{e}"
                    end
                end
            end
        end
    end
end

