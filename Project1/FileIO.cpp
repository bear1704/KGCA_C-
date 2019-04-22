#include "FileIO.h"



FileIO::FileIO()
{
	//fp = nullptr;
}


FileIO::~FileIO()
{
	if(fp)
		fclose(fp);
}


FILE* FileIO::CreateLoadFile(FILESTATUS status)
{//IO

	if (status == FILESTATUS::LOAD_)
	{
		fp = fopen("student.txt", "r+");
		if (!fp)
			printf("�ҷ��� �����Ͱ� �����ϴ�!\n");
	}


	if (status == FILESTATUS::SAVE_)
	{
		fp = fopen("student.txt", "w+");
	}

	return fp;
}

void FileIO::SaveData(LinkedList* studentList)
{//IO
	FILESTATUS status = FILESTATUS::SAVE_;


	fp = CreateLoadFile(status);

	Node* iterNode = studentList->head->next;

	//fprintf("%d\n", index);
	while (iterNode->next != nullptr) //next�� ������ tail�� ��꿡�� ���� ����
	{
		fprintf(fp, "%d %s %d %d %d\n", iterNode->data.index, iterNode->data.name, iterNode->data.age, iterNode->data.korScore, iterNode->data.mathScore);
		iterNode = iterNode->next;
	}

	fclose(fp);
	printf("���� �Ϸ�\n");
	_getche();

}


void FileIO::LoadData(LinkedList** doublePtrList)
{//IO

	fp = CreateLoadFile(FILESTATUS::LOAD_);
	char buffer[20];
	int index, age, kor, math;

	if (!fp)
	{
		printf("������ �����ϴ�\n");
		_getche();
		return;
	}
	else
	{
		LinkedList* newLL = new LinkedList;

		newLL->head = new Node;
		newLL->tail = new Node;

		newLL->head->next = newLL->tail;
		newLL->tail->prev = newLL->head;

		newLL->head->prev = nullptr;
		newLL->tail->next = nullptr;


		while (!feof(fp))
		{
			Node* node = new Node;
			fscanf(fp, "%d %s %d %d %d\n", &node->data.index, &node->data.name, &node->data.age, &node->data.korScore, &node->data.mathScore);

			newLL->InsertStudentNode(node);
		}

		printf("�ε� �Ϸ�\n");
		_getche();
		fclose(fp);

		LinkedList* tempList;
		tempList = *doublePtrList;

		*doublePtrList = newLL;
	}

}