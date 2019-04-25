#include "ScoreManagementManager.h"





ScoreManagementManager::ScoreManagementManager()
{
}


ScoreManagementManager::~ScoreManagementManager()
{
}

LinkedList<StudentData> * ScoreManagementManager::CreateInitialList()
{


		LinkedList<StudentData>* studentList = new LinkedList<StudentData>();
		
		/*Head, Tail ����*/
		studentList->SetHeadAndTail(new Node<StudentData>(), new Node<StudentData>());
		
		studentList->getHead()->SetNextAndPrev(studentList->getTail(), nullptr);
		studentList->getTail()->SetNextAndPrev(nullptr, studentList->getHead());

		LinkedList<StudentData>::index = 1;  // static index �ʱ�ȭ

		printf("\n���̺��� �����Ǿ����ϴ�\n");

		_getche();

		return studentList;


}


void ScoreManagementManager::Init()
{//Manager
	char temp = NULL;
	SELECT inputData = SELECT::NONE;



	LinkedList<StudentData>* studentList = nullptr;
	
	FileIO<StudentData, StudentData>* fileIO = new FileIO<StudentData, StudentData>;



	while (inputData != SELECT::EXIT)
	{

		char name[25];

		system("cls");
		printf("\n1.����\n2.������ ����\n3.������ ����\n4.������ �˻� �� ����\n5.������ ����\n6.������ �ε�\n7.������ ����\n8.���� ������ ����\n0.����\n");

		scanf("%c", &temp);

		if (isdigit(temp))
			inputData = (SELECT)(temp - '0');
		else
		{
			continue;
		}

		switch (inputData)
		{
		case SELECT::CREATE:
			if (studentList)
			{
				delete studentList;
				studentList = nullptr;
			}
			studentList = CreateInitialList();
			break;
		case SELECT::INSERT:
			if (isListEmpty(studentList))
				continue;
			studentList->InsertStudent();
			break;
		case SELECT::DELETE:
			if (isListEmpty(studentList))
				continue;
			printf("������ �̸� �Է� : ");
			scanf("%s", &name);
			studentList->SearchDeleteTarget(name);
			break;
		case SELECT::SEARCH_AND_MODIFY:
			if(isListEmpty(studentList))
				continue;
			studentList->SearchModify();
			break;
		case SELECT::SAVE:
			fileIO->SaveData(studentList);
			break;
		case SELECT::LOAD:
			fileIO->LoadData(&studentList);
			break;
		case SELECT::PRINT:
			if (isListEmpty(studentList))
				continue;
			studentList->PrintData();
			break;
		case SELECT::SAMPLEDATA:
			if (isListEmpty(studentList))
				continue;
			studentList->WriteSampleData();
			break;
		case SELECT::EXIT:
			if (studentList)
				studentList->AllFree(studentList->getHead()->getNext());
			
			if(studentList)
				delete studentList;
			
			if (fileIO)
				delete fileIO;

			return;
		default:
			inputData = SELECT::NONE;
			continue;
			break;
		}

		inputData = SELECT::NONE;
	
	}



}

bool ScoreManagementManager::isListEmpty(LinkedList<StudentData>* LL)
{
	if (!LL)
	{
		printf("�л� ���̺��� ����ÿ�\n");
		_getche();
		return true;
	}
	

	return false;
}



int main()
{
	ScoreManagementManager scoreManager;
	scoreManager.Init();


	system("pause");





}