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
			
			array<TreeNode^>^ nodChildFiles = {
				gcnew TreeNode("ファイル名変更"),
				gcnew TreeNode("ファイル削除"),
				gcnew TreeNode("ファイル書き込み"),
				gcnew TreeNode("ファイル走査")
			};
			TreeNode^ nodFile = gcnew TreeNode("ファイル操作", nodChildFiles);
			treeView->Nodes->Add(nodFile);

			array<TreeNode^>^ nodChildNet = {
				gcnew TreeNode("WinSock"),
				gcnew TreeNode("WinInet"),
				gcnew TreeNode("ファイルダウンロード")
			};
			TreeNode^ nodNet = gcnew TreeNode("インターネット接続", nodChildNet);
			treeView->Nodes->Add(nodNet);
			
			array<TreeNode^>^ nodChildRegistory= {
				gcnew TreeNode("RUNレジストリへの登録"),
			};
			TreeNode^ nodRegistory = gcnew TreeNode("レジストリ操作", nodChildRegistory);
			treeView->Nodes->Add(nodRegistory);
			
			array<TreeNode^>^ nodChildProcess = {
				gcnew TreeNode("子プロセスの生成"),
				gcnew TreeNode("プロセスの権限変更")
			};
			TreeNode^ nodProcess = gcnew TreeNode("プロセス操作", nodChildProcess);
			treeView->Nodes->Add(nodProcess);
			
			array<TreeNode^>^ nodChildMalware = {
				gcnew TreeNode("デバッガ検知"),
				gcnew TreeNode("暗号化処理"),
				gcnew TreeNode("自分自身の隠しファイル化"),
				gcnew TreeNode("ロケール情報の取得"),
				gcnew TreeNode("タイマーの使用"),
				gcnew TreeNode("デスクトップ壁紙の変更")
			};
			TreeNode^ nodMalware= gcnew TreeNode("マルウェアっぽい挙動", nodChildMalware);
			treeView->Nodes->Add(nodMalware);

			array<TreeNode^>^ nodChildFunction = {
				gcnew TreeNode("ファイルのバックアップ"),
			};
			TreeNode^ nodFunction = gcnew TreeNode("機能", nodChildFunction);
			nodFunction->Checked = true;
			for each (TreeNode ^ n in nodChildFunction) n->Checked = true;
			treeView->Nodes->Add(nodFunction);
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
	private: System::Windows::Forms::Button^ ArgButton;
	private: System::Windows::Forms::TextBox^ ArgTextBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ clearButton;
	private: System::Windows::Forms::Button^ selectAllButton;




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
			this->ArgButton = (gcnew System::Windows::Forms::Button());
			this->ArgTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ExecBtn = (gcnew System::Windows::Forms::Button());
			this->FileSelectBtn = (gcnew System::Windows::Forms::Button());
			this->FileSelectTextBox = (gcnew System::Windows::Forms::TextBox());
			this->checklist_panel = (gcnew System::Windows::Forms::Panel());
			this->clearButton = (gcnew System::Windows::Forms::Button());
			this->selectAllButton = (gcnew System::Windows::Forms::Button());
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
			this->target_exe_selection_panel->Controls->Add(this->ArgButton);
			this->target_exe_selection_panel->Controls->Add(this->ArgTextBox);
			this->target_exe_selection_panel->Controls->Add(this->label2);
			this->target_exe_selection_panel->Controls->Add(this->label1);
			this->target_exe_selection_panel->Controls->Add(this->ExecBtn);
			this->target_exe_selection_panel->Controls->Add(this->FileSelectBtn);
			this->target_exe_selection_panel->Controls->Add(this->FileSelectTextBox);
			this->target_exe_selection_panel->Dock = System::Windows::Forms::DockStyle::Top;
			this->target_exe_selection_panel->Location = System::Drawing::Point(0, 0);
			this->target_exe_selection_panel->Margin = System::Windows::Forms::Padding(4);
			this->target_exe_selection_panel->Name = L"target_exe_selection_panel";
			this->target_exe_selection_panel->Size = System::Drawing::Size(1148, 134);
			this->target_exe_selection_panel->TabIndex = 0;
			this->target_exe_selection_panel->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainWindow::target_exe_selection_panel_DragDrop);
			this->target_exe_selection_panel->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainWindow::target_exe_selection_panel_DragEnter);
			// 
			// ArgButton
			// 
			this->ArgButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ArgButton->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.5F));
			this->ArgButton->Location = System::Drawing::Point(897, 76);
			this->ArgButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->ArgButton->Name = L"ArgButton";
			this->ArgButton->Size = System::Drawing::Size(79, 33);
			this->ArgButton->TabIndex = 3;
			this->ArgButton->TabStop = false;
			this->ArgButton->Text = L"参照";
			this->ArgButton->UseVisualStyleBackColor = true;
			this->ArgButton->Click += gcnew System::EventHandler(this, &MainWindow::ArgButton_Click);
			// 
			// ArgTextBox
			// 
			this->ArgTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->ArgTextBox->BackColor = System::Drawing::Color::White;
			this->ArgTextBox->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 10, System::Drawing::FontStyle::Bold));
			this->ArgTextBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->ArgTextBox->Location = System::Drawing::Point(135, 81);
			this->ArgTextBox->Margin = System::Windows::Forms::Padding(4);
			this->ArgTextBox->Name = L"ArgTextBox";
			this->ArgTextBox->Size = System::Drawing::Size(753, 24);
			this->ArgTextBox->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"メイリオ", 11));
			this->label2->Location = System::Drawing::Point(77, 81);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 28);
			this->label2->TabIndex = 4;
			this->label2->Text = L"引数";
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"メイリオ", 11));
			this->label1->Location = System::Drawing::Point(3, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(126, 28);
			this->label1->TabIndex = 3;
			this->label1->Text = L"実行ファイル";
			// 
			// ExecBtn
			// 
			this->ExecBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ExecBtn->Font = (gcnew System::Drawing::Font(L"HG行書体", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ExecBtn->Location = System::Drawing::Point(1000, 31);
			this->ExecBtn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->ExecBtn->Name = L"ExecBtn";
			this->ExecBtn->Size = System::Drawing::Size(128, 68);
			this->ExecBtn->TabIndex = 2;
			this->ExecBtn->Text = L"実行";
			this->ExecBtn->UseVisualStyleBackColor = true;
			this->ExecBtn->Click += gcnew System::EventHandler(this, &MainWindow::ExecBtn_Click);
			// 
			// FileSelectBtn
			// 
			this->FileSelectBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->FileSelectBtn->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.5F));
			this->FileSelectBtn->Location = System::Drawing::Point(896, 22);
			this->FileSelectBtn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->FileSelectBtn->Name = L"FileSelectBtn";
			this->FileSelectBtn->Size = System::Drawing::Size(79, 33);
			this->FileSelectBtn->TabIndex = 1;
			this->FileSelectBtn->TabStop = false;
			this->FileSelectBtn->Text = L"参照";
			this->FileSelectBtn->UseVisualStyleBackColor = true;
			this->FileSelectBtn->Click += gcnew System::EventHandler(this, &MainWindow::FileSelectBtn_Click);
			// 
			// FileSelectTextBox
			// 
			this->FileSelectTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->FileSelectTextBox->BackColor = System::Drawing::Color::White;
			this->FileSelectTextBox->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 10, System::Drawing::FontStyle::Bold));
			this->FileSelectTextBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->FileSelectTextBox->Location = System::Drawing::Point(135, 26);
			this->FileSelectTextBox->Margin = System::Windows::Forms::Padding(4);
			this->FileSelectTextBox->Name = L"FileSelectTextBox";
			this->FileSelectTextBox->Size = System::Drawing::Size(753, 24);
			this->FileSelectTextBox->TabIndex = 0;
			// 
			// checklist_panel
			// 
			this->checklist_panel->BackColor = System::Drawing::SystemColors::Window;
			this->checklist_panel->Controls->Add(this->clearButton);
			this->checklist_panel->Controls->Add(this->selectAllButton);
			this->checklist_panel->Controls->Add(this->pictureBox1);
			this->checklist_panel->Controls->Add(this->checkboxZoneTitle);
			this->checklist_panel->Controls->Add(this->treeView);
			this->checklist_panel->Dock = System::Windows::Forms::DockStyle::Left;
			this->checklist_panel->Location = System::Drawing::Point(0, 134);
			this->checklist_panel->Margin = System::Windows::Forms::Padding(4);
			this->checklist_panel->Name = L"checklist_panel";
			this->checklist_panel->Size = System::Drawing::Size(647, 614);
			this->checklist_panel->TabIndex = 1;
			// 
			// clearButton
			// 
			this->clearButton->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.5F));
			this->clearButton->Location = System::Drawing::Point(492, 30);
			this->clearButton->Name = L"clearButton";
			this->clearButton->Size = System::Drawing::Size(80, 40);
			this->clearButton->TabIndex = 4;
			this->clearButton->TabStop = false;
			this->clearButton->Text = L"クリア";
			this->clearButton->UseVisualStyleBackColor = true;
			this->clearButton->Click += gcnew System::EventHandler(this, &MainWindow::clearButton_Click);
			// 
			// selectAllButton
			// 
			this->selectAllButton->Font = (gcnew System::Drawing::Font(L"メイリオ", 10.5F));
			this->selectAllButton->Location = System::Drawing::Point(396, 30);
			this->selectAllButton->Name = L"selectAllButton";
			this->selectAllButton->Size = System::Drawing::Size(80, 40);
			this->selectAllButton->TabIndex = 3;
			this->selectAllButton->TabStop = false;
			this->selectAllButton->Text = L"全選択";
			this->selectAllButton->UseVisualStyleBackColor = true;
			this->selectAllButton->Click += gcnew System::EventHandler(this, &MainWindow::selectAllButton_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(385, 135);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(263, 450);
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
			this->checkboxZoneTitle->Location = System::Drawing::Point(29, 30);
			this->checkboxZoneTitle->Margin = System::Windows::Forms::Padding(4);
			this->checkboxZoneTitle->Name = L"checkboxZoneTitle";
			this->checkboxZoneTitle->Size = System::Drawing::Size(345, 40);
			this->checkboxZoneTitle->TabIndex = 1;
			this->checkboxZoneTitle->TabStop = false;
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
			this->treeView->Location = System::Drawing::Point(29, 108);
			this->treeView->Margin = System::Windows::Forms::Padding(4);
			this->treeView->Name = L"treeView";
			this->treeView->Size = System::Drawing::Size(355, 491);
			this->treeView->TabIndex = 0;
			this->treeView->TabStop = false;
			this->treeView->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainWindow::treeView_AfterCheck);
			// 
			// output_panel
			// 
			this->output_panel->BackColor = System::Drawing::Color::White;
			this->output_panel->Controls->Add(this->OutputTabControl);
			this->output_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->output_panel->Location = System::Drawing::Point(647, 134);
			this->output_panel->Margin = System::Windows::Forms::Padding(4);
			this->output_panel->Name = L"output_panel";
			this->output_panel->Size = System::Drawing::Size(501, 614);
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
			this->OutputTabControl->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->OutputTabControl->Name = L"OutputTabControl";
			this->OutputTabControl->SelectedIndex = 0;
			this->OutputTabControl->Size = System::Drawing::Size(501, 614);
			this->OutputTabControl->TabIndex = 1;
			this->OutputTabControl->TabStop = false;
			// 
			// stdoutPage
			// 
			this->stdoutPage->Controls->Add(this->OutputBox);
			this->stdoutPage->Location = System::Drawing::Point(4, 34);
			this->stdoutPage->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->stdoutPage->Name = L"stdoutPage";
			this->stdoutPage->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->stdoutPage->Size = System::Drawing::Size(493, 576);
			this->stdoutPage->TabIndex = 0;
			this->stdoutPage->Text = L"標準出力";
			this->stdoutPage->UseVisualStyleBackColor = true;
			// 
			// OutputBox
			// 
			this->OutputBox->BackColor = System::Drawing::Color::Black;
			this->OutputBox->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->OutputBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->OutputBox->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 11));
			this->OutputBox->ForeColor = System::Drawing::Color::White;
			this->OutputBox->Location = System::Drawing::Point(3, 2);
			this->OutputBox->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->OutputBox->Name = L"OutputBox";
			this->OutputBox->ReadOnly = true;
			this->OutputBox->Size = System::Drawing::Size(487, 572);
			this->OutputBox->TabIndex = 0;
			this->OutputBox->TabStop = false;
			this->OutputBox->Text = L"";
			// 
			// stderrPage
			// 
			this->stderrPage->Controls->Add(this->OutputErrBox);
			this->stderrPage->Location = System::Drawing::Point(4, 34);
			this->stderrPage->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->stderrPage->Name = L"stderrPage";
			this->stderrPage->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->stderrPage->Size = System::Drawing::Size(493, 576);
			this->stderrPage->TabIndex = 1;
			this->stderrPage->Text = L"エラー出力";
			this->stderrPage->UseVisualStyleBackColor = true;
			// 
			// OutputErrBox
			// 
			this->OutputErrBox->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->OutputErrBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->OutputErrBox->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 11));
			this->OutputErrBox->ForeColor = System::Drawing::Color::White;
			this->OutputErrBox->Location = System::Drawing::Point(3, 2);
			this->OutputErrBox->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->OutputErrBox->Name = L"OutputErrBox";
			this->OutputErrBox->ReadOnly = true;
			this->OutputErrBox->Size = System::Drawing::Size(487, 572);
			this->OutputErrBox->TabIndex = 0;
			this->OutputErrBox->Text = L"";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1148, 748);
			this->Controls->Add(this->output_panel);
			this->Controls->Add(this->checklist_panel);
			this->Controls->Add(this->target_exe_selection_panel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->MinimumSize = System::Drawing::Size(1166, 795);
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
			char arg[MAX_PATH * 10];
			memset(arg, 0, sizeof(arg));
			strcat_s(arg, dllPath);
			strcat_s(arg, " ");
			strcat_s(arg, exePath);

			if (!String::IsNullOrEmpty(ArgTextBox->Text)) {
				LPCSTR cmdlineArgs = context.marshal_as<const char*>(ArgTextBox->Text);
				strcat_s(arg, " ");
				strcat_s(arg, cmdlineArgs);
			}
			
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
private: System::Void ArgButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Stream^ stream;
	OpenFileDialog^ dig = gcnew OpenFileDialog;

	dig->Filter = "All Files|*.*";
	dig->FilterIndex = 1;
	dig->RestoreDirectory = true;
	if (dig->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		if ((stream = dig->OpenFile()) != nullptr) {
			ArgTextBox->Text = dig->FileName;
			stream->Close();
		}
	}
}
private: System::Void selectAllButton_Click(System::Object^ sender, System::EventArgs^ e) {
	for each (TreeNode ^ n in treeView->Nodes)
		n->Checked = true;
}
private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e) {
	for each (TreeNode ^ n in treeView->Nodes)
		n->Checked = false;
}
};
}
