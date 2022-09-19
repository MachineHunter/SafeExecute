#pragma once

namespace WinForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainWindow �̊T�v
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ target_exe_selection_panel;
	private: System::Windows::Forms::Panel^ checklist_panel;
	private: System::Windows::Forms::Panel^ output_panel;
	protected:

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->target_exe_selection_panel = (gcnew System::Windows::Forms::Panel());
			this->checklist_panel = (gcnew System::Windows::Forms::Panel());
			this->output_panel = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// target_exe_selection_panel
			// 
			this->target_exe_selection_panel->BackColor = System::Drawing::SystemColors::HotTrack;
			resources->ApplyResources(this->target_exe_selection_panel, L"target_exe_selection_panel");
			this->target_exe_selection_panel->Name = L"target_exe_selection_panel";
			this->target_exe_selection_panel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainWindow::target_exe_selection_panel_Paint);
			// 
			// checklist_panel
			// 
			this->checklist_panel->BackColor = System::Drawing::SystemColors::InactiveCaption;
			resources->ApplyResources(this->checklist_panel, L"checklist_panel");
			this->checklist_panel->Name = L"checklist_panel";
			// 
			// output_panel
			// 
			this->output_panel->BackColor = System::Drawing::SystemColors::Info;
			resources->ApplyResources(this->output_panel, L"output_panel");
			this->output_panel->Name = L"output_panel";
			// 
			// MainWindow
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::Window;
			resources->ApplyResources(this, L"$this");
			this->Controls->Add(this->output_panel);
			this->Controls->Add(this->checklist_panel);
			this->Controls->Add(this->target_exe_selection_panel);
			this->Name = L"MainWindow";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void target_exe_selection_panel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	};
}
