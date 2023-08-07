#include <AndrewEngine/Inc/AndrewEngine.h>


using namespace AndrewEngine;
using namespace AndrewEngine::Core;


class Student
{
public:
    Student() = default;

    void SetName(const std::string& name)
    {
        mName = name;
    }

    void SetGrade(int classMark)
    {
        mClassMark = classMark;
    }

private:
    std::string mName;
    int mClassMark;
};


int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    TypeAllocator studentPool = TypeAllocator<Student>("StudentPool", 100);

    Student* a = studentPool.New();
    Student* b = studentPool.New();


    a->SetName("Andrew");
    b->SetName("Derek");

    a->SetGrade(90);
    b->SetGrade(100);

    studentPool.Delete(a);
    studentPool.Delete(b);
    return 0;
}