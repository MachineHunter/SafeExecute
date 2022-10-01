#pragma once
#include <Windows.h>
#include <msclr/marshal.h>
#include <vector>
#include <atlstr.h>
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
	using namespace System::Diagnostics;
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
	private: System::Windows::Forms::RichTextBox^ OutputBox;
	private: System::Windows::Forms::TabControl^ OutputTabControl;
	private: System::Windows::Forms::TabPage^ stdoutPage;
	private: System::Windows::Forms::TabPage^ stderrPage;
	private: System::Windows::Forms::RichTextBox^ OutputErrBox;
	private: System::Windows::Forms::TextBox^ checkboxZoneTitle;
	private: System::Windows::Forms::PictureBox^ pictureBox1;




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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->target_exe_selection_panel = (gcnew System::Windows::Forms::Panel());
			this->ExecBtn = (gcnew System::Windows::Forms::Button());
			this->FileSelectBtn = (gcnew System::Windows::Forms::Button());
			this->FileSelectTextBox = (gcnew System::Windows::Forms::TextBox());
			this->checklist_panel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->checkboxZoneTitle = (gcnew System::Windows::Forms::TextBox());
			this->treeView = (gcnew System::Windows::Forms::TreeView());
			this->output_panel = (gcnew System::Windows::Forms::Panel());
			this->OutputTabControl = (gcnew System::Windows::Forms::TabControl());
			this->stdoutPage = (gcnew System::Windows::Forms::TabPage());
			this->OutputBox = (gcnew System::Windows::Forms::RichTextBox());
			this->stderrPage = (gcnew System::Windows::Forms::TabPage());
			this->OutputErrBox = (gcnew System::Windows::Forms::RichTextBox());
			this->target_exe_selection_panel->SuspendLayout();
			this->checklist_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->output_panel->SuspendLayout();
			this->OutputTabControl->SuspendLayout();
			this->stdoutPage->SuspendLayout();
			this->stderrPage->SuspendLayout();
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
			this->target_exe_selection_panel->Name = L"target_exe_selection_panel";
			this->target_exe_selection_panel->Size = System::Drawing::Size(861, 83);
			this->target_exe_selection_panel->TabIndex = 0;
			this->target_exe_selection_panel->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainWindow::target_exe_selection_panel_DragDrop);
			this->target_exe_selection_panel->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainWindow::target_exe_selection_panel_DragEnter);
			// 
			// ExecBtn
			// 
			this->ExecBtn->Font = (gcnew System::Drawing::Font(L"メイリオ", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ExecBtn->Location = System::Drawing::Point(742, 21);
			this->ExecBtn->Margin = System::Windows::Forms::Padding(2);
			this->ExecBtn->Name = L"ExecBtn";
			this->ExecBtn->Size = System::Drawing::Size(80, 42);
			this->ExecBtn->TabIndex = 2;
			this->ExecBtn->Text = L"実行";
			this->ExecBtn->UseVisualStyleBackColor = true;
			this->ExecBtn->Click += gcnew System::EventHandler(this, &MainWindow::ExecBtn_Click);
			// 
			// FileSelectBtn
			// 
			this->FileSelectBtn->Font = (gcnew System::Drawing::Font(L"メイリオ", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->FileSelectBtn->Location = System::Drawing::Point(640, 21);
			this->FileSelectBtn->Margin = System::Windows::Forms::Padding(2);
			this->FileSelectBtn->Name = L"FileSelectBtn";
			this->FileSelectBtn->Size = System::Drawing::Size(80, 42);
			this->FileSelectBtn->TabIndex = 1;
			this->FileSelectBtn->Text = L"参照";
			this->FileSelectBtn->UseVisualStyleBackColor = true;
			this->FileSelectBtn->Click += gcnew System::EventHandler(this, &MainWindow::FileSelectBtn_Click);
			// 
			// FileSelectTextBox
			// 
			this->FileSelectTextBox->BackColor = System::Drawing::Color::White;
			this->FileSelectTextBox->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->FileSelectTextBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->FileSelectTextBox->Location = System::Drawing::Point(47, 31);
			this->FileSelectTextBox->Name = L"FileSelectTextBox";
			this->FileSelectTextBox->Size = System::Drawing::Size(566, 22);
			this->FileSelectTextBox->TabIndex = 0;
			// 
			// checklist_panel
			// 
			this->checklist_panel->BackColor = System::Drawing::SystemColors::Window;
			this->checklist_panel->Controls->Add(this->pictureBox1);
			this->checklist_panel->Controls->Add(this->checkboxZoneTitle);
			this->checklist_panel->Controls->Add(this->treeView);
			this->checklist_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->checklist_panel->Location = System::Drawing::Point(0, 83);
			this->checklist_panel->Name = L"checklist_panel";
			this->checklist_panel->Size = System::Drawing::Size(861, 515);
			this->checklist_panel->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(267, 108);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(197, 360);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MainWindow::pictureBox1_Click);
			// 
			// checkboxZoneTitle
			// 
			this->checkboxZoneTitle->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->checkboxZoneTitle->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->checkboxZoneTitle->Font = (gcnew System::Drawing::Font(L"メイリオ", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->checkboxZoneTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->checkboxZoneTitle->Location = System::Drawing::Point(22, 24);
			this->checkboxZoneTitle->Name = L"checkboxZoneTitle";
			this->checkboxZoneTitle->Size = System::Drawing::Size(259, 32);
			this->checkboxZoneTitle->TabIndex = 1;
			this->checkboxZoneTitle->Text = L"[実行に制限をかける項目]";
			this->checkboxZoneTitle->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->checkboxZoneTitle->TextChanged += gcnew System::EventHandler(this, &MainWindow::textBox1_TextChanged);
			// 
			// treeView
			// 
			this->treeView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeView->CheckBoxes = true;
			this->treeView->Font = (gcnew System::Drawing::Font(L"メイリオ", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->treeView->LineColor = System::Drawing::Color::White;
			this->treeView->Location = System::Drawing::Point(22, 86);
			this->treeView->Name = L"treeView";
			this->treeView->Size = System::Drawing::Size(442, 417);
			this->treeView->TabIndex = 0;
			this->treeView->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainWindow::treeView_AfterCheck);
			// 
			// output_panel
			// 
			this->output_panel->BackColor = System::Drawing::Color::White;
			this->output_panel->Controls->Add(this->OutputTabControl);
			this->output_panel->Dock = System::Windows::Forms::DockStyle::Right;
			this->output_panel->Location = System::Drawing::Point(482, 83);
			this->output_panel->Name = L"output_panel";
			this->output_panel->Size = System::Drawing::Size(379, 515);
			this->output_panel->TabIndex = 2;
			// 
			// OutputTabControl
			// 
			this->OutputTabControl->Controls->Add(this->stdoutPage);
			this->OutputTabControl->Controls->Add(this->stderrPage);
			this->OutputTabControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->OutputTabControl->Font = (gcnew System::Drawing::Font(L"メイリオ", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->OutputTabControl->ItemSize = System::Drawing::Size(60, 30);
			this->OutputTabControl->Location = System::Drawing::Point(0, 0);
			this->OutputTabControl->Margin = System::Windows::Forms::Padding(2);
			this->OutputTabControl->Name = L"OutputTabControl";
			this->OutputTabControl->SelectedIndex = 0;
			this->OutputTabControl->Size = System::Drawing::Size(379, 515);
			this->OutputTabControl->TabIndex = 1;
			// 
			// stdoutPage
			// 
			this->stdoutPage->Controls->Add(this->OutputBox);
			this->stdoutPage->Location = System::Drawing::Point(4, 34);
			this->stdoutPage->Margin = System::Windows::Forms::Padding(2);
			this->stdoutPage->Name = L"stdoutPage";
			this->stdoutPage->Padding = System::Windows::Forms::Padding(2);
			this->stdoutPage->Size = System::Drawing::Size(371, 477);
			this->stdoutPage->TabIndex = 0;
			this->stdoutPage->Text = L"標準出力";
			this->stdoutPage->UseVisualStyleBackColor = true;
			// 
			// OutputBox
			// 
			this->OutputBox->BackColor = System::Drawing::Color::Black;
			this->OutputBox->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->OutputBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->OutputBox->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14));
			this->OutputBox->ForeColor = System::Drawing::Color::White;
			this->OutputBox->Location = System::Drawing::Point(2, 2);
			this->OutputBox->Margin = System::Windows::Forms::Padding(2);
			this->OutputBox->Name = L"OutputBox";
			this->OutputBox->ReadOnly = true;
			this->OutputBox->Size = System::Drawing::Size(367, 473);
			this->OutputBox->TabIndex = 0;
			this->OutputBox->Text = L"";
			// 
			// stderrPage
			// 
			this->stderrPage->Controls->Add(this->OutputErrBox);
			this->stderrPage->Location = System::Drawing::Point(4, 34);
			this->stderrPage->Margin = System::Windows::Forms::Padding(2);
			this->stderrPage->Name = L"stderrPage";
			this->stderrPage->Padding = System::Windows::Forms::Padding(2);
			this->stderrPage->Size = System::Drawing::Size(371, 477);
			this->stderrPage->TabIndex = 1;
			this->stderrPage->Text = L"エラー出力";
			this->stderrPage->UseVisualStyleBackColor = true;
			// 
			// OutputErrBox
			// 
			this->OutputErrBox->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->OutputErrBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->OutputErrBox->ForeColor = System::Drawing::Color::White;
			this->OutputErrBox->Location = System::Drawing::Point(2, 2);
			this->OutputErrBox->Margin = System::Windows::Forms::Padding(2);
			this->OutputErrBox->Name = L"OutputErrBox";
			this->OutputErrBox->ReadOnly = true;
			this->OutputErrBox->Size = System::Drawing::Size(367, 473);
			this->OutputErrBox->TabIndex = 0;
			this->OutputErrBox->Text = L"";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(861, 598);
			this->Controls->Add(this->output_panel);
			this->Controls->Add(this->checklist_panel);
			this->Controls->Add(this->target_exe_selection_panel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainWindow";
			this->Text = L"安全実行侍~俺を信じろ~";
			this->target_exe_selection_panel->ResumeLayout(false);
			this->target_exe_selection_panel->PerformLayout();
			this->checklist_panel->ResumeLayout(false);
			this->checklist_panel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->output_panel->ResumeLayout(false);
			this->OutputTabControl->ResumeLayout(false);
			this->stdoutPage->ResumeLayout(false);
			this->stderrPage->ResumeLayout(false);
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
			char arg[MAX_PATH * 3];
			memset(arg, 0, sizeof(arg));
			strcat_s(arg, dllPath);
			strcat_s(arg, " ");
			strcat_s(arg, exePath);
			
			Process^ pProc = gcnew Process();
			pProc->StartInfo->FileName = gcnew String(executorPath);
			pProc->StartInfo->Arguments = gcnew String(arg);
			pProc->StartInfo->UseShellExecute = false;
			pProc->StartInfo->RedirectStandardOutput = true;
			pProc->StartInfo->RedirectStandardError = true;
			// pProc->StartInfo->RedirectStandardInput = true;
			pProc->Start();

			String^ stdOut = "";
			String^ stdErr = "";
			while (!pProc->HasExited) {
				stdOut += pProc->StandardOutput->ReadToEnd();
				stdErr += pProc->StandardError->ReadToEnd();
			}
			if (stdOut->Length != 0) {
				OutputBox->Text += stdOut;
				OutputBox->Text += "\n";
			}
			if (stdErr->Length != 0) {
				OutputErrBox->Text += stdErr;
				OutputErrBox->Text += "\n";
			}
			pProc->WaitForExit();
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
	if (e->Data->GetDataPresent(DataFormats::FileDrop))
		e->Effect = DragDropEffects::All;
	else
		e->Effect = DragDropEffects::None;
}

private: System::Void target_exe_selection_panel_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
	array<String^>^ droppedFiles = (array<String^>^)e->Data->GetData(DataFormats::FileDrop);
	FileSelectTextBox->Text = droppedFiles[0];
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
