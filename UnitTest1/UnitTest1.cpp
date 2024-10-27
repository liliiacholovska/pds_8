#include "pch.h"
#include "CppUnitTest.h"
#include "../pds_8/pds_8.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestStackContent)
        {
            std::ofstream testInput("testInput.txt");
            testInput << "1 2\n1 3\n2 4\n3 4\n";
            testInput.close();

            initializeGraph();
            loadGraphFromFile("testInput.txt");

            int startVertex = 1;
            dfsNumber[startVertex] = 1;
            visited[startVertex] = true;

            int expectedStack[5] = { 0 };
            expectedStack[0] = 1;

            DFS(startVertex);
        }
	};
}
