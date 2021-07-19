#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <time.h>
#include <string>
#include<fstream>

typedef struct {
	std::string copyfolder;
	std::string backupfolder;
} BackupConfig_t;
std::ofstream outputfile("log.txt");

bool CreateBackup(BackupConfig_t* config)
{
	time_t now = time(NULL);
	struct tm* pnow = localtime(&now);
	std::string backup = config->backupfolder;
	backup += "\\";
	backup += std::to_string(pnow->tm_year + 1900);
	backup += "年";
	backup += std::to_string(pnow->tm_mon + 1);
	backup += "月";
	backup += std::to_string(pnow->tm_mday);
	backup += "日";
	backup += std::to_string(pnow->tm_hour);
	backup += "時";
	backup += std::to_string(pnow->tm_min);
	backup += "分";
	backup += std::to_string(pnow->tm_sec);
	backup += "秒";
	try
	{
		std::filesystem::copy(config->copyfolder, backup, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		outputfile << "error: ";
		outputfile << e.what() << std::endl;
		return false;
	}

	outputfile << "バックアップを作成しました: ";
	outputfile << backup << std::endl;
	return true;
}

int main()
{
	BackupConfig_t BackupConfig;
	std::cout << "バックアップするフォルダーの絶対パスを入力してください" << std::endl;
	std::cin >> BackupConfig.copyfolder;
	std::cout << "バックアップを入れるフォルダーの絶対パスを入力してください" << std::endl;
	std::cin >> BackupConfig.backupfolder;
	std::cout << "バックアップを開始します" << std::endl;
	outputfile << "バックアップするフォルダ: ";
	outputfile << BackupConfig.copyfolder << std::endl;
	outputfile << "バックアップを入れるフォルダ";
	outputfile << BackupConfig.backupfolder << std::endl;

	while (true)
	{
		if (!CreateBackup(&BackupConfig)) break;
		std::this_thread::sleep_for(std::chrono::hours(24));
	}

	outputfile.close();
	return 0;
}
