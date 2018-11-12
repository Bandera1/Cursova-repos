#include "Header.h"

using namespace std;

const int NotUsed = system("color 02"); // Глобальна змінна для зміни кольору

// Курсова - магазин

//--------------------------------------------
//-------Прототипи функцій і структур------------
//--------------------------------------------

struct shop;
void product_menu(shop&);
void leader_menu(shop&);
void worker_menu(shop&);
void stats(shop);
void sign_in(shop&);
void buyer_menu(shop&, float&);

//--------------------------------------------
//-------Створення структур------------
//--------------------------------------------

struct date // Структура для дати
{
	int month, day;
	float year;
	void fill_date(int min, int max) // Функція автоматичної заповнення дати
	{
		year = min + (rand() % (max - min));
		month = 1 + rand() % 11;
		day = 1 + rand() % 30;

	}

	void show_date() // Функція,яка,от зараз уважно.ПОКАЗУЄ ДАТУ -____-
	{
		cout << year << "/" << month << "/" << day;
	}

};

struct product // Структура продукта
{
	string name, type, comment; // Ім'я,тип і опис товара
	float cost; // Ціна
	int popular = 0; // Популярність данного товара
	date Shelf_life[2]; // Дата пригодності

	void show_info() // Показує інформацію про данний продукт
	{
		cout << setw(15) << name << setw(8) << type << setw(25) << comment << setw(15) << cost << setw(9) << popular;
		Shelf_life[0].show_date();
		cout << "-";
		Shelf_life[1].show_date();
		cout << endl;
	}

	void fill_Shelf_life() // Функція,яка заповнює дату пригодності данного товара
	{
		Shelf_life[0].fill_date(2005, 2009); // Вказуємо з якого числа
		Shelf_life[1].fill_date(2009, 2018); // Вказуємо до якого числа
	}
};

struct worker // Структура працівника
{
	string name, surname, position, comment; // Ім'я,прізвище,посада працівника і опис
	string password = "1111"; // Пароль
	int warning = 0; // Попередження (догани)
	int sales = 0; // Кількість продаж

	bool fired() // Функція для визначення,чи потрібно звільняти співробітника
	{
		if (warning >= 3)
			return true;
	}
	void show_info() // Функція,яка виводить інформацію про робітника
	{
		cout << left << setw(8) << name << setw(10) << surname << setw(15) << position << warning << "/3" << "    " << setw(15) << sales << endl;
	}
};

struct shop // Головна структура магазин
{
	string name, description; // Назва та опис
	bool state; // Буль,щоб дізнатись відкритий чи закритий магазин
	int seller_id = 0; // Змінна,яка запам'ятовує id працівника,який в данний момент на чергуванні
	int size = 1, product_size = 1;

	worker *workers = new worker[size]; // Динамічний масив працівників
	product *products = new product[product_size]; // Динамічний масив продуктів

	void close(bool entered) { state = entered; } // Функція,яка закриває магазин
	int all_sales() //  Функція для підрахунку усіх продаж
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
	T* push_up(T *struct_arr, int &new_size) // Функція,яка збільшує розмір масива
	{
		T *new_struct_arr = new T[new_size+1]; // Створюємо новий динамічний масив

		for (int i = 0; i < new_size; i++)
		{
			new_struct_arr[i] = struct_arr[i];
		}

		new_size++;

		delete[]struct_arr;

		return new_struct_arr;
	}

	template<typename T2>
	T2* push_down(T2 *struct_arr, int &size, int position = size - 1) // Функція,якак зменшує розмір масива
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
//----------Логіка------------
//--------------------------------------------

struct worker_func // Структура,яка зберігає фукнції управлінням робітниками
{
	void show_worker(shop shop_) // Функція,яка виводить інформацю про співробітника
	{
		char entered;
		while (true)
		{
			system("cls");
			cout << "\tИнформация про сотрудников\n";
			cout << "1) Сортировка всех сотрудников по порядку\n";
			cout << "2) Вывести сотрудника по Worker id\n";
			cout << "3) Сортировка всех сотрудников по имени\n";
			cout << "4) Сортировка всех сотрудников по фамилии\n";
			cout << "5) Сортировка всех сотрудников по кол-во продаж\n";
			cout << "6) Вернуться назад\n";

			entered = _getch();
			_getch();

			switch (entered)
			{
			case '1': // Вивести по порядку
			{
				system("cls");
				cout << "\tИнформация по порядку\n";
				cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "Имя" << setw(10) << "Фамилия" << setw(10) << "Должность" << setw(9) << "Выговоры" << setw(5) << "Продажи" << endl;
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
			case '2': // Вивести по Worker id
			{
				int id;
				while (true)
				{
					system("cls");
					cout << "\tИнформация по Worker id\n";
					cout << " Введите Worker id ";
					cin >> id;
					cin.ignore(256, '\n');
					if (id > shop_.size || id < 0) // Перевірка,чи існує такий робітник
					{
						cout << " Ошибка\n";

						_getch();
						_getch();
					}
					else // Якщо існує
					{
						system("cls");
						cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "Имя" << setw(10) << "Фамилия" << setw(10) << "Должность" << setw(9) << "Выговоры" << setw(5) << "Продажи" << endl;
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
			case '3': // Сортування по імені
			{
				char *symb_arr = new char[shop_.size]; // Створюємо масиви для першої літери ім'я
				int *id_arr = new int[shop_.size]; // Масив для id Worker

				for (int i = 0; i < shop_.size; i++)
				{
					symb_arr[i] = shop_.workers[i].name[0]; // Заповнюємо масив char першими буквами імен
					id_arr[i] = i; // Присвоюємо номер робітника
				}

				for (int i = 0; i < shop_.size; i++) // Сортування Bubble
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

				cout << "\tСортировка по имени\n";
				cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "Имя" << setw(10) << "Фамилия" << setw(10) << "Должность" << setw(9) << "Выговоры" << setw(5) << "Продажи" << endl;
				cout << "---------------------------------" << endl;

				for (int i = 1; i < shop_.size; i++) // Цикл,який виводить інформацію
				{
					cout << left << setw(3) << id_arr[i] << setw(3) << "||";
					shop_.workers[symb_arr[i]].show_info();
				}

				_getch();
				_getch();

				delete[]symb_arr; // Видаляємо масиви 
				delete[]id_arr; // Видаляємо масиви 

				break;
			}
			case '4': // Сортування по прізвищу
			{

				char *symb_arr = new char[shop_.size]; // Створюємо масиви для першої літери ім'я
				int *id_arr = new int[shop_.size]; // Масив для id Worker

				for (int i = 0; i < shop_.size; i++)
				{
					symb_arr[i] = shop_.workers[i].surname[0]; // Заповнюємо масив char першими буквами прізвищ
					id_arr[i] = i; // Присвоюємо номер робітника
				}

				for (int i = 0; i < shop_.size; i++) // Сортування Bubble
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

				cout << "\tСортировка по фамилии\n";
				cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "Имя" << setw(10) << "Фамилия" << setw(10) << "Должность" << setw(9) << "Выговоры" << setw(5) << "Продажи" << endl;
				cout << "---------------------------------" << endl;

				for (int i = 1; i < shop_.size; i++) // Цикл,який виводить інформацію
				{
					cout << left << setw(3) << id_arr[i] << setw(3) << "||";
					shop_.workers[symb_arr[i]].show_info();
				}

				_getch();
				_getch();

				delete[]symb_arr; // Видаляємо масиви 
				delete[]id_arr; // Видаляємо масиви 

				break;

				_getch();
				_getch();
				break;
			}
			case '5': // Сортування по к-сті продаж
			{
				system("cls");

				cout << "\tСортировка по кол-во продаж\n";

				int *sales_arr = new int[shop_.size], *id_arr = new int[shop_.size]; // Створюємо масиви,для запам'ятовування к-сть продаж і номерів працівників

				for (int i = 0; i < shop_.size; i++) // Цикл,який це робить
				{
					sales_arr[i] = shop_.workers[i].sales;
					id_arr[i] = i;
				}

				for (int i = 0; i < shop_.size; i++) // Bubble сортування
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

				cout << left << setw(3) << "#" << setw(3) << "||" << setw(8) << "Имя" << setw(10) << "Фамилия" << setw(10) << "Должность" << setw(9) << "Выговоры" << setw(5) << "Продажи" << endl;
				for (int i = 1; i < shop_.size; i++) // Виводимо інфу
				{
					shop_.workers[id_arr[i]].show_info();
				}

				delete[]sales_arr; // Видаляємо масиви
				delete[]id_arr;	// Видаляємо масиви

				_getch();
				_getch();

				break;
			}
			case '6': // Повернутися назад
			{
				worker_menu(shop_);
				break;
			}
			}




		}
	}

	void give_warn(shop &shop_) // Функція видачі виговора робітнику
	{
		system("cls");

		string name_, surname_;

		cout << "\nВыдать выговор сотруднику\n";
		cout << " Введите имя ";
		cin >> name_;
		cin.ignore(256, '\n');
		cout << " Введите фамилию ";
		cin >> surname_;
		cin.ignore(256, '\n');
		cout << endl;

		for (int i = 0; i < shop_.size; i++) //  Цикл,який шукає співробітника
		{
			int worker_id; // Ідентифікатор робітника
			if (shop_.workers[i].name == name_ && shop_.workers[i].surname == surname_) // Перевіряє,чи всі введенні данні співпадають
			{
				worker_id = i;
				if (shop_.workers[i].fired() != true) // Якщо у працівника ще немає 3 виговора
				{
					system("cls");

					shop_.workers[i].warning++;
					cout << " У " << name_ << " " << surname_ << " всего " << shop_.workers[i].warning << "/3" << " выговоров" << endl;

					_getch();
					_getch();
				}
				else // Якщо є 3 виговора
				{
					char entered;
					while (true)
					{
						system("cls");
						cout << " У этого сотрудника уже 3 предупреждения,он будет уволен.Вы согласны?\n";
						cout << " Y - уволить данного сотрудника.N- обнулить ему все выговоры\n";

						entered = _getch();
						_getch();

						switch (entered)
						{
						case 'Y':
						case 'y':
						{
							shop_.workers = shop_.push_down(shop_.workers, shop_.size, worker_id); // Зменшуємо масив робітників,видаливши данного робітника з нього
							break;
						}
						case 'N':
						case 'n':
						{
							shop_.workers[i].warning = 0; // Обнулюємо список виговорів
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

	void create_worker(shop &shop_) // Функція створення робітника
	{
		system("cls");

		shop_.workers = shop_.push_up(shop_.workers, shop_.size); // Збільшуємо розмір масива робітників

		cout << "\tСоздать работника\n";
		cout << " Введите имя ";
		cin >> shop_.workers[shop_.size - 1].name;
		cin.ignore(256, '\n');
		cout << " Введите фамилию сотрудника ";
		cin >> shop_.workers[shop_.size - 1].surname;
		cin.ignore(256, '\n');
		cout << " Введите пароль сотрудника ";
		cin >> shop_.workers[shop_.size - 1].password;
		cin.ignore(256, '\n');
		cout << " Введите должность сотрудника(Директор,глава отдела,продавец) ";
		cin >> shop_.workers[shop_.size - 1].position;
		cin.ignore(256, '\n');
		cout << " Введите описание(не обязательно) ";
		cin >> shop_.workers[shop_.size - 1].comment;
		cin.ignore(256, '\n');

	}

	void fired_worker(shop &shop_) // Функція звільнення робітника
	{
		int entered;
		char entered_menu;
		while (true)
		{
			system("cls");
			cout << "\tУволить работника\n";
			cout << "1) Уволить сотрудника,у которого меньше всего продаж\n";
			cout << "2) Уволить сотрудника по id\n";
			cout << "3) Вернутся назад\n";

			entered_menu = _getch();
			_getch();

			switch (entered_menu)
			{
			case '1': // Менше всього продаж
			{
				int min = 1000, min_id = 0; // min - мінімальна к-сть продаж
				for (int i = 1; i < shop_.size; i++) // дізнаємося у якого прдавця менше всього продаж
				{
					if (shop_.workers[i].sales < min)
					{
						min = shop_.workers[i].sales;
						min_id = i;
					}
				}
				while (true) // Меню видалення
				{
					system("cls");
					cout << "Сотрудник с наименьшим кол-во продаж - " << shop_.workers[min_id].name << " " << shop_.workers[min_id].surname << "." << shop_.workers[min_id].sales << " продаж.\n";
					cout << "\tУволить его?(y/n): ";
					entered = _getch();
					_getch();
					switch (entered)
					{
					case 'Y':
					case 'y':
					{
						shop_.workers = shop_.push_down(shop_.workers, shop_.size, min_id); // Зменшуэмо масив на 1 елемент
						cout << "\tУволен\n";
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
			case '2': // Видалити по id
			{
				system("cls");
				int id;
				cout << "Введите worker id: ";
				cin >> id;

				if (id < 0 || id > shop_.size)
				{
					cout << " Сотрудник с таким worker id.Не найден\n";
					_getch();
					_getch();
					break;
				}

				cin.ignore(256, '\n');
				if (id == -1) // Якщо ми передумали
					break;
				else
					shop_.workers = shop_.push_down(shop_.workers, shop_.size, id);  // Звільнюємо робітника
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

}work_func; // глобальна змінна,для виклику функцій

struct product_func // Структура,яка зберігає функції для управлінням товаром
{
	//---------Показ інформації----------

	void sort_by_increase(shop shop_) // Сортування по зростанню
	{
		system("cls");

		cout << "\tСортировка по возростанию\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "Имя товара" << setw(8) << "Тип" << setw(25) << "Описание" << setw(10) << "Цена" << setw(15) << "Популярность" << setw(20) << "Срок пригодности" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < shop_.product_size-1 ; i++)
		{
			cout << left << setw(3) << i+1 << setw(3) << "||";
			shop_.products[i].show_info();
		}


		_getch();
		_getch();
	}
	void sort_by_fall(shop shop_) //  Сортування по порядку спадання
	{
		system("cls");

		cout << "\tСортировка по возростанию\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "Имя товара" << setw(8) << "Тип" << setw(25) << "Описание" << setw(10) << "Цена" << setw(15) << "Популярность" << setw(20) << "Срок пригодности" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;
		for (int i = shop_.product_size - 1; i > 0; i--)
		{
			cout << left << setw(3) << i << setw(3) << "||";
			shop_.products[i].show_info();
		}


		_getch();
		_getch();
	}
	void sort_by_name(shop shop_) // Сортування по імені
	{
		system("cls");

		char *symb_arr = new char[shop_.product_size]; // Створюємо масиви для першої літери ім'я
		int *id_arr = new int[shop_.product_size]; // Масив для id Worker

		for (int i = 0; i < shop_.product_size; i++)
		{
			symb_arr[i] = shop_.products[i].name[0]; // Заповнюємо масив char першими буквами імен
			id_arr[i] = i; // Присвоюємо номер робітника
		}

		for (int i = 0; i < shop_.product_size; i++) // Сортування Bubble
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

		cout << "\tСортировка по имени\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "Имя товара" << setw(8) << "Тип" << setw(25) << "Описание" << setw(10) << "Цена" << setw(15) << "Популярность" << setw(20) << "Срок пригодности" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 1; i < shop_.product_size; i++) // Цикл,який виводить інформацію
		{
			cout << left << setw(3) << id_arr[i] << setw(3) << "||";
			shop_.products[id_arr[i]].show_info();
		}

		_getch();
		_getch();

		delete[]symb_arr; // Видаляємо масиви 
		delete[]id_arr; // Видаляємо масиви 
	}
	void sort_by_type(shop shop_) // Сортування по типу
	{
		system("cls");

		char *symb_arr = new char[shop_.product_size]; // Створюємо масиви для першої літери ім'я
		int *id_arr = new int[shop_.product_size]; // Масив для id Worker

		for (int i = 0; i < shop_.product_size; i++)
		{
			symb_arr[i] = shop_.products[i].type[0]; // Заповнюємо масив char першими буквами імен
			id_arr[i] = i; // Присвоюємо номер робітника
		}

		for (int i = 0; i < shop_.product_size; i++) // Сортування Bubble
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

		cout << "\tСортировка по типу товара\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "Имя товара" << setw(8) << "Тип" << setw(25) << "Описание" << setw(10) << "Цена" << setw(15) << "Популярность" << setw(20) << "Срок пригодности" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 1; i < shop_.product_size; i++) // Цикл,який виводить інформацію
		{
			cout << left << setw(3) << id_arr[i] << setw(3) << "||";
			shop_.products[id_arr[i]].show_info();
		}

		_getch();
		_getch();

		delete[]symb_arr; // Видаляємо масиви 
		delete[]id_arr; // Видаляємо масиви 
	}
	void sort_by_cost(shop shop_) // Сортування по ціні
	{
		system("cls");

		int *cost_arr = new int[shop_.product_size], *id_arr = new int[shop_.product_size]; // Масиви для запису ціни і id товарів

		for (int i = 0; i < shop_.product_size; i++)
		{
			cost_arr[i] = shop_.products[i].cost;
			id_arr[i] = i;
		}

		for (int i = 0; i < shop_.product_size; i++) // Сортування Bubble
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

		cout << "\tСортировка по типу товара\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "Имя товара" << setw(8) << "Тип" << setw(25) << "Описание" << setw(10) << "Цена" << setw(15) << "Популярность" << setw(20) << "Срок пригодности" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 1; i < shop_.product_size; i++) // Цикл,який виводить інформацію
		{
			cout << left << setw(3) << id_arr[i] << setw(3) << "||";
			shop_.products[id_arr[i]].show_info();
		}

		_getch();
		_getch();

		delete[]cost_arr; // Видаляємо масиви
		delete[]id_arr; // Видаляємо масиви
	}
	void sort_by_popular(shop shop_) // Сортування по популярності
	{
		system("cls");

		int *pop_arr = new int[shop_.product_size], *id_arr = new int[shop_.product_size]; // Масиви для данних

		for (int i = 0; i < shop_.product_size; i++)
		{
			pop_arr[i] = shop_.products[i].popular;
			id_arr[i] = i;
		}

		for (int i = 0; i < shop_.product_size; i++) // Сортування Bubble
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

		cout << "\tСортировка по популярности\n";
		cout << left << setw(3) << "#" << setw(3) << "||" << setw(15) << "Имя товара" << setw(8) << "Тип" << setw(25) << "Описание" << setw(10) << "Цена" << setw(15) << "Популярность" << setw(20) << "Срок пригодности" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;

		for (int i = 1; i < shop_.product_size; i++) // Цикл,який виводить інформацію
		{
			cout << left << setw(3) << id_arr[i] << setw(3) << "||";
			shop_.products[id_arr[i]].show_info();
		}

		_getch();
		_getch();

	}

	//---------Керування продуктами-------

	void add_product(shop &shop_) // Функція добавляння товару
	{
		// Данна функція,має змогу створювати багато одинакових товарів
		//-------------------------------------------------------------

		system("cls");

		int count = 0, cost; // Змінні,для кількості товарів і ціни
		string name, type, comment; // Змінні для назви,типу і опису


		cout << "\tДобавить продукт(-ы)\n";
		cout << " Введите кол-во продуктов ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << "Введите имя ";
		cin >> name;
		cin.ignore(256, '\n');
		cout << "Введите тип ";
		cin >> type;
		cin.ignore(256, '\n');
		cout << "Введите цену ";
		cin >> cost;
		cin.ignore(256, '\n');
		cout << "Введите описание ";
		cin >> comment;
		cin.ignore(256, '\n');


		for (int i = 0; i < count; i++) // Цикл створення товарів
		{
			shop_.products = shop_.push_up(shop_.products, shop_.product_size);
		}
	
		for (int i = (shop_.product_size - count) - 1;i < shop_.product_size; i++) // Цикл,який заповнює інформацію про данні товари
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
	void dell_product(shop &shop_) // Функція видалення товару
	{
		// Данна функція,має змогу видаляти декілька товарів
		//-------------------------------------------------------------

		system("cls");

		int count = 0;

		cout << "\tУдаление товара\n";
		cout << " Введите кол-во удаляемых продуктов ";
		cin >> count;
		cin.ignore(256, '\n');

		if (count < shop_.product_size || count > shop_.product_size)
		{
			cout << " На складе есть только " << shop_.product_size << " товаров\n";
			_getch();
			_getch();
			return;
		}
	

		int *entered_arr = new int[count]; // Створюємо новий динамічний масив,який буде зберігати номера товарів
		cout << endl;

		cout << "Введите номер товара(-ов) ";

		for (int i = 0; i < count; i++) // Записуємо номера товарів і відразу їх видаляємо
		{
			cin >> entered_arr[i];
			cin.ignore(256, '\n');
			if (entered_arr[i] < 0 || entered_arr[i] > shop_.product_size)
			{
				cout << " Товара под номером " << entered_arr[i] << " не существует\n";
				_getch();
				_getch();
				break;
			}
			shop_.products = shop_.push_down(shop_.products, shop_.product_size, entered_arr[i]); // Викликаємо функція видалення товару
		}

		cout << endl;

		_getch();
		_getch();

		delete[]entered_arr; // Видаляємо масив
	}
	void change_name_product(shop &shop_) // Функція зміни ім'я товару
	{

		system("cls");

		int count = 0;
		string new_name;

		cout << "\tИзменение имя продукта\n";
		cout << " Введите новое имя ";
		cin >> new_name;
		cin.ignore(256, '\n');
		cout << " Введите кол-во изменяемих продуктов ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << endl;

		int *entered_arr = new int[count];

		cout << "Введите номер товара(-ов) ";

		for (int i = 0; i < count; i++) // Цикл,який записує номера товарів і відразу їх змінює
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
	void change_type_product(shop &shop_) // Функція зміни типу продукту
	{
		system("cls");

		int count = 0;
		string new_type;

		cout << "\tИзменение типа продукта\n";
		cout << " Введите новый тип ";
		cin >> new_type;
		cin.ignore(256, '\n');
		cout << " Введите кол-во изменяемих продуктов ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << endl;

		int *entered_arr = new int[count];

		cout << "Введите номер товара(-ов) ";

		for (int i = 0; i < count; i++) // Цикл,який записує номера товарів і відразу їх змінює
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
	void change_comment_product(shop &shop_) // Функція зміни опису товару
	{
		system("cls");

		int count = 0;
		string new_comment;

		cout << "\tИзменение описания продукта\n";
		cout << " Введите новое описание ";
		cin >> new_comment;
		cin.ignore(256, '\n');
		cout << " Введите кол-во изменяемих продуктов ";
		cin >> count;
		cin.ignore(256, '\n');

		cout << endl;

		int *entered_arr = new int[count];

		cout << "Введите номер товара(-ов) ";

		for (int i = 0; i < count; i++) // Цикл,який записує номера товарів і відразу їх змінює
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
	void change_cost_product(shop &shop_) // Функція зміни ціни товару
	{
		system("cls");

		int count = 0;
		int new_cost;

		cout << "\tИзменение цены продукта\n";
		cout << " Введите новою цену ";
		cin >> new_cost;
		cin.ignore(256, '\n');
		cout << " Введите кол-во изменяемих продуктов ";
		cin >> count;
		cin.ignore(256, '\n');

		if (count < 0 || count > shop_.product_size)
		{
			cout << " На складе только " << shop_.product_size << " продуктов\n";
			_getch();
			_getch();
			return;
		}

		cout << endl;

		int *entered_arr = new int[count];

		cout << "Введите номер товара(-ов) ";

		for (int i = 0; i < count; i++) // Цикл,який записує номера товарів і відразу їх змінює
		{
			cin >> entered_arr[i];
			cin.ignore(256, '\n');
			
			if (entered_arr[i] < 0 || entered_arr[i] > shop_.product_size - 1)
			{
				cout << " На складе нету продукта по номером " << entered_arr[i] << endl;
				_getch();
				_getch();
				return;
			}

			shop_.products[entered_arr[i]].cost = new_cost;
		}

		cout << endl;

		_getch();
		_getch();

		delete[]entered_arr;
	}

	//---------Функції для покупця--------

	void buy_product(shop &shop_, float &money) // Функція,для покупки товара
	{
		int count, prod_count = 0; // Змінна для к-сть товару,і доступної к-сть товара
		int *id_prod = new int[shop_.product_size]; // Масив,де знаходятся товари,які потрібно видалити
		float cost = 0; // Змінна,потрібна для перевірки,чи вистачить грошей
		string prod_name; // Назва товара,якого ми хочемо купити

		while (true)
		{
			system("cls");
			cout << "\tПокупка товара\n";
			cout << "На счету " << money << "$\n";
			cout << " Введите имя товара ";
			cin >> prod_name;
			cin.ignore(256, '\n');

			for (int i = 0; i < shop_.product_size-1; i++) // Шукаємо,скільки на складі є такого товара
			{
				if (shop_.products[i].name == prod_name) // Якщо товар є,показуємо його к-сть
				{
					cost = shop_.products[i].cost;
					id_prod[prod_count] = i;
					prod_count++;
				}
			}

			cout << " На складе товара с именем " << prod_name << " есть " << prod_count << " шт.\n";
			cout << " Введите кол-во товара ";
			cin >> count;
			cin.ignore(256, '\n');

			if (count > prod_count || count < 0)
			{
				cout << " Ошибка,вы ввели неправильное кол-во\n";
				Sleep(2000);
				continue;
			}
			else
			{
				if (money > cost*count) // Перевірка,чи достатньо грошей
				{
					shop_.workers[shop_.seller_id].sales++; // Збільшуємо к-сть продаж продавцю
					for (int i = 0; i < count; i++) // Цикл,який видаляє товар
					{
						shop_.products = shop_.push_down(shop_.products, shop_.product_size, id_prod[i]);
					}

					system("cls");
					cout << "\tСпасибо за покупку,приходите еще\n";
					money -= cost * count;

					_getch();
					_getch();

					buyer_menu(shop_, money);
				}
				else {
					cout << " У вас недостаточно денег,не хватает " << cost * count - money << "$\n";
					_getch();
					_getch();
					continue;
				}
			}

			delete[]id_prod; // Видаляємо змінну

			break;
		}
	}

}prod_func; // глобальна змінна,для виклику функцій

struct file_func // Структура,яка зберігає функції для роботи з файлами
{
	ofstream fout; // Змінна для запису в файл
	ifstream fin; // Змінна для зчитування файла

				  //------------Запис в файл-------------
	void write_stats(string info_arr[])	// Функція для виводу статистики в файл
	{
		string file_name = "shop_stats.txt"; // Назва файлу

		fout.open(file_name, ios_base::out | ios_base::ate); // Відкрили файл для запису в кінець файла

		for (int i = 0; i <5; i++)
		{
			fout << "\t" << info_arr[i] << endl;
		}

		fout.close();
	}

	//------------Зчитування файла---------

}file_; // Глобальна змінна для 
		
// --------------------------------------------
//----------Меню------------
//--------------------------------------------

void info_about_product_menu(shop shop_) // Меню інформації про товар
{
	char entered;

	while (true)
	{
		system("cls");

		cout << "\tИнформация про продукты\n";
		cout << "1) Сортировка по порядку возростания\n";
		cout << "2) Сортировка по порядку спадания\n";
		cout << "3) Сортировка названию товара\n";
		cout << "4) Сортировка по типу товара\n";
		cout << "5) Сортировка по цене товара\n";
		cout << "6) Сортировка по популярности товара\n";
		cout << "7) Вернуться назад\n";

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

void change_product_menu(shop &shop_) // Меню,для зміни товару
{
	char entered;
	//							\   /
	while (true) // Вічний цикл 0___0 
	{
		system("cls");
		cout << "\tИзменение товара\n";
		cout << "1) Добавить товар\n";
		cout << "2) Удалить товар\n";
		cout << "3) Изменить имя товара\n";
		cout << "4) Изменить тип товара\n";
		cout << "5) Изменить описание товара\n";
		cout << "6) Изменить цену товара\n";
		cout << "7) Вернуться назад\n";

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

void product_menu(shop &shop_) // Меню керуванням товару
{
	char entered;


	while (true)
	{
		system("cls");

		cout << "\tМеню управление товаром\n";
		cout << "1) Информация про товары\n";
		cout << "2) Изменение товара\n";
		cout << "3) Вернуться назад\n";

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

void change_shop(shop &shop_) // Зміна параметрів магазину
{
	char entered;

	while (true)
	{
		system("cls");

		cout << "\tИзменение магазина\n";
		cout << "1) Изменить имя\n";
		cout << "2) Изменить описание\n";
		if (shop_.state == true)
			cout << "3) Закрыть магазин\n";
		else
			cout << "3) Открыть магазин\n";
		cout << "4) Вернуться назад\n";

		entered = _getch();
		_getch();

		switch (entered)
		{
		case '1':
		{
			system("cls");
			cout << "\tИзменение имя магазина\n";
			cout << " Введите новое имя ";
			cin >> shop_.name;
			cin.ignore(256, '\n');
			break;
		}
		case '2':
		{
			system("cls");
			cout << "\tИзменение описания магазина\n";
			cout << " Введите новое описание ";
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

void buyer_menu(shop &shop_, float &money) // Меню для покупця
{
	char entered;

	while (true)
	{
		system("cls");

		cout << "\tМагазин " << shop_.name << " рад вас приветствовать\n";
		cout << "\tНа счету " << money << "$\n";
		cout << "1) Посмотреть асортимент товаров\n";
		cout << "2) Купить товар\n";
		cout << "3) Уйти с магазина\n";

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

void worker_menu(shop &shop_) // Меню керування співробітниками
{
	char entered;
	while (true)
	{
		system("cls");
		cout << "\tМеню управления сотрудников\n";
		cout << "1) Информация про всех сотрудников\n";
		cout << "2) Выдать выговор сотруднику\n";
		cout << "3) Создать сотрудника\n";
		cout << "4) Уволить сотрудника\n";
		cout << "5) Назад в главное меню\n";

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

void menu_for_worker(shop &shop_) // Меню для працівника
{
	char entered;

	while (true)
	{
		system("cls");

		cout << "\tМагазин " << shop_.name << endl;
		cout << "1) Управление товаром\n";
		cout << "2) Управление сотрудниками\n";
		cout << "3) Статистика магазина\n";
		cout << "4) Сменить пользователя\n";
		cout << "5) Выйти\n";

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
			if (shop_.workers[shop_.seller_id].position != "Director") // Перевірка,чи є у працівника доступ
			{
				cout << "У вас нехватает прав\n";
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
			if (shop_.workers[shop_.seller_id].position != "Glava otdela")// Перевірка,чи є у працівника доступ
			{
				cout << "У вас нехватает прав\n";
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
			shop_.seller_id = NULL; // Тоді немає вільних продавців
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

void leader_menu(shop &shop_) // Головне меню
{

	char entered;
	while (true)
	{
		system("cls");
		cout << "\tМагазин " << shop_.name << endl;
		cout << "1) Управление сотрудниками\n";
		cout << "2) Управление товаром\n";
		cout << "3) Статистика\n";
		cout << "4) Управление магазином\n";
		cout << "5) Сменить пользователя\n";

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
//----------Інші функції--------------
//--------------------------------------------


void stats(shop shop_) // Статистика магазину
{

	//---------Вивід в файл----------

	string arr[6];

	arr[0] = "Статистика магазина ";
	arr[0] += shop_.name;
	arr[1] = "Всего работников ";
	arr[1] += shop_.size;
	arr[2] = "Всего продуктов ";
	arr[2] += shop_.product_size;
	arr[3] = "Всего продаж ";
	arr[3] += shop_.all_sales();
	arr[4] = "Описание - ";
	arr[4] += shop_.description;
	arr[5] = "----------------------";

	file_.write_stats(arr); // Викликаємо функція виводу в файл

							//---------Вивід в консоль---------

	system("cls");

	cout << "\tСтатистика\n";
	cout << " Название магазина " << shop_.name << endl;
	cout << " Всего работников " << shop_.size - 1 << endl;
	cout << " Всего продуктов " << shop_.product_size - 1 << endl;
	cout << " Всего продаж " << shop_.all_sales() << endl;
	cout << " Описание магазина - " << shop_.description << endl;

	_getch();
	_getch();


}

void sign_in(shop &shop_) // Функція входу в систему
{
	string in_name, in_password;
	while (true)
	{
		system("cls");

		cout << "\tВход в систему магазина " << shop_.name << endl;
		cout << ">> Введите логин(имя): ";
		cin >> in_name;
		cin.ignore(256, '\n');
		cout << ">> Введите пароль: ";
		cin >> in_password;
		cin.ignore(256, '\n');

		if (in_name == "admin" && in_password == "admin") // Якщо ми ввели admin admin,це аккаунт бога
			leader_menu(shop_);

		if (shop_.state != true) // Перевірка,чи магазин відкритий
		{
			system("cls");
			cout << "\tМагазин закрыт\n";
			Sleep(2000);
		}
		else if (in_name == "buy" && in_password == "buy") // Аккаунт для покупця
		{
			float money = 200 + rand() % 4800; // Генеруємо гроші

			if (shop_.seller_id == NULL) // Якщо в цей час,немає продавців на роботі
				shop_.seller_id = 1 + rand() % shop_.size; // Генеруємо випадкового продавця
			buyer_menu(shop_, money);
		}
		else // Якщо це не бог і не покупець
		{
			for (int i = 0; i < shop_.size; i++) // Перевірка данних
			{

				if (shop_.workers[i].name == in_name) // Якщо логін підійшов
				{
					if (shop_.workers[i].password == in_password) // Якщо пароль підійшов
					{
						system("cls");
						shop_.seller_id = i; // То на роботу виходить цей робітник

						cout << "\tДобрый день " << shop_.workers[shop_.seller_id].name << endl;
						Sleep(2000);
						menu_for_worker(shop_);
					}
					else // Якщо пароль неправильний
					{
						cout << endl << "Неверный пароль\n";
						Sleep(2000);
					}

				}
				else if (i == shop_.size && shop_.workers[i].name != in_name) // Якщо логін неправильний
				{
					cout << endl << "Неверный логин\n";
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
	shop Apple; // Створюємо магазин

	setlocale(LC_ALL, "Russian");
	srand(time(NULL));


	cout << "Введите название магазина: ";
	cin >> Apple.name; // Вводимо його назву

	sign_in(Apple); // Викликаємо функцію входу
}

