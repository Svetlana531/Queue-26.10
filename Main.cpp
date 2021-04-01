#include "Queue.h"
#include <locale>

#define PATH_FOR_FILE  "C:\\out.txt"

int main()
{
	setlocale(LC_ALL, "RUS");

	int sizeQueue = 5;

	std::cout << "���� Queue\n";
	queue<int> qu(sizeQueue);

	std::cout << "�������� ������:\n";
	srand(time(NULL));

	for (int i = 0; i < sizeQueue ; i++)
	{
		int val = rand() % 15;
		std::cout << val << " ";
		qu.Put(val);
	}
	std::cout << "\n";
		
	std::cout << "Front - " << qu.Front() << " Back - " << qu.Back() << " Size - " << qu.Size() << "\n";
	qu.Pop();

	std::cout << "Front - " << qu.Front() << " Back - " << qu.Back() << " Size - " << qu.Size() << "\n";
	qu.Pop();

	std::cout << "Front - " << qu.Front() << " Back - " << qu.Back() << " Size - " << qu.Size() << "\n";
	qu.Pop();

	std::cout << "Front - " << qu.Front() << " Back - " << qu.Back() << " Size - " << qu.Size() << "\n";
	qu.Pop();

	std::cout << "Front - " << qu.Front() << " Back - " << qu.Back() << " Size - " << qu.Size() << "\n";
	qu.Pop();
	std::cout << "Size - " << qu.Size() << "\n\n";

	std::cout << "Pop �� ������� Queue:\n";
	try
	{
		qu.Pop();
	}
	catch (std::logic_error err)
	{
		std::cout << err.what();
	}

	std::cout << "\n\n";

	std::cout << "Front �� ������� Queue:\n";
	try
	{
		qu.Front();
	}
	catch (std::logic_error err)
	{
		std::cout << err.what();
	}

	std::cout << "\n\n";

	std::cout << "Back �� ������� Queue:\n";
	try
	{
		qu.Back();
	}
	catch (std::logic_error err)
	{
		std::cout << err.what();
	}

	std::cout << "\n\n";

	for (int i = 0; i < sizeQueue; i++)
	{
		int val = 1 + rand() % 300;
		qu.Put(val);
	}
	qu.Print();

	std::cout << "����������� ������� - " << qu.FindMin() << "\n";
	std::cout << "������������ ������� - " << qu.FindMax() << "\n";

	std::cout << "\n";

	std::cout << "\n���������� �������� � ����������� stack:\n";
	try
	{
		qu.Put(3);
	}
	catch (std::logic_error err)
	{
		std::cout << err.what();
	}

	qu.InFile(PATH_FOR_FILE);
	std::cout << "������� �� ����������: ";
	qu.Print();

	queue<int> qu_2(sizeQueue);
	qu_2.FromFile(PATH_FOR_FILE);
	std::cout << "������� ����� ������ �� �����: ";
	while (!qu_2.Empty())
	{
		std::cout << qu_2.Pop() << " ";
	}

	std::cout << "\n";

	system("pause");
	return 0;
}
