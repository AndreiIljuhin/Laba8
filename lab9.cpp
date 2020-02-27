#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

template<typename T>
void random_one_array_filling(T*& mass, int N) {
	for (int i = 0; i < N; i++)
		mass[i] = rand() % 100;
}

template<typename T>
void one_array_output(T* mass, int N) {
	cout << "Полученный массив \n";
	for (int i = 0; i < N; i++)
		cout << "[" << i << "]" << mass[i] << " ";
	cout << endl << endl;
}

template<typename T>
void delete_element_by_index_one_array(T*& mass, int index, int& N){//Удаление элемента по индексу
	if (N != 0) {
		for (int i = index; i < N - 1; i++)
			mass[i] = mass[i + 1];
		N--;
		mass = (T*)realloc(mass, N * sizeof(T));
	}
}

template<typename T>
int element_search_one_array(T* mass, T value, int N) {
	for (int i = 0; i < N; i++) {
		if (mass[i] == value)
			return i;
		else if (i == N - 1)
			return -1;
	}
}

template<typename T>
void delete_element_by_value_one_array(T*& mass, T value, int& N) {//Удаление элемента по значению
	if (N != 0) {
		int index = element_search_one_array( mass, value, N);
		if (index != -1)
			delete_element_by_index_one_array(mass, index, N);
	}
}

template<typename T>
void insert_element_one_array(T*& mass, int index, T element, int& N) {//Вставка элемента
	N++;
	mass = (T*)realloc(mass, N * sizeof(T));
	for (int i = N - 1; i > index; i--)
		mass[i] = mass[i - 1];
	mass[index] = element;
}

void clear_stream() {
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
}

char* one_char_keyboard_array(int& N) {
	char* arr = (char*)malloc(1);
	int i = 0;
	while (cin.get(arr[i]) and arr[i] != '\n') {
		if (arr[i] != ' ') {
			i++;
			arr = (char*)realloc(arr, i + 1);
		}
	}
	arr[i] = '\0';
	N = i;
	return arr;
}

char* one_char_file_array(int& N) {
	system("File.txt");
	ifstream file("File.txt");
	char* arr = (char*)malloc(1);
	int i = 0;
	while (file.get(arr[i])) {
		if (arr[i] != ' ') {
			i++;
			arr = (char*)realloc(arr, i + 1);
		}
	}
	arr[i] = '\0';
	N = i;
	file.close();
	return arr;
}

void cout_time(unsigned start_time, unsigned end_time, char* str) {
	unsigned search_time = end_time - start_time;
	if (!search_time)
		cout << str << ": меньше, чем за 0.001 секунды\n\n";
	else
		cout << str << ": за " << (float)search_time / 1000 << " секунды\n\n";
}

template<typename T>
struct doubly_list {//Двусвязный список
	T info;
	doubly_list* previous = nullptr;//Предыдущий
	doubly_list* following = nullptr;//Следующий
};

void random_list_filling(doubly_list<int>* first_object) {
	doubly_list<int>* current_object = first_object;
	while (current_object != nullptr) {
		current_object->info = rand() % 100;
		current_object = current_object->following;
	}
}

void list_keyboard_filling(doubly_list<char>*& first_object, int& N_list) {
	doubly_list<char>* last_object = nullptr;
	doubly_list<char>* current_object = first_object;
	if (first_object != nullptr) {
		last_object = first_object->previous;
	}
	char c;
	int counter = 0;
	cout << "Вводите элементы списка, после нажатия клавиши Entr все объекты будут созданы\n";
	while (cin.get(c) and c != '\n') {
		if (c != ' ') {
			if (current_object == nullptr)
				current_object = new doubly_list<char>;
			if (first_object == nullptr)
				first_object = current_object;
			current_object->info = c;
			if (last_object != nullptr)
				last_object->following = current_object;
			current_object->previous = last_object;
			last_object = current_object;
			current_object = current_object->following;
			counter++;
		}
	}
	clear_stream();
	cout << "Количество объектов списка: " << counter << endl;
	N_list = counter;
}

void list_file_filling(doubly_list<char>*& first_object, int& N_list) {
	doubly_list<char>* last_object = nullptr;
	doubly_list<char>* current_object = first_object;
	if (first_object != nullptr) {
		last_object = first_object->previous;
	}
	char c;
	int counter = 0;
	cout << "Вводите элементы списка, после закрытия файла все объекты будут созданы\n";
	system("File.txt");
	ifstream file("File.txt");
	while (file.get(c)) {
		if (!(c == ' ' or c == '\n')) {
			if (current_object == nullptr)
				current_object = new doubly_list<char>;
			if (first_object == nullptr)
				first_object = current_object;
			current_object->info = c;
			if (last_object != nullptr)
				last_object->following = current_object;
			current_object->previous = last_object;
			last_object = current_object;
			current_object = current_object->following;
			counter++;
		}
	}
	file.close();
	cout << "Количество объектов списка: " << counter << endl;
	N_list = counter;
}

template<typename T>
void list_output(doubly_list<T>* first_object) {
	int counter = 1;
	while (first_object != nullptr) {
		cout << "[" << counter << "]" << first_object->info << " ";
		first_object = first_object->following;
		counter++;
	}
	cout << endl;
}

template<typename T>
void delete_list(doubly_list<T>*& first_object) {
	doubly_list<T>* current_object = first_object;
	doubly_list<T>* next_object = first_object->following;
	while (current_object != nullptr) {
		delete current_object;
		current_object = next_object;
		if (current_object != nullptr)
			next_object = next_object->following;
	}
	first_object = nullptr;
}

template<typename T>
void create_list(doubly_list<T>*& first_object, int N) {
	first_object = new doubly_list<T>;
	doubly_list<T>* current_object = first_object;
	doubly_list<T>* next_object;
	for (int i = 0; i < N - 1; i++) {
		next_object = new doubly_list<T>;
		next_object->previous = current_object;
		current_object->following = next_object;
		current_object = next_object;
	}
}

template<typename T>
bool list_insert_item(doubly_list<T>*& first_object, int N, T info) {
	if (N > 0) {
		doubly_list<T>* current_object = first_object;
		for (int i = 1; i < N; i++) {
			if (current_object->following != nullptr)
				current_object = current_object->following;
			else {//Последний в списке
				doubly_list<T>* new_object = new doubly_list<T>;
				new_object->info = info;
				new_object->previous = current_object;
				current_object->following = new_object;
				return 0;
			}
		}
		doubly_list<T>* new_object = new doubly_list<T>;
		new_object->info = info;
		if (N != 1)
			current_object->previous->following = new_object;
		else
			first_object = new_object;
		new_object->previous = current_object->previous;
		new_object->following = current_object;
		current_object->previous = new_object;
	}
	return 1;
}

template<typename T>
bool list_delete_item_by_index(doubly_list<T>*& first_object, int N) {
	if (N > 0) {
		doubly_list<T>* current_object = first_object;
		for (int i = 1; i < N; i++) {
			if (current_object->following != nullptr)
				current_object = current_object->following;
			else
				return 0;//Слишком большой N
		}
		if (current_object->following != nullptr)
			current_object->following->previous = current_object->previous;
		if (current_object->previous != nullptr)
			current_object->previous->following = current_object->following;
		else
			first_object = current_object->following;
		delete current_object;
		return 1;
	}
	else
		return 0;
}

template<typename T>
bool list_delete_item_by_value(doubly_list<T>*& first_object, T value) {
	doubly_list<T>* current_object = first_object;
	while (!(current_object == nullptr or current_object->info == value))
		current_object = current_object->following;
	if (current_object != nullptr) {
		if (current_object->following != nullptr)
			current_object->following->previous = current_object->previous;
		if (current_object->previous != nullptr)
			current_object->previous->following = current_object->following;
		else
			first_object = current_object->following;
		delete current_object;
		return 1;
	}
	else
		return 0;

}

template<typename T>
T list_search_by_index(doubly_list<T>* first_object, int N) {
	doubly_list<T>* current_object = first_object;
	for(int i = 1; i < N; i++)
		if (current_object->following != nullptr)
			current_object = current_object->following;
		else
			return -1;//Слишком большой N
	return current_object->info;
}

template<typename T>
int list_search_by_value(doubly_list<T>* first_object, T value) {
	doubly_list<T>* current_object = first_object;
	int counter = 1;
	while (!(current_object == nullptr or current_object->info == value)) {
		current_object = current_object->following;
		counter++;
	}
	if (current_object == nullptr)
		return -1;
	else
		return counter;
}

template<typename T>
void one_array_bubbleSort(T* arr, int N)
{
	T temp;
	for (int i = 0; i < N - 1; i++)
		for (int j = 0; j < N - i - 1; j++)
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
}

template<typename T>
int list_get_length(doubly_list<T>* current_object) {
	int counter = 0;
	while (current_object != nullptr) {
		current_object = current_object->following;
		counter++;
	}
	return counter;
}

template<typename T>
void list_bubbleSort(doubly_list<T>* first_object, int N)
{
	T temp;
	doubly_list<T>* current_object;
	for (int i = 0; i < N - 1; i++) {
		current_object = first_object;
		for (int j = 0; j < N - i - 1; j++) {
			if (current_object->info > current_object->following->info) {
				temp = current_object->info;
				current_object->info = current_object->following->info;
				current_object->following->info = temp;
			}
			current_object = current_object->following;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));
	bool exit = 0;
	int* mass = nullptr;
	char* mass2 = nullptr;
	doubly_list<int>* first_objecti = nullptr;
	doubly_list<char>* first_objectc = nullptr;
	int N = 0, N_list = 0;
	int choise, number, infoi;
	char infoc;
	unsigned start_time;
	unsigned end_time;
	while (!exit) {
		system("cls");
		cout << "1 - Cоздание массива\n";
		cout << "2 - Вставка, удаление и получение элемента массива\n";
		cout << "3 - Формирование двусвязного списка размерности N\n";
		cout << "4 - Вставка элемента двусвязного списка\n";
		cout << "5 - Удаление элемента двусвязного списка\n";
		cout << "6 - Получение элемента двусвязного списка\n";
		cout << "7 - bubble sort\n";
		cin >> choise;
		clear_stream();

		switch (choise) {
		case 1://Cоздание массива
			if (mass != nullptr) {
				free(mass);
				mass = nullptr;
			}
			if (mass2 != nullptr) {
				free(mass2);
				mass2 = nullptr;
			}
			cout << " 1 - N с клавиатуры, элементы рандомно\n";
			cout << " 2 - элементы с клавиатуры, N автоматически\n";
			cout << " 3 - элементы с файла, N автоматически\n";
			cin >> choise;
			clear_stream();
			switch (choise) {
			case 1:
				cout << "Количество элементов одномерного массива: ";
				cin >> N;
				clear_stream();
				start_time = clock();
				mass = (int*)malloc(N * sizeof(int));
				random_one_array_filling(mass, N);
				one_array_output(mass, N);
				end_time = clock();
				cout_time(start_time, end_time, (char*)"создание и вывод динамического массива");
				break;

			case 2:
				cout << "Вводите элементы символьного массива, после нажатия клавиши Enter массив будет автоматически создан: ";
				mass2 = one_char_keyboard_array(N);
				one_array_output(mass2, N);
				break;

			case 3:
				cout << "Запишите символьный массив в файл\n";
				mass2 = one_char_file_array(N);
				one_array_output(mass2, N);
				break;
			}
			break;

		case 2://Вставка, удаление и получение элемента массива
			if (mass != nullptr or mass2 != nullptr) {
				cout << " 1 - вставка элемента\n";
				cout << " 2 - удаление элемента по значению\n";
				cout << " 3 - удаление по индексу\n";
				cout << " 4 - поиск индекса элемента\n";
				cout << " 5 - вывод значения по индексу\n";
				cin >> choise;
				clear_stream();
				int element;
				char element2;
				int index;
				if (mass != nullptr) {
					switch (choise)
					{
					case 1:// вставка элемента целочисленного массива
						cout << "Значение элемента: ";
						cin >> element;
						clear_stream();
						cout << "Номер в массиве: ";
						cin >> index;
						clear_stream();
						index--;
						if (index < N + 1 and index >= 0) {
							start_time = clock();
							insert_element_one_array(mass, index, element, N);
							end_time = clock();
							cout_time(start_time, end_time, (char*)"добавление элемента в массив");
							one_array_output(mass, N);
						}
						else
							cout << "Слишком большой или маленький индекс\n";
						break;

					case 2:// удаление элемента целочисленного массива по значению
						cout << "Значение элемента: ";
						cin >> element;
						clear_stream();
						start_time = clock();
						delete_element_by_value_one_array(mass, element, N);
						end_time = clock();
						cout_time(start_time, end_time, (char*)"поиск и удаление(если есть) элемента");
						one_array_output(mass, N);
						break;

					case 3:// удаление элемента целочисленного массива по индексу
						cout << "Номер в массиве: ";
						cin >> index;
						clear_stream();
						index--;
						if (index < N + 1 and index >= 0) {
							unsigned start_time = clock();
							delete_element_by_index_one_array(mass, index, N);
							unsigned end_time = clock();
							cout_time(start_time, end_time, (char*)"удаление элемента");
							one_array_output(mass, N);
						}
						else
							cout << "Слишком большой или маленький индекс\n";
						break;

					case 4:// поиск индекса элемента целочисленного массива
						cout << "Значение элемента: ";
						cin >> element;
						clear_stream();
						start_time = clock();
						index = element_search_one_array(mass, element, N);
						end_time = clock();
						if (index != -1)
							cout << "Элемент не найден\n";
						else
							cout << "Элемент найден, номер: " << ++index << endl;
						cout_time(start_time, end_time, (char*)"поиск");
						break;

					case 5:// определение значения элемента целочисленного массива
						cout << "Номер в массиве: ";
						cin >> index;
						clear_stream();
						index--;
						if (index >= 0 and index < N)
							cout << "Элемент под номером " << index << ": " << mass[index] << endl;
						else
							cout << "Слишком большой или маленький номер\n";
						break;
					}
				}
				else if (mass2 != nullptr) {
					switch (choise)
					{
					case 1://вставка элемента символьного массива
						cout << "Значение элемента: ";
						cin >> element2;
						clear_stream();
						cout << "Номер в массиве: ";
						cin >> index;
						clear_stream();
						index--;
						if (index < N + 1 and index >= 0) {
							start_time = clock();
							insert_element_one_array(mass2, index, element2, N);
							end_time = clock();
							cout_time(start_time, end_time, (char*)"добавление элемента в массив");
							one_array_output(mass2, N);
						}
						else
							cout << "Слишком большой или маленький индекс\n";
						break;

					case 2:// удаление элемента символьного массива по значению
						cout << "Значение элемента: ";
						cin >> element2;
						clear_stream();
						start_time = clock();
						delete_element_by_value_one_array(mass2, element2, N);
						end_time = clock();
						cout_time(start_time, end_time, (char*)"поиск и удаление(если есть) элемента");
						one_array_output(mass2, N);
						break;

					case 3:// удаление элемента символьного массива по индексу
						cout << "Номер в массиве: ";
						cin >> index;
						clear_stream();
						index--;
						if (index < N + 1 and index >= 0) {
							start_time = clock();
							delete_element_by_index_one_array(mass2, index, N);
							end_time = clock();
							cout_time(start_time, end_time, (char*)"удаление элемента");
							one_array_output(mass2, N);
						}
						else
							cout << "Слишком большой или маленький индекс\n";
						break;

					case 4:// поиск индекса элемента символьного массива
						cout << "Значение элемента: ";
						cin >> element2;
						clear_stream();
						start_time = clock();
						index = element_search_one_array(mass2, element2, N);
						end_time = clock();
						if (index != -1)
							cout << "Элемент не найден\n";
						else
							cout << "Элемент найден, номер: " << ++index << endl;
						cout_time(start_time, end_time, (char*)"поиск");
						break;

					case 5:// определение значения элемента сивмольного массива
						cout << "Номер в массиве: ";
						cin >> index;
						clear_stream();
						index--;
						if (index >= 0 and index < N)
							cout << "Элемент под номером " << index << ": " << mass2[index] << endl;
						else
							cout << "Слишком большой или маленький номер\n";
						break;
					}
				}
			}
			else cout << "Сначала создайте массив\n";
			break;

		case 3://Формирование двусвязного списка размерности N
			if (first_objecti != nullptr)
				delete_list(first_objecti);
			if (first_objectc != nullptr) 
				delete_list(first_objectc);

			cout << " 1 - N с клавиатуры, элементы рандомно\n";
			cout << " 2 - элементы с клавиатуры, N автоматически\n";
			cout << " 3 - элементы с файла, N автоматически\n";
			cin >> choise;
			clear_stream();
			switch (choise) {
			case 1:
				cout << "Количество объектов списка: ";
				cin >> N_list;
				clear_stream();
				start_time = clock();
				create_list(first_objecti, N_list);
				random_list_filling(first_objecti);
				list_output(first_objecti);
				end_time = clock();
				cout_time(start_time, end_time, (char*)"создание и вывод списка");
				break;

			case 2:
				list_keyboard_filling(first_objectc, N_list);
				list_output(first_objectc);
				break;

			case 3:
				list_file_filling(first_objectc, N_list);
				list_output(first_objectc);
				break;
			}
			break;

		case 4://Вставка элемента двусвязного списка
			if (first_objecti != nullptr) {
				cout << "Вставить на место: ";
				cin >> number;
				clear_stream();
				if (number > 0) {
					cout << "Введите значение: ";
					cin >> infoi;
					clear_stream();
					start_time = clock();
					list_insert_item(first_objecti, number, infoi);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"вставка объекта в список");
					list_output(first_objecti);
				}
				else
					cout << "Слишком маленький номер\n";
			}
			else if (first_objectc != nullptr) {
				cout << "Вставить на место: ";
				cin >> number;
				clear_stream();
				if (number > 0) {
					cout << "Введите значение: ";
					cin >> infoc;
					clear_stream();
					start_time = clock();
					list_insert_item(first_objectc, number, infoc);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"вставка объекта в список");
					list_output(first_objectc);
				}
				else
					cout << "Слишком маленький номер\n";
			}
			else
				cout << "Сначала создайте список длиной хотя бы 1 элемент\n";
			break;

		case 5://Удаление элемента двусвязного списка
			cout << " 1 - по индексу\n";
			cout << " 2 - по значению\n";
			cin >> choise;
			clear_stream();
			if (choise == 1) {
				cout << "Введите индекс: ";
				cin >> number;
				if (first_objecti != nullptr) {
					start_time = clock();
					if (list_delete_item_by_index(first_objecti, number)) {
						end_time = clock();
						cout_time(start_time, end_time, (char*)"удаление объекта списка");
					}
					else
						cout << "Элемент не найден\n";
					list_output(first_objecti);
				}
				else if (first_objectc != nullptr) {
					start_time = clock();
					if (list_delete_item_by_index(first_objectc, number)) {
						end_time = clock();
						cout_time(start_time, end_time, (char*)"удаление объекта списка");
					}
					else
						cout << "Элемент не найден\n";
					list_output(first_objectc);
				}
				else
					cout << "Сначала создайте список длиной хотя бы 1 элемент\n";
				break;
			}
			else if (choise == 2) {
				if (first_objecti != nullptr) {
					cout << "Введите значение: ";
					cin >> infoi;
					clear_stream();
					start_time = clock();
					if (list_delete_item_by_value(first_objecti, infoi)) {
						end_time = clock();
						cout_time(start_time, end_time, (char*)"удаление объекта списка");
					}
					else
						cout << "Элемент не найден\n";
					list_output(first_objecti);
				}
				else if (first_objectc != nullptr) {
					cout << "Введите значение: ";
					cin >> infoc;
					clear_stream();
					start_time = clock();
					if (list_delete_item_by_value(first_objectc, infoc)) {
						end_time = clock();
						cout_time(start_time, end_time, (char*)"удаление объекта списка");
					}
					else
						cout << "Элемент не найден\n";
					list_output(first_objectc);
				}
				else
					cout << "Сначала создайте список длиной хотя бы 1 элемент\n";
				break;
			}
			break;

		case 6:
			cout << " 1 - Получение по индексу\n";
			cout << " 2 - По значению\n";
			cin >> choise;
			if (choise == 1) {
				cout << "Введите индекс: ";
				cin >> number;
				clear_stream();
				if (first_objecti != nullptr) {
					start_time = clock();
					infoi = list_search_by_index(first_objecti, number);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"поиск элемента списка");
					if (infoi == -1)
						cout << "Элемента под этим номером не существует\n";
					else
						cout << "Элемент под номером " << number << ": " << infoi << endl;
					list_output(first_objecti);
				}
				else if (first_objectc != nullptr) {
					start_time = clock();
					infoc = list_search_by_index(first_objectc, number);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"поиск элемента списка");
					if (infoc == -1)
						cout << "Элемента под этим номером не существует\n";
					else
						cout << "Элемент под номером " << number << ": " << infoc << endl;
					list_output(first_objectc);
				}
				else
					cout << "Сначала создайте список длиной хотя бы 1 элемент\n";
				break;
			}
			else if (choise == 2) {
				if (first_objecti != nullptr) {
					cout << "Введите значение: ";
					cin >> infoi;
					clear_stream();
					start_time = clock();
					number = list_search_by_value(first_objecti, infoi);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"поиск объекта списка");
					if (number == -1)
						cout << "Элемент не найден\n";
					else
						cout << "Элемент найден, его номер " << number << endl;
					list_output(first_objecti);
				}
				else if (first_objectc != nullptr) {
					cout << "Введите значение: ";
					cin >> infoc;
					clear_stream();
					start_time = clock();
					number = list_search_by_value(first_objectc, infoc);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"поиск объекта списка");
					if (number == -1)
						cout << "Элемент не найден\n";
					else
						cout << "Элемент найден, его номер " << number << endl;
					list_output(first_objectc);
				}
				else
					cout << "Сначала создайте список длиной хотя бы 1 элемент\n";
				break;
			}
			break;

		case 7:
			cout << "1 - Сортировка массива\n";  
			cout << "2 - Сортировка списка\n";
			cin >> choise;
			clear_stream();
			if (choise == 1) {
				if (mass != nullptr) {
					start_time = clock();
					one_array_bubbleSort(mass, N);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"сортировка");
					one_array_output(mass, N);
				}
				else if (mass2 != nullptr) {
					start_time = clock();
					one_array_bubbleSort(mass2, N);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"сортировка");
					one_array_output(mass2, N);
				}
				else
					cout << "Сначала создайте массив\n";
			}
			else if (choise == 2) {
				if (first_objecti != nullptr) {
					start_time = clock();
					N_list = list_get_length(first_objecti);
					list_bubbleSort(first_objecti, N_list);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"определение длины и сортировка");
					list_output(first_objecti);
				}
				else if (first_objectc != nullptr) {
					start_time = clock();
					N_list = list_get_length(first_objectc);
					list_bubbleSort(first_objectc, N_list);
					end_time = clock();
					cout_time(start_time, end_time, (char*)"определение длины и сортировка");
					list_output(first_objectc);
				}
				else
					cout << "Сначала создайте список\n";
			}
			break;
		}
		system("Pause");
	}
}