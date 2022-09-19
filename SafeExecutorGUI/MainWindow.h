#pragma once
#include <Windows.h>
#include <msclr/marshal.h>
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

namespace SafeExecutorGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// MainWindow の概要
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ target_exe_selection_panel;
	protected:
	private: System::Windows::Forms::Panel^ checklist_panel;
	private: System::Windows::Forms::Panel^ output_panel;
	private: System::Windows::Forms::Button^ FileSelectBtn;
	private: System::Windows::Forms::TextBox^ FileSelectTextBox;
	private: System::Windows::Forms::Button^ ExecBtn;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->target_exe_selection_panel = (gcnew System::Windows::Forms::Panel());
			this->ExecBtn = (gcnew System::Windows::Forms::Button());
			this->FileSelectBtn = (gcnew System::Windows::Forms::Button());
			this->FileSelectTextBox = (gcnew System::Windows::Forms::TextBox());
			this->checklist_panel = (gcnew System::Windows::Forms::Panel());
			this->output_panel = (gcnew System::Windows::Forms::Panel());
			this->target_exe_selection_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// target_exe_selection_panel
			// 
			this->target_exe_selection_panel->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->target_exe_selection_panel->Controls->Add(this->ExecBtn);
			this->target_exe_selection_panel->Controls->Add(this->FileSelectBtn);
			this->target_exe_selection_panel->Controls->Add(this->FileSelectTextBox);
			this->target_exe_selection_panel->Dock = System::Windows::Forms::DockStyle::Top;
			this->target_exe_selection_panel->Location = System::Drawing::Point(0, 0);
			this->target_exe_selection_panel->Margin = System::Windows::Forms::Padding(4);
			this->target_exe_selection_panel->Name = L"target_exe_selection_panel";
			this->target_exe_selection_panel->Size = System::Drawing::Size(1148, 208);
			this->target_exe_selection_panel->TabIndex = 0;
			// 
			// ExecBtn
			// 
			this->ExecBtn->Location = System::Drawing::Point(878, 81);
			this->ExecBtn->Name = L"ExecBtn";
			this->ExecBtn->Size = System::Drawing::Size(75, 31);
			this->ExecBtn->TabIndex = 2;
			this->ExecBtn->Text = L"実行";
			this->ExecBtn->UseVisualStyleBackColor = true;
			this->ExecBtn->Click += gcnew System::EventHandler(this, &MainWindow::ExecBtn_Click);
			// 
			// FileSelectBtn
			// 
			this->FileSelectBtn->Location = System::Drawing::Point(780, 81);
			this->FileSelectBtn->Name = L"FileSelectBtn";
			this->FileSelectBtn->Size = System::Drawing::Size(75, 31);
			this->FileSelectBtn->TabIndex = 1;
			this->FileSelectBtn->Text = L"参照";
			this->FileSelectBtn->UseVisualStyleBackColor = true;
			this->FileSelectBtn->Click += gcnew System::EventHandler(this, &MainWindow::FileSelectBtn_Click);
			// 
			// FileSelectTextBox
			// 
			this->FileSelectTextBox->BackColor = System::Drawing::Color::White;
			this->FileSelectTextBox->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 10.2F, System::Drawing::FontStyle::Bold));
			this->FileSelectTextBox->Location = System::Drawing::Point(72, 84);
			this->FileSelectTextBox->Name = L"FileSelectTextBox";
			this->FileSelectTextBox->Size = System::Drawing::Size(688, 24);
			this->FileSelectTextBox->TabIndex = 0;
			// 
			// checklist_panel
			// 
			this->checklist_panel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->checklist_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->checklist_panel->Location = System::Drawing::Point(0, 208);
			this->checklist_panel->Margin = System::Windows::Forms::Padding(4);
			this->checklist_panel->Name = L"checklist_panel";
			this->checklist_panel->Size = System::Drawing::Size(1148, 540);
			this->checklist_panel->TabIndex = 1;
			// 
			// output_panel
			// 
			this->output_panel->BackColor = System::Drawing::SystemColors::Info;
			this->output_panel->Dock = System::Windows::Forms::DockStyle::Right;
			this->output_panel->Location = System::Drawing::Point(643, 208);
			this->output_panel->Margin = System::Windows::Forms::Padding(4);
			this->output_panel->Name = L"output_panel";
			this->output_panel->Size = System::Drawing::Size(505, 540);
			this->output_panel->TabIndex = 2;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1148, 748);
			this->Controls->Add(this->output_panel);
			this->Controls->Add(this->checklist_panel);
			this->Controls->Add(this->target_exe_selection_panel);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			this->target_exe_selection_panel->ResumeLayout(false);
			this->target_exe_selection_panel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FileSelectBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		Stream^ stream;
		OpenFileDialog^ dig = gcnew OpenFileDialog;

		dig->Filter = "Exe Files (*.exe)|*.exe" + "|All Files|*.*";
		dig->FilterIndex = 1;
		dig->RestoreDirectory = true;
		if (dig->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if ((stream = dig->OpenFile()) != nullptr) {
				FileSelectTextBox->Text = dig->FileName;
				stream->Close();
			}
		}
	}
private: System::Void ExecBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	msclr::interop::marshal_context context;
	LPCSTR exePath = context.marshal_as<const char*>(FileSelectTextBox->Text);
	char processPath[MAX_PATH];
	GetModuleFileNameA(NULL, processPath, MAX_PATH);

	if (PathFileExistsA(exePath)) {
		// TODO: このパスの計算をいつか環境変数とかで整理したい
		//   例) [System.Environment]::SetEnvironmentVariable("SafeExecuteInstallDir", $PSScriptRoot, "Machine")
		for(int i=0; i<4; i++) PathRemoveFileSpecA(processPath);
		SetCurrentDirectoryA(processPath);
		char executorPath[MAX_PATH];
		snprintf(executorPath, MAX_PATH, "%s\\%s", processPath, "SafeExecutor\\x64\\Debug\\SafeExecutor.exe");
		char dllPath[MAX_PATH];
		snprintf(dllPath, MAX_PATH, "%s\\%s", processPath, "SafeExecute\\x64\\Debug\\SafeExecute.dll");

		if (PathFileExistsA(executorPath) && PathFileExistsA(dllPath)) {
			STARTUPINFOA si;
			PROCESS_INFORMATION pi;
			memset(&si, 0, sizeof(si));
			memset(&pi, 0, sizeof(pi));
			si.cb = sizeof(si);

			char cmd[MAX_PATH * 4];
			memset(cmd, 0, sizeof(cmd));
			strcat_s(cmd, executorPath);
			strcat_s(cmd, " ");
			strcat_s(cmd, dllPath);
			strcat_s(cmd, " ");
			strcat_s(cmd, exePath);
			
			if (!CreateProcessA(NULL, cmd, NULL, NULL, 0, 0, NULL, NULL, &si, &pi)) {
				MessageBox::Show("Couldn't start executor process", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			
		}
		else MessageBox::Show("Something went wrong in Path Calculation", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
}
};
}
