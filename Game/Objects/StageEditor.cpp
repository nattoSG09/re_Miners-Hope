#include "StageEditor.h"

#include "Stage.h"
#include "StageObject.h"

#include "../../Engine/DirectX/Direct3D.h"
#include "../../Engine/ImGui/imgui.h"
#include <vector>

#include <windows.h>
#include <commdlg.h> // Common dialogs

StageEditor::StageEditor(GameObject* _parent)
	:GameObject(_parent,"StageEditor"),editTarget_(nullptr),selectedIndex_(-1)
{
}

void StageEditor::Initialize()
{
}

void StageEditor::Update()
{
    if (editTarget_ == nullptr)return;

    std::vector<StageObject*> objects = editTarget_->GetStageObjects();

    // ウィンドウの描画
    ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f,0));
    ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));
    ImGui::GetIO().FontGlobalScale = 1.2f; // デフォルトの1.0よりも1.5倍大きなサイズ
    ImGui::Begin("World Outliner", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    {
        // 追加ボタンを表示
        if (ImGui::Button("Add"))AddStageObject();

        // 表示
        if (ImGui::TreeNode("Object list")) {

            // リストを描画
            for (int i = 0; i < objects.size(); ++i) {
                if (ImGui::Selectable(objects[i]->GetObjectName().c_str(), selectedIndex_ == i)) {
                    selectedIndex_ = i;
                }
            }

            ImGui::TreePop();
        } 
    }
    ImGui::End();

    // ウィンドウの描画
    ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f, Direct3D::screenHeight_ * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));
    ImGui::Begin("Datails", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    {
        // 詳細を描画
        if (selectedIndex_ >= 0 && selectedIndex_ < objects.size()) {
            if (ImGui::TreeNode("Transform")) {
                if (ImGui::TreeNode("position_")) {
                    ImGui::InputFloat("x", &objects[selectedIndex_]->transform_.position_.x);
                    ImGui::InputFloat("y", &objects[selectedIndex_]->transform_.position_.y);
                    ImGui::InputFloat("z", &objects[selectedIndex_]->transform_.position_.z);
                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("rotate_")) {
                    ImGui::InputFloat("x", &objects[selectedIndex_]->transform_.rotate_.x);
                    ImGui::InputFloat("y", &objects[selectedIndex_]->transform_.rotate_.y);
                    ImGui::InputFloat("z", &objects[selectedIndex_]->transform_.rotate_.z);
                    ImGui::TreePop();
                }

                if (ImGui::TreeNode("scale_")) {
                    ImGui::InputFloat("x", &objects[selectedIndex_]->transform_.scale_.x);
                    ImGui::InputFloat("y", &objects[selectedIndex_]->transform_.scale_.y);
                    ImGui::InputFloat("z", &objects[selectedIndex_]->transform_.scale_.z);
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
}

void StageEditor::Draw()
{
}

void StageEditor::Release()
{
}

namespace {
    std::string TCHARToString(const TCHAR* tchar) {
#ifdef UNICODE
        int len = WideCharToMultiByte(CP_UTF8, 0, tchar, -1, nullptr, 0, nullptr, nullptr);
        std::string str(len - 1, 0);
        WideCharToMultiByte(CP_UTF8, 0, tchar, -1, &str[0], len, nullptr, nullptr);
        return str;
#else
        return std::string(tchar);
#endif
    };

    std::string GetAssetsRelativePath(const std::string& absolutePath) {
        // "Assets\" 以降の部分の位置を検索
        size_t assetsPos = absolutePath.find("Assets\\");
        if (assetsPos != std::string::npos) {
            // "Assets\" 以降の部分を取得
            std::string relativePath = absolutePath.substr(assetsPos);
            return relativePath;
        }
        else {
            // "Assets\" が見つからない場合は、元のファイルパスを返す
            return absolutePath;
        }
    }
}

bool StageEditor::GetModelFileName(std::string& _dst)
{
    
    // ファイルを開くダイアログの設定用構造体
    OPENFILENAME ofn; {
        TCHAR szFile[MAX_PATH] = {}; // ファイル名を格納するバッファ
        ZeroMemory(&ofn, sizeof(ofn)); // 構造体の初期化
        ofn.lStructSize = sizeof(ofn); // 構造体のサイズ
        ofn.lpstrFile = szFile; // ファイル名を格納するバッファ
        ofn.lpstrFile[0] = '\0'; // 初期化
        ofn.nMaxFile = sizeof(szFile); // ファイル名バッファのサイズ
        ofn.lpstrFilter = TEXT("FBXファイル(*.fbx)\0*.fbx\0すべてのファイル(*.*)\0*.*\0"); // フィルター（FBXファイルのみ表示）
        ofn.nFilterIndex = 1; // 初期選択するフィルター
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // フラグ（ファイルが存在すること、パスが存在することを確認）
        ofn.lpstrInitialDir = TEXT("."); // カレントディレクトリを初期選択位置として設定
    }

    // ファイルを選択するダイアログの表示
    if (GetOpenFileName(&ofn) == TRUE) {
        // 選択されたファイルの相対パスを取得
        std::string selectedFile = TCHARToString(ofn.lpstrFile);
        // カレントディレクトリからの相対パスを計算
        _dst = GetAssetsRelativePath(selectedFile);
        return true;
    }
    else {
        // ダイアログがキャンセルされた場合の処理
        return false;
    }
}

void StageEditor::AddStageObject()
{
    std::string modelFilePath{};
    if (GetModelFileName(modelFilePath)) {
        StageObject* obj = CreateStageObject("Object" + std::to_string(editTarget_->GetStageObjects().size() + 1), modelFilePath, this);
        editTarget_->AddObject(obj);
    }
}
