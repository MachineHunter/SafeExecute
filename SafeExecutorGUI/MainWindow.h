#pragma once
#include <Windows.h>
#include <msclr/marshal.h>
#include <vector>
#include <atlstr.h>
#include <string>
#include "ApiDict.h"
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
	using namespace System::Runtime::InteropServices;
	using namespace msclr::interop;
	typedef System::Collections::Generic::Queue<TreeNode^> NodeQueue;
	typedef System::Collections::Generic::List<String^> StrList;

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
			//apiDic

			//ファイル操作
			array<TreeNode^>^ nodChildFiles = {
				gcnew TreeNode("ファイル名変更"),
				gcnew TreeNode("ファイル削除"),
				gcnew TreeNode("ファイル書き込み")
			};

			TreeNode^ nodFile = gcnew TreeNode("ファイル操作", nodChildFiles);
			treeView->Nodes->Add(nodFile);

			//インターネット接続
			array<TreeNode^>^ nodChildNet = {
				gcnew TreeNode("WinSock"),
				gcnew TreeNode("WinInet"),
			};

			TreeNode^ nodNet = gcnew TreeNode("インターネット接続", nodChildNet);
			treeView->Nodes->Add(nodNet);


			//レジストリ操作
			array<TreeNode^>^ nodChildRegistory= {
				gcnew TreeNode("RUNレジストリへの登録"),
			};

			TreeNode^ nodRegistory = gcnew TreeNode("レジストリ操作", nodChildRegistory);
			treeView->Nodes->Add(nodRegistory);

			//プロセス操作
			array<TreeNode^>^ nodChildProcess = {
				gcnew TreeNode("子プロセスの生成"),
			};

			TreeNode^ nodProcess = gcnew TreeNode("プロセス操作", nodChildProcess);
			treeView->Nodes->Add(nodProcess);
	
			//マルウェアっぽい挙動
			array<TreeNode^>^ nodChildMalware = {
				gcnew TreeNode("デバッガ検知"),
				gcnew TreeNode("暗号化処理"),
				gcnew TreeNode("自分自身の隠しファイル化"),
			};

			TreeNode^ nodMalware= gcnew TreeNode("マルウェアっぽい挙動", nodChildMalware);
			treeView->Nodes->Add(nodMalware);
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
	private: System::Windows::Forms::TreeView^ treeView;



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
			this->treeView = (gcnew System::Windows::Forms::TreeView());
			this->output_panel = (gcnew System::Windows::Forms::Panel());
			this->target_exe_selection_panel->SuspendLayout();
			this->checklist_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// target_exe_selection_panel
			// 
			this->target_exe_selection_panel->AllowDrop = true;
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
			this->target_exe_selection_panel->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainWindow::target_exe_selection_panel_DragDrop);
			this->target_exe_selection_panel->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainWindow::target_exe_selection_panel_DragEnter);
			// 
			// ExecBtn
			// 
			this->ExecBtn->Location = System::Drawing::Point(877, 81);
			this->ExecBtn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
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
			this->FileSelectBtn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
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
			this->FileSelectTextBox->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->FileSelectTextBox->Name = L"FileSelectTextBox";
			this->FileSelectTextBox->Size = System::Drawing::Size(688, 24);
			this->FileSelectTextBox->TabIndex = 0;
			// 
			// checklist_panel
			// 
			this->checklist_panel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->checklist_panel->Controls->Add(this->treeView);
			this->checklist_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->checklist_panel->Location = System::Drawing::Point(0, 208);
			this->checklist_panel->Margin = System::Windows::Forms::Padding(4);
			this->checklist_panel->Name = L"checklist_panel";
			this->checklist_panel->Size = System::Drawing::Size(1148, 540);
			this->checklist_panel->TabIndex = 1;
			// 
			// treeView
			// 
			this->treeView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeView->CheckBoxes = true;
			this->treeView->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12));
			this->treeView->Location = System::Drawing::Point(28, 19);
			this->treeView->Margin = System::Windows::Forms::Padding(4);
			this->treeView->Name = L"treeView";
			this->treeView->Size = System::Drawing::Size(591, 505);
			this->treeView->TabIndex = 0;
			this->treeView->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainWindow::treeView_AfterCheck);
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
			this->checklist_panel->ResumeLayout(false);
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
	
	// TODO: 
	char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	for (int i = 0; i < 4; i++) PathRemoveFileSpecA(path);
	strcat_s(path, "\\rules");

	if (PathFileExistsA(path)) {
		strcat_s(path, "\\rules.csv");

		HANDLE hFile;
		DWORD writesize;
		ApiDict^ ad = gcnew ApiDict();

		if (PathFileExistsA(path)) {
			DeleteFileA(path);
		}
		
		hFile = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		
		for each(TreeNode ^n in treeView->Nodes)
		{
			if (n!= nullptr)
			{
				//Using a queue to store and process each node in the TreeView
				NodeQueue ^staging = gcnew NodeQueue();
				staging->Enqueue(n);
				while (staging->Count > 0)
				{
					n = staging->Dequeue();
			
					if (n->Parent) {
						for each (String ^ s in ad->apiDict[n->Text]) {
							char buf[100];
							memset(buf, 0, 100);
							// char* apiName = (char*)Marshal::StringToHGlobalAnsi(s).ToPointer();
							marshal_context^ context = gcnew marshal_context();
							const char* apiName = context->marshal_as<const char*>(s);
							strcat(buf, apiName);
							strcat(buf, ",");
							char c = n->Checked + '0';
							strcat(buf, &c);
							strcat(buf, "\n");
							DWORD writesize;
							WriteFile(hFile, buf, strlen(buf), &writesize, NULL);
							SetFilePointer(hFile, 0, NULL, FILE_END);
						}
					}

					for each(TreeNode ^node in n->Nodes)
					{
						staging->Enqueue(node);
					}
				}
			}
		}
		CloseHandle(hFile);
	}


	msclr::interop::marshal_context context;
	LPCSTR exePath = context.marshal_as<const char*>(FileSelectTextBox->Text);
	char processPath[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);

	if (PathFileExistsA(exePath)) {
		// TODO: このパスの計算をいつか環境変数とかで整理したい
		//   例) [System.Environment]::SetEnvironmentVariable("SafeExecuteInstallDir", $PSScriptRoot, "Machine")
		for(int i=0; i<4; i++) PathRemoveFileSpecA(path);
		SetCurrentDirectoryA(path);
		char executorPath[MAX_PATH];
		snprintf(executorPath, MAX_PATH, "%s\\%s", path, "SafeExecutor\\x64\\Debug\\SafeExecutor.exe");
		char dllPath[MAX_PATH];
		snprintf(dllPath, MAX_PATH, "%s\\%s", path, "SafeExecute\\x64\\Debug\\SafeExecute.dll");

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

private: void CheckTreeViewNode(TreeNode^ node, BOOL isChecked) {
	for each (TreeNode^ n in node->Nodes) {
		n->Checked = isChecked;
		if (n->Nodes->Count > 0) {
			this->CheckTreeViewNode(n, isChecked);
		}
	}
}

private: System::Void treeView_AfterCheck(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e) {
	CheckTreeViewNode(e->Node, e->Node->Checked);
}

private: System::Void target_exe_selection_panel_DragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
	if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
		e->Effect = DragDropEffects::All;
	}
	else {
		e->Effect = DragDropEffects::None;
	}
}

private: System::Void target_exe_selection_panel_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
	array<String^>^ droppedFiles = (array<String^>^)e->Data->GetData(DataFormats::FileDrop);
	FileSelectTextBox->Text = droppedFiles[0];
}
};
}
