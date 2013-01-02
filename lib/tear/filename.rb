module Tear
    class Filename
        def initialize(config, title, author, disc, format)
            @config = config
            @title = title
            @author = author
            @disc = disc
            @format = format
        end

        def build_filename
            template = File.join(@config.baseDir, @config.filename)
            template.sub! "%a", escape(@author)
            template.sub! "%t", escape(@title)
            template.sub! "%d", escape(@disc)
            template.sub! "%e", escape(@format.ext)
            template
        end

        private
        def escape(part)
            part.to_s.tr('^a-zA-Z0-9_', '_')
        end
    end
end
