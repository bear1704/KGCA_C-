#pragma once
#include "HeaderManager.h"
#include "LinkedList.h"

template <typename C, typename N>
class FileIO
{
private:
	FILE* fp;

public:
	FileIO();
	~FileIO();
	FILE* CreateLoadFile(FILESTATUS status);
	void SaveData(LinkedList<C>* studentList);
	void LoadData(LinkedList<C>** doublePtrList);

};

template <typename C, typename N>
FileIO<C, N>::FileIO()
{
	//fp = nullptr;
}

template <typename C, typename N>
FileIO<C, N>::~FileIO()
{
	if (fp)
		fclose(fp);
}

template <typename C, typename N>
FILE* FileIO<C, N>::CreateLoadFile(FILESTATUS status)
{//IO

	FILE* fp_ = nullptr;
	if (status == FILESTATUS::LOAD_)
	{
		fp_ = fopen("student.txt", "r+");
		if (!fp_)
			printf("불러올 데이터가 없습니다!\n");
	}


	if (status == FILESTATUS::SAVE_)
	{
		fp_ = fopen("student.txt", "w+");
	}

	return fp_;
}

template <typename C, typename N>
void FileIO<C, N>::SaveData(LinkedList<C>* studentList)
{//IO
	FILESTATUS status = FILESTATUS::SAVE_;

	fp = CreateLoadFile(status);

	Node<N>* iterNode = studentList->getHead()->getNext();

	while (iterNode->getNext() != nullptr) //next인 이유는 tail을 계산에서 빼기 위해
	{
		fprintf(fp, "%d %s %d %d %d\n", iterNode->getData()->getIntInfo("index"), iterNode->getData()->getStringInfo("name"),
			iterNode->getData()->getIntInfo("age"), iterNode->getData()->getIntInfo("korScore"), iterNode->getData()->getIntInfo("mathScore"));
		iterNode = iterNode->getNext();
	}

	fclose(fp);
	printf("저장 완료\n");
	_getche();

}

template <typename C, typename N>
void FileIO<C, N>::LoadData(LinkedList<C>** doublePtrList)
{//IO

	fp = CreateLoadFile(FILESTATUS::LOAD_);
	char buffer[20];
	int index, age, kor, math;

	if (!fp)
	{
		printf("파일이 없습니다\n");
		_getche();
		return;
	}
	else
	{
		LinkedList<C>* newLL = new LinkedList<C>();

		newLL->SetHeadAndTail(new Node<N>(), new Node<N>());


		newLL->getHead()->SetNextAndPrev(newLL->getTail(), nullptr);
		newLL->getTail()->SetNextAndPrev(nullptr, newLL->getHead());

		while (!feof(fp))
		{
			int index, age, korScore, mathScore;
			char name[25];

			Node<N>* node = new Node<N>();

			fscanf(fp, "%d %s %d %d %d\n", &index, name, &age, &korScore, &mathScore);

			node->getData()->SetData(index, name, age, korScore, mathScore);

			newLL->InsertStudentNode(node);
		}

		printf("로드 완료\n");
		_getche();
		fclose(fp);

		LinkedList<StudentData>* tempList;
		tempList = *doublePtrList;

		if(tempList != nullptr)
			tempList->AllFree(tempList->getHead()->getNext());

		*doublePtrList = newLL;

		
		//_getche();
	}

}

