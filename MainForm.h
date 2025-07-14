#pragma once

#using <System.Numerics.dll>
using namespace System::Numerics;

namespace FactorialCalculatorApp {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace System::Text;

	public ref class MainForm : public Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
				delete components;
		}

	private:
		// UI Elements
		System::Windows::Forms::Label^ titleLabel;
		System::Windows::Forms::TextBox^ inputBox;
		System::Windows::Forms::Button^ calculateBtn;
		System::Windows::Forms::Button^ clearBtn;
		System::Windows::Forms::Label^ resultLabel;
		System::Windows::Forms::Label^ formulaLabel;
		System::Windows::Forms::Label^ timeLabel;
		System::Windows::Forms::Label^ stepLabel;
		System::Windows::Forms::CheckBox^ bigIntCheckBox;
		System::Windows::Forms::Label^ fasterLabel;
		array<System::Windows::Forms::Button^>^ numpadButtons = gcnew array<Button^>(12);

		// Step Counters
		int recursiveSteps = 0;
		int iterativeSteps = 0;

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->ClientSize = Drawing::Size(400, 800);
			this->Text = L"Factorial Calculator";
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackColor = Color::LightGray;
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10);

			// Title
			titleLabel = gcnew Label();
			titleLabel->Text = L"Factorial Calculator";
			titleLabel->Font = gcnew Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
			titleLabel->ForeColor = Color::FromArgb(30, 30, 30);
			titleLabel->AutoSize = true;
			titleLabel->Location = Point(100, 20);

			// Input
			inputBox = gcnew TextBox();
			inputBox->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
			inputBox->Location = Point(20, 70);
			inputBox->Size = Drawing::Size(150, 40);
			inputBox->BackColor = Color::White;
			inputBox->BorderStyle = BorderStyle::FixedSingle;

			// Calculate Button
			calculateBtn = gcnew Button();
			calculateBtn->Text = L"Calculate";
			calculateBtn->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
			calculateBtn->Location = Point(190, 70);
			calculateBtn->Size = Drawing::Size(90, 40);
			calculateBtn->BackColor = Color::FromArgb(50, 120, 230);
			calculateBtn->ForeColor = Color::White;
			calculateBtn->FlatStyle = FlatStyle::Flat;
			calculateBtn->FlatAppearance->BorderSize = 0;
			calculateBtn->Click += gcnew EventHandler(this, &MainForm::calculateBtn_Click);

			// Clear Button
			clearBtn = gcnew Button();
			clearBtn->Text = L"Clear";
			clearBtn->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
			clearBtn->Location = Point(290, 70);
			clearBtn->Size = Drawing::Size(80, 40);
			clearBtn->BackColor = Color::WhiteSmoke;
			clearBtn->ForeColor = Color::Black;
			clearBtn->FlatStyle = FlatStyle::Flat;
			clearBtn->FlatAppearance->BorderSize = 0;
			clearBtn->Click += gcnew EventHandler(this, &MainForm::clearBtn_Click);

			// BigInt Toggle
			bigIntCheckBox = gcnew CheckBox();
			bigIntCheckBox->Text = L"Big Number Mode (If Number is More Than 20)";
			bigIntCheckBox->Location = Point(20, 125);
			bigIntCheckBox->AutoSize = true;
			bigIntCheckBox->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
			bigIntCheckBox->ForeColor = Color::Black;

			// --- Numpad Buttons Layout ---
			array<String^>^ labels = gcnew array<String^> {
					"7", "8", "9",
					"4", "5", "6",
					"1", "2", "3",
					"0", ".", "="
			};

			for (int i = 0; i < 12; ++i) {
				numpadButtons[i] = gcnew Button();
				numpadButtons[i]->Text = labels[i];
				numpadButtons[i]->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
				numpadButtons[i]->FlatStyle = FlatStyle::Flat;
				numpadButtons[i]->FlatAppearance->BorderSize = 0;
				numpadButtons[i]->Size = Drawing::Size(70, 50);
				numpadButtons[i]->BackColor = (labels[i] == "=")
					? Color::FromArgb(50, 120, 230)
					: Color::FromArgb(60, 60, 60);
				numpadButtons[i]->ForeColor = Color::White;

				// Position in 3x4 grid
				int row = i / 3;
				int col = i % 3;
				int x = 80 + col * 80;
				int y = 165 + row * 60;

				numpadButtons[i]->Location = Point(x, y);
				numpadButtons[i]->Click += gcnew EventHandler(this, &MainForm::numpadButton_Click);
				this->Controls->Add(numpadButtons[i]);
			}


			// Output Labels
			resultLabel = gcnew Label();
			resultLabel->Location = Point(20, 415);
			resultLabel->Size = Drawing::Size(350, 50);
			resultLabel->Font = gcnew Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
			resultLabel->ForeColor = Color::Black;
			resultLabel->Text = L"Result:";

			formulaLabel = gcnew Label();
			formulaLabel->Location = Point(20, 465);
			formulaLabel->Size = Drawing::Size(350, 140);
			formulaLabel->Font = gcnew Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
			formulaLabel->ForeColor = Color::Black;
			formulaLabel->Text = L"Formula:";

			timeLabel = gcnew Label();
			timeLabel->Location = Point(20, 605);
			timeLabel->Size = Drawing::Size(350, 50);
			timeLabel->Font = gcnew Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
			timeLabel->ForeColor = Color::Black;
			timeLabel->Text = L"Time:";

			stepLabel = gcnew Label();
			stepLabel->Location = Point(20, 655);
			stepLabel->Size = Drawing::Size(350, 50);
			stepLabel->Font = gcnew Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
			stepLabel->ForeColor = Color::Black;
			stepLabel->Text = L"Steps:";

			fasterLabel = gcnew Label();
			fasterLabel->Location = Point(20, 705);
			fasterLabel->Size = Drawing::Size(350, 50);
			fasterLabel->Font = gcnew Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
			fasterLabel->ForeColor = Color::FromArgb(50, 120, 230);
			fasterLabel->Text = L"Faster:";

			// Add to Form
			this->Controls->Add(titleLabel);
			this->Controls->Add(inputBox);
			this->Controls->Add(calculateBtn);
			this->Controls->Add(clearBtn);
			this->Controls->Add(bigIntCheckBox);
			this->Controls->Add(resultLabel);
			this->Controls->Add(formulaLabel);
			this->Controls->Add(timeLabel);
			this->Controls->Add(stepLabel);
			this->Controls->Add(fasterLabel);  // NEW
		}
#pragma endregion

		// Factorial Methods
		long long factorialRecursiveLL(int n) {
			recursiveSteps++;
			if (n <= 1) return 1;
			return n * factorialRecursiveLL(n - 1);
		}

		long long factorialIterativeLL(int n) {
			long long result = 1;
			iterativeSteps = 0;
			for (int i = 2; i <= n; ++i) {
				result *= i;
				iterativeSteps++;
			}
			return result;
		}

		BigInteger factorialRecursiveBI(int n) {
			recursiveSteps++;
			if (n <= 1) return 1;
			return BigInteger(n) * factorialRecursiveBI(n - 1);
		}

		BigInteger factorialIterativeBI(int n) {
			BigInteger result = 1;
			iterativeSteps = 0;
			for (int i = 2; i <= n; ++i) {
				result *= i;
				iterativeSteps++;
			}
			return result;
		}

		String^ getFactorialFormula(int n) {
			if (n <= 1) return n.ToString() + "! = 1";
			StringBuilder^ sb = gcnew StringBuilder();
			sb->Append(n.ToString() + "! = ");
			for (int i = n; i > 1; i--) sb->Append(i.ToString() + " × ");
			sb->Append("1");
			return sb->ToString();
		}

		System::Void calculateBtn_Click(Object^ sender, EventArgs^ e) {
			int n;
			if (!Int32::TryParse(inputBox->Text, n) || n < 0) {
				MessageBox::Show("Please enter a valid non-negative integer.");
				return;
			}

			bool useBigInt = bigIntCheckBox->Checked;
			const int runs = 100000;

			if (!useBigInt && n > 20) {
				MessageBox::Show("Warning: Value too large. Please enter a number between 0 - 20 or Enable BigInt mode.");
				return;
			}

			recursiveSteps = 0;
			iterativeSteps = 0;
			String^ result;
			String^ formula = getFactorialFormula(n);

			// Recursive Timing
			Stopwatch^ sw1 = Stopwatch::StartNew();
			for (int i = 0; i < runs; ++i) {
				if (useBigInt)
					factorialRecursiveBI(n);
				else
					factorialRecursiveLL(n);
			}
			sw1->Stop();

			// Iterative Timing
			Stopwatch^ sw2 = Stopwatch::StartNew();
			if (useBigInt) {
				BigInteger res;
				for (int i = 0; i < runs; ++i)
					res = factorialIterativeBI(n);
				result = res.ToString("N0");
			}
			else {
				long long res;
				for (int i = 0; i < runs; ++i)
					res = factorialIterativeLL(n);
				result = res.ToString("N0");
			}
			sw2->Stop();

			// Output
			resultLabel->Text = "Result: " + result;
			formulaLabel->Text = "Formula: " + formula;
			timeLabel->Text = "Recursive Time: " + sw1->ElapsedMilliseconds + " ms | Iterative Time: " + sw2->ElapsedMilliseconds + " ms";
			stepLabel->Text = "Recursive Steps: " + recursiveSteps + " | Iterative Steps: " + iterativeSteps;

			// Faster Method
			fasterLabel->Text = "Faster: " + (sw1->ElapsedMilliseconds > sw2->ElapsedMilliseconds ? "Iterative" : "Recursive");
		}

		System::Void numpadButton_Click(System::Object^ sender, System::EventArgs^ e) {
			Button^ btn = dynamic_cast<Button^>(sender);
			if (btn == nullptr) return;

			String^ value = btn->Text;

			if (value == "=") {
				calculateBtn_Click(sender, e); // Trigger main calculate
			}
			else {
				inputBox->Text += value;
			}
		}


		System::Void clearBtn_Click(Object^ sender, EventArgs^ e) {
			inputBox->Text = "";
			resultLabel->Text = "Result:";
			formulaLabel->Text = "Formula:";
			timeLabel->Text = "Time:";
			stepLabel->Text = "Steps:";
			fasterLabel->Text = "Faster:";
		}
	};
}
