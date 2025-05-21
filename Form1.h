#pragma once

#include "People.h"
#include "AddForm.h"
#include <msclr/marshal_cppstd.h>

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#using <System.Data.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data;

namespace DarinaWind {

    public ref class Form1 : public Form
    {
    public:

        Form1(void)
        {
            InitializeComponent();
            org = new Organisation();
            org->load();
            UpdateDataGridView();
        }

    protected:
        ~Form1()
        {
            if (components)
                delete components;
            delete org;
        }

    private:
        Organisation* org;
        System::Windows::Forms::DataGridView^ dataGridView;
        System::Windows::Forms::Button^ btnShow;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnCalculate;
        System::Windows::Forms::Button^ btnSort;
        System::Windows::Forms::ComboBox^ cmbSortBy;
        System::ComponentModel::IContainer^ components;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            // DataGridView
            this->dataGridView = gcnew System::Windows::Forms::DataGridView();
            this->dataGridView->Location = System::Drawing::Point(10, 10);
            this->dataGridView->Size = System::Drawing::Size(780, 400);
            this->dataGridView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Bottom);
            this->dataGridView->ReadOnly = true;
            this->dataGridView->AllowUserToAddRows = false;
            this->dataGridView->AllowUserToDeleteRows = false;
            this->dataGridView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;

            // Buttons
            this->btnShow = gcnew System::Windows::Forms::Button();
            this->btnShow->Text = L"Показать список";
            this->btnShow->Location = System::Drawing::Point(10, 420);
            this->btnShow->Size = System::Drawing::Size(120, 30);

            this->btnAdd = gcnew System::Windows::Forms::Button();
            this->btnAdd->Text = L"Добавить";
            this->btnAdd->Location = System::Drawing::Point(140, 420);
            this->btnAdd->Size = System::Drawing::Size(120, 30);

            this->btnDelete = gcnew System::Windows::Forms::Button();
            this->btnDelete->Text = L"Удалить";
            this->btnDelete->Location = System::Drawing::Point(270, 420);
            this->btnDelete->Size = System::Drawing::Size(120, 30);

            this->btnCalculate = gcnew System::Windows::Forms::Button();
            this->btnCalculate->Text = L"Рассчитать стаж";
            this->btnCalculate->Location = System::Drawing::Point(400, 420);
            this->btnCalculate->Size = System::Drawing::Size(120, 30);

            this->btnSort = gcnew System::Windows::Forms::Button();
            this->btnSort->Text = L"Сортировать";
            this->btnSort->Location = System::Drawing::Point(530, 420);
            this->btnSort->Size = System::Drawing::Size(120, 30);

            // ComboBox
            this->cmbSortBy = gcnew System::Windows::Forms::ComboBox();
            this->cmbSortBy->Location = System::Drawing::Point(660, 420);
            this->cmbSortBy->Size = System::Drawing::Size(120, 30);
            this->cmbSortBy->Items->Add(L"По имени");
            this->cmbSortBy->Items->Add(L"По фамилии");
            this->cmbSortBy->Items->Add(L"По дате приема");
            this->cmbSortBy->Items->Add(L"По дате увольнения");
            this->cmbSortBy->Items->Add(L"По стажу");
            this->cmbSortBy->SelectedIndex = 0;

            // Form settings
            this->Text = L"Учет сотрудников";
            this->ClientSize = System::Drawing::Size(800, 470);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            // Add controls to form
            this->Controls->Add(this->dataGridView);
            this->Controls->Add(this->btnShow);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->btnCalculate);
            this->Controls->Add(this->btnSort);
            this->Controls->Add(this->cmbSortBy);

            // Event handlers
            this->btnShow->Click += gcnew System::EventHandler(this, &Form1::btnShow_Click);
            this->btnAdd->Click += gcnew System::EventHandler(this, &Form1::btnAdd_Click);
            this->btnDelete->Click += gcnew System::EventHandler(this, &Form1::btnDelete_Click);
            this->btnCalculate->Click += gcnew System::EventHandler(this, &Form1::btnCalculate_Click);
            this->btnSort->Click += gcnew System::EventHandler(this, &Form1::btnSort_Click);
        }

        void UpdateDataGridView()
        {
            this->dataGridView->Rows->Clear();
            this->dataGridView->Columns->Clear();

            // Add columns
            this->dataGridView->Columns->Add(L"num", L"№");
            this->dataGridView->Columns->Add(L"name", L"Имя");
            this->dataGridView->Columns->Add(L"firstname", L"Фамилия");
            this->dataGridView->Columns->Add(L"date_hiring", L"Дата приема");
            this->dataGridView->Columns->Add(L"date_firing", L"Дата увольнения");
            this->dataGridView->Columns->Add(L"reason", L"Причина увольнения");
            this->dataGridView->Columns->Add(L"gratitude", L"Благодарность");
            this->dataGridView->Columns->Add(L"experience", L"Стаж");

            // Add data
            for (int i = 0; i < org->num_people; i++)
            {
                this->dataGridView->Rows->Add(
                    org->ppl[i].num,
                    marshal_as<String^>(org->ppl[i].name),
                    marshal_as<String^>(org->ppl[i].firstname),
                    marshal_as<String^>(org->ppl[i].date_hiring),
                    marshal_as<String^>(org->ppl[i].date_firing),
                    marshal_as<String^>(org->ppl[i].reason_firing),
                    marshal_as<String^>(org->ppl[i].gratitude),
                    marshal_as<String^>(org->ppl[i].experience)
                );
            }
        }

    private:
        void btnShow_Click(Object^ sender, EventArgs^ e) {
            org->load();
            UpdateDataGridView();
        }

        void btnAdd_Click(Object^ sender, EventArgs^ e) {
            People newPeople;
            Form^ addForm = gcnew AddForm();
            addForm->Show();
        }

        void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (dataGridView->SelectedRows->Count > 0)
            {
                int selectedIndex = dataGridView->SelectedRows[0]->Index;
                int numToDelete = Convert::ToInt32(dataGridView->Rows[selectedIndex]->Cells[0]->Value);

                org->del_people(numToDelete);
                org->load();
                UpdateDataGridView();
            }
            else
            {
                MessageBox::Show(L"Выберите запись для удаления!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void btnCalculate_Click(Object^ sender, EventArgs^ e) {
            org->calcul();
            MessageBox::Show(L"Расчет стажа выполнен!", L"Информация",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnSort_Click(Object^ sender, EventArgs^ e) {
            int sortBy = cmbSortBy->SelectedIndex + 1;
            org->sort_by(sortBy);
            UpdateDataGridView();
        }
    };
}