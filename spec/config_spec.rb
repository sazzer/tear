require "spec_helper"
require "tear/config"

describe Tear::Config do
    describe "A non-existant config file" do
        before do
            @file = File.expand_path("../resources/badfile", __FILE__)
            @config = Tear::Config.new(@file)
        end

        it "should not be loaded" do
            @config.loaded.should eq(false)
        end

        it "should be from the expected file" do
            @config.configFile.should eq(@file)
        end

        it "should have the default filename" do
            @config.filename.should eq("%a/%t/%d.%e")
        end
    end

    describe "A valid config file" do
        before do
            @file = File.expand_path("../resources/config", __FILE__)
            @config = Tear::Config.new(@file)
        end

        it "should be loaded" do
            @config.loaded.should eq(true)
        end
        
        it "should be from the expected file" do
            @config.configFile.should eq(@file)
        end

        it "should have the expected filename" do
            @config.filename.should eq("filename goes here")
        end

        it "should have the expected base dir" do
            @config.baseDir.should eq("basedir goes here")
        end
    end
end
