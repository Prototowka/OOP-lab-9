#include <iostream>
#include <string>

using namespace std;

//узел списка
template<typename t>
struct Node {
	t data; //инф. поле
	Node* next; //следующий узел
	Node* prev; //предыдущий

	//конструктор
	Node(t data) {
		this->data = data;
		next = prev = nullptr;
	}

	//по умолчанию
	Node() {
		data = t();
		next = prev = nullptr;
	}
};

//шаблон двусвязного некольцевого списка
template<typename t>
class List {
	Node<t>* head; //голова списка
	Node<t>* tail; //хвост

public:
	//конструктор
	List() {
		head = tail = nullptr;
	}

	//указатели
	Node<t>* begin(int index) {
		Node<t>* cur = head;
		while (index > 0 && cur->next) {
			index--;
			cur = cur->next;
		}
		return cur;
	}

	//добавление в начало списка
	void push_front(t data) {
		Node<t>* n = new Node<t>(data);
		if (!isEmpty()) {
			n->next = head;
			head->prev = n;
			head = n;
		}
		else {
			head = tail = n;
		}
	}

	//удаление из начала списка
	void pop_front() {
		if (!isEmpty()) {
			Node<t>* cur = head;
			head = head->next;
			delete cur;
			if (!head) {
				head = tail = nullptr;
			}
			else {
				head->prev = nullptr;
			}
		}
	}

	//добавление в произвольное место отличное от начала
	void insert(Node<t>* cur, t data) {
		if (!isEmpty()) {
			if (cur) {
				Node<t>* n = new Node<t>(data);
				if (cur == tail) {
					tail->next = n;
					n->prev = tail;
					tail = n;
				}
				else {
					cur->next->prev = n;
					n->next = cur->next;
					n->prev = cur;
					cur->next = n;
				}
			}
		}
		else {
			push_front(data); //если список пуст
		}
	}

	//удаление из произвольного места отличного от начала
	void remove(Node<t>* cur) {
		if (!isEmpty()) {
			if (cur) {
				cur = cur->next;
				if (cur) {
					if (cur == tail) {
						tail = tail->prev;
						if (!tail) {
							head = nullptr;
							tail = nullptr;
						}
						else {
							tail->next = nullptr;
						}
					}
					else {
						cur->prev->next = cur->next;
						cur->next->prev = cur->prev;
					}
					delete cur;
				}
			}
		}
		else {
			cout << "Список пуст" << endl;
		}
	}

	//проверка на пустоту
	bool isEmpty() {
		return head == nullptr;
	}

	//очистка списка
	void clear() {
		while (head) {
			Node<t>* cur = head;
			head = head->next;
			delete cur;
		}
		head = tail = nullptr;
	}

	//формирование списка
	bool form() {
		int size = 0;
		cout << "Укажите кол-во элементов списка: ";
		cin >> size;
		if (cin.fail()) {
			return false;
		}
		cout << "Введите элементы списка:" << endl;
		t elem;
		for (int i = 0; i < size; i++) {
			cout << "№" << (i + 1) << ": ";
			cin >> elem;
			if (cin.fail()) {
				clear();
				return false;
			}
			push_front(elem);
		}
		return true;
	}

	//печать списка
	void print() {
		if (!isEmpty()) {
			for (Node<t>* i = head; i; i = i->next) {
				cout << i->data << " ";
			}
			cout << endl;
		}
		else {
			cout << "Список пуст" << endl;
		}
	}

	//подсчет кол-ва элементов у которых соседи равны
	int calc() {
		int k = 0;
		if (!isEmpty()) {
			for (Node<t>* i = head->next; i; i = i->next) {
				if (i != tail) {
					//элемент слева равен элементу справа
					if (i->prev->data == i->next->data) {
						k++;
					}
				}
			}
		}
		return k;
	}

	//деструктор
	~List() {
		clear();
	}
};

//тест класса List<t>
int main() {
	system("chcp 1251");
	system("cls");
	int num = 0;
	List<int> list;
	do {
		cout << "1 - Добавление в начало" << endl;
		cout << "2 - Удаление из начала" << endl;
		cout << "3 - Добавление в произвольное место" << endl;
		cout << "4 - Удаление из произвольного места" << endl;
		cout << "5 - Проверка списка на пустоту" << endl;
		cout << "6 - Очистка списка" << endl;
		cout << "7 - Формирование списка" << endl;
		cout << "8 - Печать списка" << endl;
		cout << "9 - Подсчитать кол-во элементов у которых равные соседи" << endl;
		cout << "0 - Выход;" << endl;
		cout << ">> ";
		cin >> num;
		switch (num) {
		case 1: {
			int k = 0;
			cout << "Введите значение элемента: ";
			cin >> k;
			if (!cin.fail())
				list.push_front(k);
			break;
		}
		case 2: {
			list.pop_front();
			break;
		}
		case 3: {
			int k = 0;
			cout << "Введите значение элемента: ";
			cin >> k;
			if (!cin.fail()) {
				cout << "Укажите номер элемента для вставки: ";
				int index;
				cin >> index;
				if (!cin.fail())
					list.insert(list.begin(index), k);
			}
			break;
		}
		case 4: {
			cout << "Укажите номер элемента для удаления: ";
			int index;
			cin >> index;
			if (!cin.fail())
				list.remove(list.begin(index));
			break;
		}
		case 5: {
			if (list.isEmpty()) {
				cout << "Список пуст" << endl;
			}
			else {
				cout << "Список не пуст" << endl;
			}
			break;
		}
		case 6: {
			list.clear();
			cout << "Список очищен" << endl;
			break;
		}
		case 7: {
			list.form();
			break;
		}
		case 8: {
			list.print();
			break;
		}
		case 9: {
			cout << "Кол-во элементов к которых равные соседи: " << list.calc() << endl;
			break;
		}
		}
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<int>::max(), '\n');
			cout << "Ошибка ввода!" << endl;
			num = -1;
		}
		cout << endl;
	} while (num != 0);
	system("pause");
	return 0;
}