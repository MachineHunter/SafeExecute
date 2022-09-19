#pragma once

namespace SafeExecutorGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
			this->checklist_panel = (gcnew System::Windows::Forms::Panel());
			this->output_panel = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// target_exe_selection_panel
			// 
			this->target_exe_selection_panel->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->target_exe_selection_panel->Dock = System::Windows::Forms::DockStyle::Top;
			this->target_exe_selection_panel->Location = System::Drawing::Point(0, 0);
			this->target_exe_selection_panel->Name = L"target_exe_selection_panel";
			this->target_exe_selection_panel->Size = System::Drawing::Size(861, 166);
			this->target_exe_selection_panel->TabIndex = 0;
			// 
			// checklist_panel
			// 
			this->checklist_panel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->checklist_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->checklist_panel->Location = System::Drawing::Point(0, 166);
			this->checklist_panel->Name = L"checklist_panel";
			this->checklist_panel->Size = System::Drawing::Size(861, 432);
			this->checklist_panel->TabIndex = 1;
			// 
			// output_panel
			// 
			this->output_panel->BackColor = System::Drawing::SystemColors::Info;
			this->output_panel->Dock = System::Windows::Forms::DockStyle::Right;
			this->output_panel->Location = System::Drawing::Point(482, 166);
			this->output_panel->Name = L"output_panel";
			this->output_panel->Size = System::Drawing::Size(379, 432);
			this->output_panel->TabIndex = 2;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(861, 598);
			this->Controls->Add(this->output_panel);
			this->Controls->Add(this->checklist_panel);
			this->Controls->Add(this->target_exe_selection_panel);
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
