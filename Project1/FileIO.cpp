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

	FILE* fp_ = nullptr;
	if (status == FILESTATUS::LOAD_)
	{
		fp_ = fopen("student.txt", "r+");
		if (!fp_)
			printf("�ҷ��� �����Ͱ� �����ϴ�!\n");
	}


	if (status == FILESTATUS::SAVE_)
	{
		fp_ = fopen("student.txt", "w+");
	}

	return fp_;
}

void FileIO::SaveData(LinkedList* studentList)
{//IO
	FILESTATUS status = FILESTATUS::SAVE_;

	fp = CreateLoadFile(status);

	Node* iterNode = studentList->getHead()->getNext();


	while (iterNode->getNext() != nullptr) //next�� ������ tail�� ��꿡�� ���� ����
	{
		fprintf(fp, "%d %s %d %d %d\n", iterNode->getData()->getIntInfo("index"), iterNode->getData()->getStringInfo("name"),
			iterNode->getData()->getIntInfo("age"), iterNode->getData()->getIntInfo("korScore"), iterNode->getData()->getIntInfo("mathScore"));
		iterNode = iterNode->getNext();
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

		newLL->SetHeadAndTail(new Node(), new Node());


		newLL->getHead()->SetNextAndPrev(newLL->getTail(), nullptr);
		newLL->getTail()->SetNextAndPrev(nullptr, newLL->getHead());

		/*newLL->getHead()->next = newLL->getTail();
		newLL->getTail()->prev = newLL->getHead();

		newLL->getHead()->prev = nullptr;
		newLL->getTail()->next = nullptr;
		*/

		while (!feof(fp))
		{
			int index, age, korScore, mathScore;
			char name[25];

			Node* node = new Node;

			fscanf(fp, "%d %s %d %d %d\n", &index, name, &age, &korScore, &mathScore);

			node->getData()->SetData(index, name, age, korScore, mathScore);

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

