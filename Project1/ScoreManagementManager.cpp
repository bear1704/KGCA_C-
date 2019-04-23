#include "ScoreManagementManager.h"





ScoreManagementManager::ScoreManagementManager()
{
}


ScoreManagementManager::~ScoreManagementManager()
{
}

LinkedList * ScoreManagementManager::CreateInitialList()
{


		LinkedList* studentList = new LinkedList;
		
		/*Head, Tail 선언*/
		studentList->SetHeadAndTail(new Node(), new Node());
		

		//studentList->getHead()->getNext() = studentList->getTail(); //Head의 다음 노드는 Tail로
		//studentList->getTail()->prev = studentList->getHead(); //Taill의 이전 노드는 head로
		//studentList->getHead()->prev = nullptr;
		//studentList->getTail()->next = nullptr;

		studentList->getHead()->SetNextAndPrev(studentList->getTail(), nullptr);
		studentList->getTail()->SetNextAndPrev(nullptr, studentList->getHead());

		LinkedList::index = 1;  // static index 초기화

		printf("\n테이블이 생성되었습니다\n");

		_getche();

		return studentList;


}


void ScoreManagementManager::Init()
{//Manager
	char temp = NULL;
	SELECT inputData = SELECT::NONE;

	//STUDENT* student = NULL;


	LinkedList* studentList = nullptr;
	FileIO* fileIO = new FileIO;



	while (inputData != SELECT::EXIT)
	{

		char name[25];

		system("cls");
		printf("\n1.생성\n2.데이터 삽입\n3.데이터 삭제\n4.데이터 검색 및 수정\n5.데이터 저장\n6.데이터 로드\n7.데이터 열람\n8.샘플 데이터 생성\n0.종료\n");

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
			printf("삭제할 이름 입력 : ");
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

bool ScoreManagementManager::isListEmpty(LinkedList* LL)
{
	if (!LL)
	{
		printf("학생 테이블을 만드시오\n");
		_getche();
		return true;
	}
	

	return false;
}



int main()
{
	ScoreManagementManager scoreManager;
	scoreManager.Init();

}
