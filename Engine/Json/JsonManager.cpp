#include "JsonManager.h"
#include <fstream>
using namespace std;

bool JsonManager::Load(string fileName,json& _data)
{
    // ファイルを開く
    ifstream readingFile;
    readingFile.open(fileName, ios::in);

    // ファイルが開けなかったら
    if (readingFile.is_open() == false)return false;

    // データをjsonオブジェクトに格納
    readingFile >> _data;

    // ファイルを閉じる
    readingFile.close();

    return true;
}

bool JsonManager::Save(string fileName, json& _data)
{
    // ファイルを開く
    ofstream writingFile;
    writingFile.open(fileName, ios::out);

    // ファイルが開けなかったら
    if (writingFile.is_open() == false)return false;

    // データをファイルに流す
    writingFile << _data.dump() << endl;

    // ファイルを閉じる
    writingFile.close();

    return true;
}
