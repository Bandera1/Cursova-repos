#include "Header.h"

using namespace std;

const int NotUsed = system("color 02"); // ��������� ����� ��� ���� �������

// ������� - �������

//--------------------------------------------
//-------��������� ������� � ��������------------
//--------------------------------------------

struct shop;
void product_menu(shop&);
void leader_menu(shop&);
void worker_menu(shop&);
void stats(shop);
void sign_in(shop&);
void buyer_menu(shop&, float&);

//--------------------------------------------
//-------��������� ��������------------
//--------------------------------------------

struct date // ��������� ��� ����
{
	int month, day;
	float year;
	void fill_date(int min, int max) // ������� ����������� ���������� ����
	{
		year = min + (rand() % (max - min));
		month = 1 + rand() % 11;
		day = 1 + rand() % 30;

	}

	void show_date() // �������,���,�� ����� ������.�����Ӫ ���� -____-
	{
		cout << year << "/" << month << "/" << day;
	}

};

struct product // ��������� ��������
{
	string name, type, comment; // ��'�,��� � ���� ������
	float cost; // ֳ��
	int popular = 0; // ����������� ������� ������
	date Shelf_life[2]; // ���� ����������

	void show_info() // ������ ���������� ��� ������ �������
	{
		cout << setw(15) << name << setw(8) << type << setw(25) << comment << setw(15) << cost << setw(9) << popular;
		Shelf_life[0].show_date();
		cout << "-";
		Shelf_life[1].show_date();
		cout << endl;
	}

	void fill_Shelf_life() // �������,��� �������� ���� ���������� ������� ������
	{
		Shelf_life[0].fill_date(2005, 2009); // ������� � ����� �����
		Shelf_life[1].fill_date(2009, 2018); // ������� �� ����� �����
	}
};

struct worker // ��������� ����������
{
	string name, surname, position, comment; // ��'�,�������,������ ���������� � ����
	string password = "1111"; // ������
	int warning = 0; // ������������ (������)
	int sales = 0; // ʳ������ ������

	bool fired() // ������� ��� ����������,�� ������� �������� �����������
	{
		if (warning >= 3)
			return true;
	}
	void show_info() // �������,��� �������� ���������� ��� ��������
	{
		cout << left << setw(8) << name << setw(10) << surname << setw(15) << position << warning << "/3" << "    " << setw(15) << sales << endl;
	}
};

struct shop // ������� ��������� �������
{
	string name, description; // ����� �� ����
	bool state; // ����,��� �������� �������� �� �������� �������
	int seller_id; // �����,��� �����'����� id ����������,���� � ������ ������ �� ���������
	int size = 1, product_size = 1;

	worker *workers = new worker[size]; // ��������� ����� ����������
	product *products = new product[product_size]; // ��������� ����� ��������

	void close(bool entered) { state = entered; } // �������,��� ������� �������
	int all_sales() //  ������� ��� ��������� ��� ������
	{
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += workers[i].sales;
		}
		return sum;
	}

	//                    \   /
	//                    -___-
	template<typename T>
	T* push_up(T *struct_arr, int &new_size) // �������,��� ������ ����� ������
	{
		T *new_struct_arr = new T[new_size+1]; // ��������� ����� ��������� �����

		for (int i = 0; i < new_size; i++)
		{
			new_struct_arr[i] = struct_arr[i];
		}

		new_size++;

		delete[]struct_arr;

		return new_struct_arr;
	}

	template<typename T2>
	T2* push_down(T2 *struct_arr, int &size, int position = size - 1) // �������,���� ������ ����� ������
	{
		T2 *new_struct_arr = new T2[size - 1];
		int count = 0;
		for (int i = 0; i < size - 1; i++)
		{
			if (count != position)
			{
				new_struct_arr[i] = struct_arr[count];
				count++;
			}
			else
				continue;
		}
		size--;
		delete[]struct_arr;
		return new_struct_arr;
	}
};

//--------------------------------------------
//----------�����------------
//--------------------------------------------

struct worker_func // ���������,��� ������ ������� ���������� ����������
{
	void show_worker(shop shop_) // �������,��� �������� ��������� ��� �����������
	{
		char entered;
		while (true)
		{
			system("cls");
			cout << "\t���������� ��� �����������\n";
			cout << "1) ���������� ���� ����������� �� �������\n";
			cout << "2) ������� ���������� �� Worker id\n";
			cout << "3) ���������� ���� ����������� �� �����\n";
			cout << "4) ���������� ���� ����������� �� �������\n";
			cout << "5) ���������� ���� ����������� �� ���-�� ������\n";
			cout << "6) ��������� �����\n";

			entered = _getch();
			_getch();

			switch (entered)
			{
			case '1': // ������� �� �������
			{
				system("cls");
				cout << "\t���������� �� �������\n";
				cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "���" << setw(10) << "�������" << setw(10) << "���������" << setw(9) << "��������" << setw(5) << "�������" << endl;
				cout << "---------------------------------" << endl;
				for (int i = 1; i < shop_.size; i++)
				{
					cout << left << setw(3) << i << setw(3) << "||";
					shop_.workers[i].show_info();
				}
				_getch();
				_getch();
				break;
			}
			case '2': // ������� �� Worker id
			{
				int id;
				while (true)
				{
					system("cls");
					cout << "\t���������� �� Worker id\n";
					cout << " ������� Worker id ";
					cin >> id;
					cin.ignore(256, '\n');
					if (id > shop_.size || id < 0) // ��������,�� ���� ����� �������
					{
						cout << " ������\n";

						_getch();
						_getch();
					}
					else // ���� ����
					{
						system("cls");
						cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "���" << setw(10) << "�������" << setw(10) << "���������" << setw(9) << "��������" << setw(5) << "�������" << endl;
						cout << "---------------------------------" << endl;
						cout << left << setw(3) << id << setw(3) << "||";
						shop_.workers[id].show_info();

						_getch();
						_getch();
						break;
					}
				}
				break;
			}
			case '3': // ���������� �� ����
			{
				char *symb_arr = new char[shop_.size]; // ��������� ������ ��� ����� ����� ��'�
				int *id_arr = new int[shop_.size]; // ����� ��� id Worker

				for (int i = 0; i < shop_.size; i++)
				{
					symb_arr[i] = shop_.workers[i].name[0]; // ���������� ����� char ������� ������� ����
					id_arr[i] = i; // ���������� ����� ��������
				}

				for (int i = 0; i < shop_.size; i++) // ���������� Bubble
				{
					for (int j = 0; j < shop_.size - 1; j++)
					{
						if (symb_arr[j] < symb_arr[j + 1])
						{
							swap(symb_arr[j], symb_arr[j + 1]);
							swap(id_arr[j], id_arr[j + 1]);
						}
					}
				}

				cout << "\t���������� �� �����\n";
				cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "���" << setw(10) << "�������" << setw(10) << "���������" << setw(9) << "��������" << setw(5) << "�������" << endl;
				cout << "---------------------------------" << endl;

				for (int i = 1; i < shop_.size; i++) // ����,���� �������� ����������
				{
					cout << left << setw(3) << id_arr[i] << setw(3) << "||";
					shop_.workers[symb_arr[i]].show_info();
				}

				_getch();
				_getch();

				delete[]symb_arr; // ��������� ������ 
				delete[]id_arr; // ��������� ������ 

				break;
			}
			case '4': // ���������� �� �������
			{

				char *symb_arr = new char[shop_.size]; // ��������� ������ ��� ����� ����� ��'�
				int *id_arr = new int[shop_.size]; // ����� ��� id Worker

				for (int i = 0; i < shop_.size; i++)
				{
					symb_arr[i] = shop_.workers[i].surname[0]; // ���������� ����� char ������� ������� ������
					id_arr[i] = i; // ���������� ����� ��������
				}

				for (int i = 0; i < shop_.size; i++) // ���������� Bubble
				{
					for (int j = 0; j < shop_.size - 1; j++)
					{
						if (symb_arr[j] < symb_arr[j + 1])
						{
							swap(symb_arr[j], symb_arr[j + 1]);
							swap(id_arr[j], id_arr[j + 1]);
						}
					}
				}

				cout << "\t���������� �� �������\n";
				cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "���" << setw(10) << "�������" << setw(10) << "���������" << setw(9) << "��������" << setw(5) << "�������" << endl;
				cout << "---------------------------------" << endl;

				for (int i = 1; i < shop_.size; i++) // ����,���� �������� ����������
				{
					cout << left << setw(3) << id_arr[i] << setw(3) << "||";
					shop_.workers[symb_arr[i]].show_info();
				}

				_getch();
				_getch();

				delete[]symb_arr; // ��������� ������ 
				delete[]id_arr; // ��������� ������ 

				break;

				_getch();
				_getch();
				break;
			}
			case '5': // ���������� �� �-�� ������
			{
				system("cls");

				cout << "\t���������� �� ���-�� ������\n";

				int *sales_arr = new int[shop_.size], *id_arr = new int[shop_.size]; // ��������� ������,��� �����'���������� �-��� ������ � ������ ����������

				for (int i = 0; i < shop_.size; i++) // ����,���� �� ������
				{
					sales_arr[i] = shop_.workers[i].sales;
					id_arr[i] = i;
				}

				for (int i = 0; i < shop_.size; i++) // Bubble ����������
				{
					for (int j = 0; j < shop_.size - 1; j++)
					{
						if (sales_arr[j] < sales_arr[j + 1])
						{
							swap(sales_arr[j], sales_arr[j + 1]);
							swap(id_arr[j], id_arr[j + 1]);
						}
					}
				}

				cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "���" << setw(10) << "�������" << setw(10) << "���������" << setw(9) << "��������" << setw(5) << "�������" << endl;
				for (int i = 1; i < shop_.size; i++) // �������� ����
				{
					shop_.workers[id_arr[i]].show_info();
				}

				delete[]sales_arr; // ��������� ������
				delete[]id_arr;	// ��������� ������

				_getch();
				_getch();

				break;
			}
			case '6': // ����������� �����
			{
				worker_menu(shop_);
				break;
			}
			}




		}
	}

	void give_warn(shop &shop_) // ������� ������ �������� ��������
	{
		system("cls");

		string name_, surname_;

		cout << "\n������ ������� ����������\n";
		cout << " ������� ��� ";
		cin >> name_;
		cin.ignore(256, '\n');
		cout << " ������� ������� ";
		cin >> surname_;
		cin.ignore(256, '\n');
		cout << endl;

		for (int i = 0; i < shop_.size; i++) //  ����,���� ���� �����������
		{
			int worker_id; // ������������� ��������
			if (shop_.workers[i].name == name_ && shop_.workers[i].surname == surname_) // ��������,�� �� ������� ���� ����������
			{
				worker_id = i;
				if (shop_.workers[i].fired() != true) // ���� � ���������� �� ���� 3 ��������
				{
					system("cls");

					cout << " � " << name_ << " " << surname_ << " ����� " << shop_.workers[i].warning << "/3" << " ���������" << endl;

					_getch();
					_getch();
				}
				else // ���� � 3 ��������
				{
					char entered;
					while (true)
					{
						system("cls");
						cout << " � ����� ���������� ��� 3 ��������������,�� ����� ������.�� ��������?\n";
						cout << " Y - ������� ������� ����������.N- �������� ��� ��� ��������\n";

						entered = _getch();
						_getch();

						switch (entered)
						{
						case 'Y':
						case 'y':
						{
							shop_.workers = shop_.push_down(shop_.workers, shop_.size, worker_id); // �������� ����� ��������,��������� ������� �������� � �����
							break;
						}
						case 'N':
						case 'n':
						{
							shop_.workers[i].warning = 0; // ��������� ������ ��������
							break;
						}
						default:
							continue;
						}
					}
				}
			}

		}

	}

	void create_worker(shop &shop_) // ������� ��������� ��������
	{
		system("cls");

		shop_.workers = shop_.push_up(shop_.workers, shop_.size); // �������� ����� ������ ��������

		cout << "\t������� ���������\n";
		cout << " ������� ��� ";
		cin >> shop_.workers[shop_.size - 1].name;
		cin.ignore(256, '\n');
		cout << " ������� ������� ���������� ";
		cin >> shop_.workers[shop_.size - 1].surname;
		cin.ignore(256, '\n');
		cout << " ������� ������ ���������� ";
		cin >> shop_.workers[shop_.size - 1].password;
		cin.ignore(256, '\n');
		cout << " ������� ��������� ����������(��������,����� ������,��������) ";
		cin >> shop_.workers[shop_.size - 1].position;
		cin.ignore(256, '\n');
		cout << " ������� ��������(�� �����������) ";
		cin >> shop_.workers[shop_.size - 1].comment;
		cin.ignore(256, '\n');

	}

	void fired_worker(shop &shop_) // ������� ��������� ��������
	{
		int entered;
		char entered_menu;
		while (true)
		{
			system("cls");
			cout << "\t������� ���������\n";
			cout << "1) ������� ����������,� �������� ������ ����� ������\n";
			cout << "2) ������� ���������� �� id\n";
			cout << "3) �������� �����\n";

			entered_menu = _getch();
			_getch();

			switch (entered_menu)
			{
			case '1': // ����� ������ ������
			{
				int min = 1000, min_id = 0; // min - �������� �-��� ������
				for (int i = 1; i < shop_.size; i++) // �������� � ����� ������� ����� ������ ������
				{
					if (shop_.workers[i].sales < min)
					{
						min = shop_.workers[i].sales;
						min_id = i;
					}
				}
				while (true) // ���� ���������
				{
					system("cls");
					cout << "��������� � ���������� ���-�� ������ - " << shop_.workers[min_id].name << " " << shop_.workers[min_id].surname << "." << shop_.workers[min_id].sales << " ������.\n";
					cout << "\t������� ���?(y/n): ";
					entered = _getch();
					_getch();
					switch (entered)
					{
					case 'Y':
					case 'y':
					{
						shop_.workers = shop_.push_down(shop_.workers, shop_.size, min_id); // ��������� ����� �� 1 �������
						cout << "\t������\n";
						_getch();
						_getch();
						return;
					}
					case 'N':
					case 'n':
					{
						return;
					}
					default:
						continue;
					}
				}
				break;
			}
			case '2': // �������� �� id
			{
				system("cls");
				int id;
				cout << "������� worker id: ";
				cin >> id;
				cin.ignore(256, '\n');
				if (id == -1) // ���� �� ����������
					break;
				else
					shop_.workers = shop_.push_down(shop_.workers, shop_.size, id);  // ��������� ��������
				break;
			}
			case '3':
			{
				worker_menu(shop_);
				break;
			}
			default:
				continue;
			}
		}
	}

}work_func; // ��������� �����,��� ������� �������

struct product_func // ���������,��� ������ ������� ��� ���������� �������
{
	//---------����� ����������----------

	void sort_by_increase(shop shop_) // ���������� �� ���������
	{
		system("cls");

		cout << "\t���������� �� �����������\n";
		cout << shop_.product_size << endl;
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "��� ������" << setw(8) << "���" << setw(25) << "��������" << setw(10) << "����" << setw(15) << "������������" << setw(20) << "���� �����������" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < shop_.product_size-1 ; i++)
		{
			cout << left << setw(3) << i+1 << setw(3) << "||";
			shop_.products[i].show_info();
		}


		_getch();
		_getch();
	}
	void sort_by_fall(shop shop_) //  ���������� �� ������� ��������
	{
		system("cls");

		cout << "\t���������� �� �����������\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "��� ������" << setw(8) << "���" << setw(25) << "��������" << setw(10) << "����" << setw(15) << "������������" << setw(20) << "���� �����������" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;
		for (int i = shop_.product_size - 1; i > 0; i--)
		{
			cout << left << setw(3) << i << setw(3) << "||";
			shop_.products[i].show_info();
		}


		_getch();
		_getch();
	}
	void sort_by_name(shop shop_) // ���������� �� ����
	{
		system("cls");

		char *symb_arr = new char[shop_.product_size]; // ��������� ������ ��� ����� ����� ��'�
		int *id_arr = new int[shop_.product_size]; // ����� ��� id Worker

		for (int i = 0; i < shop_.product_size; i++)
		{
			symb_arr[i] = shop_.products[i].name[0]; // ���������� ����� char ������� ������� ����
			id_arr[i] = i; // ���������� ����� ��������
		}

		for (int i = 0; i < shop_.product_size; i++) // ���������� Bubble
		{
			for (int j = 0; j < shop_.product_size - 1; j++)
			{
				if (symb_arr[j] < symb_arr[j + 1])
				{
					swap(symb_arr[j], symb_arr[j + 1]);
					swap(id_arr[j], id_arr[j + 1]);
				}
			}
		}

		cout << "\t���������� �� �����\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "��� ������" << setw(8) << "���" << setw(25) << "��������" << setw(10) << "����" << setw(15) << "������������" << setw(20) << "���� �����������" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 1; i < shop_.product_size; i++) // ����,���� �������� ����������
		{
			cout << left << setw(3) << id_arr[i] << setw(3) << "||";
			shop_.products[id_arr[i]].show_info();
		}

		_getch();
		_getch();

		delete[]symb_arr; // ��������� ������ 
		delete[]id_arr; // ��������� ������ 
	}
	void sort_by_type(shop shop_) // ���������� �� ����
	{
		system("cls");

		char *symb_arr = new char[shop_.product_size]; // ��������� ������ ��� ����� ����� ��'�
		int *id_arr = new int[shop_.product_size]; // ����� ��� id Worker

		for (int i = 0; i < shop_.product_size; i++)
		{
			symb_arr[i] = shop_.products[i].type[0]; // ���������� ����� char ������� ������� ����
			id_arr[i] = i; // ���������� ����� ��������
		}

		for (int i = 0; i < shop_.product_size; i++) // ���������� Bubble
		{
			for (int j = 0; j < shop_.product_size - 1; j++)
			{
				if (symb_arr[j] < symb_arr[j + 1])
				{
					swap(symb_arr[j], symb_arr[j + 1]);
					swap(id_arr[j], id_arr[j + 1]);
				}
			}
		}

		cout << "\t���������� �� ���� ������\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "��� ������" << setw(8) << "���" << setw(25) << "��������" << setw(10) << "����" << setw(15) << "������������" << setw(20) << "���� �����������" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 1; i < shop_.product_size; i++) // ����,���� �������� ����������
		{
			cout << left << setw(3) << id_arr[i] << setw(3) << "||";
			shop_.products[id_arr[i]].show_info();
		}

		_getch();
		_getch();

		delete[]symb_arr; // ��������� ������ 
		delete[]id_arr; // ��������� ������ 
	}
	void sort_by_cost(shop shop_) // ���������� �� ���
	{
		system("cls");

		int *cost_arr = new int[shop_.product_size], *id_arr = new int[shop_.product_size]; // ������ ��� ������ ���� � id ������

		for (int i = 0; i < shop_.product_size; i++)
		{
			cost_arr[i] = shop_.products[i].cost;
			id_arr[i] = i;
		}

		for (int i = 0; i < shop_.product_size; i++) // ���������� Bubble
		{
			for (int j = 0; j < shop_.product_size - 1; j++)
			{
				if (cost_arr[j] < cost_arr[j + 1])
				{
					swap(cost_arr[j], cost_arr[j + 1]);
					swap(id_arr[j], id_arr[j + 1]);
				}
			}
		}

		cout << "\t���������� �� ���� ������\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "��� ������" << setw(8) << "���" << setw(25) << "��������" << setw(10) << "����" << setw(15) << "������������" << setw(20) << "���� �����������" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 1; i < shop_.product_size; i++) // ����,���� �������� ����������
		{
			cout << left << setw(3) << id_arr[i] << setw(3) << "||";
			shop_.products[id_arr[i]].show_info();
		}

		_getch();
		_getch();

		delete[]cost_arr; // ��������� ������
		delete[]id_arr; // ��������� ������
	}
	void sort_by_popular(shop shop_) // ���������� �� �����������
	{
		system("cls");

		int *pop_arr = new int[shop_.product_size], *id_arr = new int[shop_.product_size]; // ������ ��� ������

		for (int i = 0; i < shop_.product_size; i++)
		{
			pop_arr[i] = shop_.products[i].popular;
			id_arr[i] = i;
		}

		for (int i = 0; i < shop_.product_size; i++) // ���������� Bubble
		{
			for (int j = 0; j < shop_.product_size - 1; j++)
			{
				if (pop_arr[j] < pop_arr[j + 1])
				{
					swap(pop_arr[j], pop_arr[j + 1]);
					swap(id_arr[j], id_arr[j + 1]);
				}
			}
		}

		cout << "\t���������� �� ������������\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "��� ������" << setw(8) << "���" << setw(25) << "��������" << setw(10) << "����" << setw(15) << "������������" << setw(20) << "���� �����������" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 1; i < shop_.product_size; i++) // ����,���� �������� ����������
		{
			cout << left << setw(3) << id_arr[i] << setw(3) << "||";
			shop_.products[id_arr[i]].show_info();
		}

		_getch();
		_getch();

	}

	//---------��������� ����������-------

	void add_product(shop &shop_) // ������� ���������� ������
	{
		// ����� �������,�� ����� ���������� ������ ���������� ������
		//-------------------------------------------------------------

		system("cls");

		int count = 0, cost; // ����,��� ������� ������ � ����
		string name, type, comment; // ���� ��� �����,���� � �����


		cout << "\t�������� �������(-�)\n";
		cout << " ������� ���-�� ��������� ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << "������� ��� ";
		cin >> name;
		cin.ignore(256, '\n');
		cout << "������� ��� ";
		cin >> type;
		cin.ignore(256, '\n');
		cout << "������� ���� ";
		cin >> cost;
		cin.ignore(256, '\n');
		cout << "������� �������� ";
		cin >> comment;
		cin.ignore(256, '\n');


		for (int i = 0; i < count; i++) // ���� ��������� ������
		{
			shop_.products = shop_.push_up(shop_.products, shop_.product_size);
		}
	
		for (int i = (shop_.product_size - count) - 1;i < shop_.product_size; i++) // ����,���� �������� ���������� ��� ���� ������
		{
			shop_.products[i].name = name;
			shop_.products[i].type = type;
			shop_.products[i].cost = cost;
			shop_.products[i].comment = comment;
			shop_.products[i].fill_Shelf_life();
		}

		_getch();
		_getch();

	}
	void dell_product(shop &shop_) // ������� ��������� ������
	{
		// ����� �������,�� ����� �������� ������� ������
		//-------------------------------------------------------------

		system("cls");

		int count = 0;

		cout << "\t�������� ������\n";
		cout << " ������� ���-�� ��������� ��������� ";
		cin >> count;
		cin.ignore(256, '\n');

		int *entered_arr = new int[count]; // ��������� ����� ��������� �����,���� ���� �������� ������ ������
		cout << endl;

		cout << "������� ����� ������(-��) ";

		for (int i = 0; i < count; i++) // �������� ������ ������ � ������ �� ���������
		{
			cin >> entered_arr[i];
			shop_.products = shop_.push_down(shop_.products, shop_.product_size, entered_arr[i]); // ��������� ������� ��������� ������
		}

		cout << endl;

		_getch();
		_getch();

		delete[]entered_arr; // ��������� �����
	}
	void change_name_product(shop &shop_) // ������� ���� ��'� ������
	{

		system("cls");

		int count = 0;
		string new_name;

		cout << "\t��������� ��� ��������\n";
		cout << " ������� ����� ��� ";
		cin >> new_name;
		cin.ignore(256, '\n');
		cout << " ������� ���-�� ���������� ��������� ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << endl;

		int *entered_arr = new int[count];

		cout << "������� ����� ������(-��) ";

		for (int i = 0; i < count; i++) // ����,���� ������ ������ ������ � ������ �� �����
		{
			cin >> entered_arr[i];
			cin.ignore(256, '\n');
			shop_.products[entered_arr[i]].name = new_name;
		}

		cout << endl;

		_getch();
		_getch();

		delete[]entered_arr;

	}
	void change_type_product(shop &shop_) // ������� ���� ���� ��������
	{
		system("cls");

		int count = 0;
		string new_type;

		cout << "\t��������� ���� ��������\n";
		cout << " ������� ����� ��� ";
		cin >> new_type;
		cin.ignore(256, '\n');
		cout << " ������� ���-�� ���������� ��������� ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << endl;

		int *entered_arr = new int[count];

		cout << "������� ����� ������(-��) ";

		for (int i = 0; i < count; i++) // ����,���� ������ ������ ������ � ������ �� �����
		{
			cin >> entered_arr[i];
			cin.ignore(256, '\n');
			shop_.products[entered_arr[i]].type = new_type;
		}

		cout << endl;

		_getch();
		_getch();

		delete[]entered_arr;
	}
	void change_comment_product(shop &shop_) // ������� ���� ����� ������
	{
		system("cls");

		int count = 0;
		string new_comment;

		cout << "\t��������� �������� ��������\n";
		cout << " ������� ����� �������� ";
		cin >> new_comment;
		cin.ignore(256, '\n');
		cout << " ������� ���-�� ���������� ��������� ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << endl;

		int *entered_arr = new int[count];

		cout << "������� ����� ������(-��) ";

		for (int i = 0; i < count; i++) // ����,���� ������ ������ ������ � ������ �� �����
		{
			cin >> entered_arr[i];
			cin.ignore(256, '\n');
			shop_.products[entered_arr[i]].comment = new_comment;
		}

		cout << endl;

		_getch();
		_getch();

		delete[]entered_arr;
	}
	void change_cost_product(shop &shop_) // ������� ���� ���� ������
	{
		system("cls");

		int count = 0;
		int new_cost;

		cout << "\t��������� ���� ��������\n";
		cout << " ������� ����� ���� ";
		cin >> new_cost;
		cin.ignore(256, '\n');
		cout << " ������� ���-�� ���������� ��������� ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << endl;

		int *entered_arr = new int[count];

		cout << "������� ����� ������(-��) ";

		for (int i = 0; i < count; i++) // ����,���� ������ ������ ������ � ������ �� �����
		{
			cin >> entered_arr[i];
			cin.ignore(256, '\n');
			shop_.products[entered_arr[i]].cost = new_cost;
		}

		cout << endl;

		_getch();
		_getch();

		delete[]entered_arr;
	}

	//---------������� ��� �������--------

	void buy_product(shop &shop_, float &money) // �������,��� ������� ������
	{
		int count, prod_count = 0; // ����� ��� �-��� ������,� �������� �-��� ������
		int *id_prod = new int[shop_.product_size]; // �����,�� ���������� ������,�� ������� ��������
		float cost = 0; // �����,������� ��� ��������,�� ��������� ������
		string prod_name; // ����� ������,����� �� ������ ������

		while (true)
		{
			system("cls");
			cout << "\t������� ������\n";
			cout << "�� ����� " << money << "$\n";
			cout << " ������� ��� ������ ";
			cin >> prod_name;
			cin.ignore(256, '\n');

			for (int i = 1; i < shop_.product_size; i++) // ������,������ �� ����� � ������ ������
			{
				if (shop_.products[i].name == prod_name) // ���� ����� �,�������� ���� �-���
				{
					cost = shop_.products[i].cost;
					prod_count++;
					id_prod[prod_count] = i;
				}
			}

			cout << " �� ������ ������ � ������ " << prod_name << " ���� " << prod_count << " ��.\n";
			cout << " ������� ���-�� ������ ";
			cin >> count;
			cin.ignore(256, '\n');

			if (count > prod_count || count < 0)
			{
				cout << " ������,�� ����� ������������ ���-��\n";
				Sleep(2000);
				continue;
			}
			else
			{
				if (money > cost*count) // ��������,�� ��������� ������
				{
					shop_.workers[shop_.seller_id].sales++; // �������� �-��� ������ ��������
					for (int i = 0; i < count; i++) // ����,���� ������� �����
					{
						shop_.products = shop_.push_down(shop_.products, shop_.product_size, id_prod[i]);
					}
					cout << "\t������� �� �������,��������� ���\n";
					money -= cost * count;
					buyer_menu(shop_, money);
				}
				else {
					cout << " � ��� ������������ �����,�� ������� " << cost * count - money << "$\n";
					Sleep(3000);
					continue;
				}
			}

			delete[]id_prod; // ��������� �����

			break;
		}
	}

}prod_func; // ��������� �����,��� ������� �������

struct file_func // ���������,��� ������ ������� ��� ������ � �������
{
	ofstream fout; // ����� ��� ������ � ����
	ifstream fin; // ����� ��� ���������� �����

				  //------------����� � ����-------------
	void write_stats(string info_arr[])	// ������� ��� ������ ���������� � ����
	{
		string file_name = "shop_stats.txt"; // ����� �����

		fout.open(file_name, ios_base::out | ios_base::ate); // ³������ ���� ��� ������ � ����� �����

		for (int i = 0; i <5; i++)
		{
			fout << "\t" << info_arr[i] << endl;
		}

		fout.close();
	}

	//------------���������� �����---------

}file_; // ��������� ����� ��� 
		
		// --------------------------------------------
		//----------����------------
		//--------------------------------------------

void info_about_product_menu(shop shop_) // ���� ���������� ��� �����
{
	char entered;

	while (true)
	{
		system("cls");

		cout << "\t���������� ��� ��������\n";
		cout << "1) ���������� �� ������� �����������\n";
		cout << "2) ���������� �� ������� ��������\n";
		cout << "3) ���������� �������� ������\n";
		cout << "4) ���������� �� ���� ������\n";
		cout << "5) ���������� �� ���� ������\n";
		cout << "6) ���������� �� ������������ ������\n";
		cout << "7) ��������� �����\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			prod_func.sort_by_increase(shop_);
			break;
		}
		case '2':
		{
			prod_func.sort_by_fall(shop_);
			break;
		}
		case '3':
		{
			prod_func.sort_by_name(shop_);
			break;
		}
		case '4':
		{
			prod_func.sort_by_type(shop_);
			break;
		}
		case '5':
		{
			prod_func.sort_by_cost(shop_);
			break;
		}
		case '6':
		{
			prod_func.sort_by_popular(shop_);
			break;
		}
		case '7':
		{
			product_menu(shop_);
			break;
		}
		default:
			continue;
		}
	}
}

void change_product_menu(shop &shop_) // ����,��� ���� ������
{
	char entered;
	//							\   /
	while (true) // ³���� ���� 0___0 
	{
		system("cls");
		cout << "\t��������� ������\n";
		cout << "1) �������� �����\n";
		cout << "2) ������� �����\n";
		cout << "3) �������� ��� ������\n";
		cout << "4) �������� ��� ������\n";
		cout << "5) �������� �������� ������\n";
		cout << "6) �������� ���� ������\n";
		cout << "7) ��������� �����\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			prod_func.add_product(shop_);
			break;
		}
		case '2':
		{
			prod_func.dell_product(shop_);
			break;
		}
		case '3':
		{
			prod_func.change_name_product(shop_);
			break;
		}
		case '4':
		{
			prod_func.change_type_product(shop_);
			break;
		}
		case '5':
		{
			prod_func.change_comment_product(shop_);
			break;
		}
		case '6':
		{
			prod_func.change_cost_product(shop_);
			break;
		}
		case '7':
		{
			product_menu(shop_);
			break;
		}
		default:
			continue;
		}
	}
}

void product_menu(shop &shop_) // ���� ���������� ������
{
	char entered;


	while (true)
	{
		system("cls");

		cout << "\t���� ���������� �������\n";
		cout << "1) ���������� ��� ������\n";
		cout << "2) ��������� ������\n";
		cout << "3) ��������� �����\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			info_about_product_menu(shop_);
			break;
		}
		case '2':
		{
			change_product_menu(shop_);
			break;
		}
		case '3':
		{
			leader_menu(shop_);
			break;
		}
		default:
			continue;
		}
	}
}

//-----------------------------------------------

void change_shop(shop &shop_) // ���� ��������� ��������
{
	char entered;

	while (true)
	{
		system("cls");

		cout << "\t��������� ��������\n";
		cout << "1) �������� ���\n";
		cout << "2) �������� ��������\n";
		if (shop_.state == true)
			cout << "3) ������� �������\n";
		else
			cout << "3) ������� �������\n";
		cout << "4) ��������� �����\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			system("cls");
			cout << "\t��������� ��� ��������\n";
			cout << " ������� ����� ��� ";
			cin >> shop_.name;
			cin.ignore(256, '\n');
			break;
		}
		case '2':
		{
			system("cls");
			cout << "\t��������� �������� ��������\n";
			cout << " ������� ����� �������� ";
			cin >> shop_.description;
			cin.ignore(256, '\n');
			break;
		}
		case '3':
		{
			if (shop_.state == true)
				shop_.state = false;
			else
				shop_.state = true;
			break;
		}
		case '4':
		{
			leader_menu(shop_);
			break;
		}
		default:
			continue;
		}
	}
}

//-----------------------------------------------

void buyer_menu(shop &shop_, float &money) // ���� ��� �������
{
	char entered;

	while (true)
	{
		system("cls");

		cout << "\t������� " << shop_.name << " ��� ��� ��������������\n";
		cout << "\t�� ����� " << money << "$\n";
		cout << "1) ���������� ���������� �������\n";
		cout << "2) ������ �����\n";
		cout << "3) ���� � ��������\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			prod_func.sort_by_increase(shop_);
			break;
		}
		case '2':
		{
			prod_func.buy_product(shop_, money);
			break;
		}
		case '3':
		{
			sign_in(shop_);
			break;
		}
		default:
			continue;
		}
	}
}

//-----------------------------------------------

void worker_menu(shop &shop_) // ���� ��������� �������������
{
	char entered;
	while (true)
	{
		system("cls");
		cout << "\t���� ���������� �����������\n";
		cout << "1) ���������� ��� ���� �����������\n";
		cout << "2) ������ ������� ����������\n";
		cout << "3) ������� ����������\n";
		cout << "4) ������� ����������\n";
		cout << "5) ����� � ������� ����\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			work_func.show_worker(shop_);
			break;
		}
		case '2':
		{
			work_func.give_warn(shop_);
			break;
		}
		case '3':
		{
			work_func.create_worker(shop_);
			break;
		}
		case '4':
		{
			work_func.fired_worker(shop_);
			break;
		}
		case '5':
		{
			leader_menu(shop_);
			break;
		}
		default:
			continue;
		}
	}
}

void menu_for_worker(shop &shop_) // ���� ��� ����������
{
	char entered;

	while (true)
	{
		cout << "\t������� " << shop_.name << endl;
		cout << "1) ���������� �������\n";
		cout << "2) ���������� ������������\n";
		cout << "3) ���������� ��������\n";
		cout << "4) ������� ������������\n";
		cout << "5) �����\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			product_menu(shop_);
			break;
		}
		case '2':
		{
			if (shop_.workers[shop_.seller_id].position != "Director") // ��������,�� � � ���������� ������
			{
				cout << "� ��� ��������� ����\n";
				Sleep(2000);
			}
			else
			{
				worker_menu(shop_);
			}
			break;
		}
		case '3':
		{
			if (shop_.workers[shop_.seller_id].position != "Glava otdela")// ��������,�� � � ���������� ������
			{
				cout << "� ��� ��������� ����\n";
				Sleep(2000);
			}
			else
			{
				stats(shop_);
			}
			break;
		}
		case '4':
		{
			shop_.seller_id = NULL; // ��� ���� ������ ���������
			sign_in(shop_);
			break;
		}
		case '5':
		{
			system("exit");
			break;
		}
		default:
			continue;
		}
	}
}

void leader_menu(shop &shop_) // ������� ����
{

	char entered;
	while (true)
	{
		system("cls");
		cout << "\t������� " << shop_.name << endl;
		cout << "1) ���������� ������������\n";
		cout << "2) ���������� �������\n";
		cout << "3) ����������\n";
		cout << "4) ���������� ���������\n";
		cout << "5) ������� ������������\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			worker_menu(shop_);
			break;
		}
		case '2':
		{
			product_menu(shop_);
			break;
		}
		case '3':
		{
			stats(shop_);
			break;
		}
		case '4':
		{
			change_shop(shop_);
			break;
		}
		case '5':
		{
			sign_in(shop_);
			break;
		}
		default:
			continue;
		}
	}
}

//--------------------------------------------
//----------���� �������--------------
//--------------------------------------------


void stats(shop shop_) // ���������� ��������
{

	//---------���� � ����----------

	string arr[6];

	arr[0] = "���������� �������� ";
	arr[0] += shop_.name;
	arr[1] = "����� ���������� ";
	arr[1] += shop_.size;
	arr[2] = "����� ��������� ";
	arr[2] += shop_.product_size;
	arr[3] = "����� ������ ";
	arr[3] += shop_.all_sales();
	arr[4] = "�������� - ";
	arr[4] += shop_.description;
	arr[5] = "----------------------";

	file_.write_stats(arr); // ��������� ������� ������ � ����

							//---------���� � �������---------

	system("cls");

	cout << "\t����������\n";
	cout << " �������� �������� " << shop_.name << endl;
	cout << " ����� ���������� " << shop_.size - 1 << endl;
	cout << " ����� ��������� " << shop_.product_size - 1 << endl;
	cout << " ����� ������ " << shop_.all_sales() << endl;
	cout << " �������� �������� - " << shop_.description << endl;

	_getch();
	_getch();


}

void sign_in(shop &shop_) // ������� ����� � �������
{
	string in_name, in_password;
	while (true)
	{
		system("cls");

		cout << "\t���� � ������� �������� " << shop_.name << endl;
		cout << ">> ������� �����(���): ";
		cin >> in_name;
		cin.ignore(256, '\n');
		cout << ">> ������� ������: ";
		cin >> in_password;
		cin.ignore(256, '\n');

		if (in_name == "admin" && in_password == "admin") // ���� �� ����� admin admin,�� ������� ����
			leader_menu(shop_);

		if (shop_.state != true) // ��������,�� ������� ��������
		{
			system("cls");
			cout << "\t������� ������\n";
			Sleep(2000);
		}
		else if (in_name == "buy" && in_password == "buy") // ������� ��� �������
		{
			float money = 200 + rand() % 4800; // �������� �����

			if (shop_.seller_id == NULL) // ���� � ��� ���,���� ��������� �� �����
				shop_.seller_id = 1 + rand() % shop_.size; // �������� ����������� ��������
			buyer_menu(shop_, money);
		}
		else // ���� �� �� ��� � �� ��������
		{
			for (int i = 0; i < shop_.size; i++) // �������� ������
			{

				if (shop_.workers[i].name == in_name) // ���� ���� ������
				{
					if (shop_.workers[i].password == in_password) // ���� ������ ������
					{
						system("cls");
						shop_.seller_id = i; // �� �� ������ �������� ��� �������

						cout << "\t������ ���� " << shop_.workers[shop_.seller_id].name << endl;
						Sleep(2000);
						menu_for_worker(shop_);
					}
					else // ���� ������ ������������
					{
						cout << endl << "�������� ������\n";
						Sleep(2000);
					}

				}
				else if (i == shop_.size && shop_.workers[i].name != in_name) // ���� ���� ������������
				{
					cout << endl << "�������� �����\n";
					Sleep(2000);
				}
			}
		}
	}
}

//--------------------------------------------
//----------int main()--------------
//--------------------------------------------

int main()
{
	shop Apple; // ��������� �������

	setlocale(LC_ALL, "Russian");
	srand(time(NULL));


	cout << "������� �������� ��������: ";
	cin >> Apple.name; // ������� ���� �����

	sign_in(Apple); // ��������� ������� �����
}

