#include "../../include/Audio-player/FileManager.hpp"

#include <gtest/gtest.h>

class FileManagerTest : public ::testing::Test {
  protected:
    FileManager file_manager;
};

TEST_F(FileManagerTest, TestScanDirectory) {
    file_manager.ScanDirectory();
    EXPECT_FALSE(file_manager.get_ogg_file_paths().empty());
}

TEST_F(FileManagerTest, TestChangeScanningDirectory) {
    fs::path new_directory = "/new/music/directory";
    file_manager.ChangeScanningDirectory(new_directory);
    EXPECT_EQ(file_manager.get_directory(), new_directory);
}

TEST_F(FileManagerTest, TestSaveAndLoadFilePaths) {
    file_manager.ScanDirectory();
    file_manager.SaveFilePaths();
    file_manager.LoadFilePaths();
    EXPECT_FALSE(file_manager.get_ogg_file_paths().empty());
}
