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

    // �E�B���h�E�̕`��
    ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f,0));
    ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));
    ImGui::GetIO().FontGlobalScale = 1.2f; // �f�t�H���g��1.0����1.5�{�傫�ȃT�C�Y
    ImGui::Begin("World Outliner", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    {
        // �ǉ��{�^����\��
        if (ImGui::Button("Add"))AddStageObject();

        // �\��
        if (ImGui::TreeNode("Object list")) {

            // ���X�g��`��
            for (int i = 0; i < objects.size(); ++i) {
                if (ImGui::Selectable(objects[i]->GetObjectName().c_str(), selectedIndex_ == i)) {
                    selectedIndex_ = i;
                }
            }

            ImGui::TreePop();
        } 
    }
    ImGui::End();

    // �E�B���h�E�̕`��
    ImGui::SetNextWindowPos(ImVec2(Direct3D::screenWidth_ * 0.7f, Direct3D::screenHeight_ * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(Direct3D::screenWidth_ * 0.3f, Direct3D::screenHeight_ * 0.5f));
    ImGui::Begin("Datails", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    {
        // �ڍׂ�`��
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
        // "Assets\" �ȍ~�̕����̈ʒu������
        size_t assetsPos = absolutePath.find("Assets\\");
        if (assetsPos != std::string::npos) {
            // "Assets\" �ȍ~�̕������擾
            std::string relativePath = absolutePath.substr(assetsPos);
            return relativePath;
        }
        else {
            // "Assets\" ��������Ȃ��ꍇ�́A���̃t�@�C���p�X��Ԃ�
            return absolutePath;
        }
    }
}

bool StageEditor::GetModelFileName(std::string& _dst)
{
    
    // �t�@�C�����J���_�C�A���O�̐ݒ�p�\����
    OPENFILENAME ofn; {
        TCHAR szFile[MAX_PATH] = {}; // �t�@�C�������i�[����o�b�t�@
        ZeroMemory(&ofn, sizeof(ofn)); // �\���̂̏�����
        ofn.lStructSize = sizeof(ofn); // �\���̂̃T�C�Y
        ofn.lpstrFile = szFile; // �t�@�C�������i�[����o�b�t�@
        ofn.lpstrFile[0] = '\0'; // ������
        ofn.nMaxFile = sizeof(szFile); // �t�@�C�����o�b�t�@�̃T�C�Y
        ofn.lpstrFilter = TEXT("FBX�t�@�C��(*.fbx)\0*.fbx\0���ׂẴt�@�C��(*.*)\0*.*\0"); // �t�B���^�[�iFBX�t�@�C���̂ݕ\���j
        ofn.nFilterIndex = 1; // �����I������t�B���^�[
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // �t���O�i�t�@�C�������݂��邱�ƁA�p�X�����݂��邱�Ƃ��m�F�j
        ofn.lpstrInitialDir = TEXT("."); // �J�����g�f�B���N�g���������I���ʒu�Ƃ��Đݒ�
    }

    // �t�@�C����I������_�C�A���O�̕\��
    if (GetOpenFileName(&ofn) == TRUE) {
        // �I�����ꂽ�t�@�C���̑��΃p�X���擾
        std::string selectedFile = TCHARToString(ofn.lpstrFile);
        // �J�����g�f�B���N�g������̑��΃p�X���v�Z
        _dst = GetAssetsRelativePath(selectedFile);
        return true;
    }
    else {
        // �_�C�A���O���L�����Z�����ꂽ�ꍇ�̏���
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
