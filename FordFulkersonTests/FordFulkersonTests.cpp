#include "pch.h"
#include "CppUnitTest.h"
#include "..\FordFulkerson\FordFulkerson.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FordFulkersonTests
{
	TEST_CLASS(FordFulkersonTests)
	{
	public:

		TEST_METHOD(graphTest)
		{
			Graph actualGraph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			Assert::AreEqual(actualGraph.getNumOfVertices(), 6);
			Assert::AreEqual(actualGraph.getWeight(0, 1), 3);
			Assert::AreEqual(actualGraph.getWeight(3, 5), 2);
		}

		TEST_METHOD(graphCopyTest)
		{
			Graph expectedGraph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			Graph actualGraph(expectedGraph);
			Assert::AreEqual(actualGraph.getNumOfVertices(), expectedGraph.getNumOfVertices());
			Assert::AreEqual(actualGraph.getWeight(0, 1), expectedGraph.getWeight(0, 1));
			Assert::AreEqual(actualGraph.getWeight(3, 5), expectedGraph.getWeight(3, 5));
		}

		TEST_METHOD(getWeghtTest)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			Assert::AreEqual(graph.getWeight(0, 5), 0);
			Assert::AreEqual(graph.getWeight(4, 5), 3);
		}

		TEST_METHOD(setWeghtTest)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			graph.setWeight(0, 5, 10);
			graph.setWeight(4, 5, 9);
			Assert::AreEqual(graph.getWeight(0, 5), 10);
			Assert::AreEqual(graph.getWeight(4, 5), 9);
		}

		TEST_METHOD(getVertexByIdTest)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			Assert::IsTrue(graph.getVertexById(4) == "R");
			Assert::IsTrue(graph.getVertexById(1) == "O");
		}

		TEST_METHOD(getVertexIdTest)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			Assert::AreEqual(graph.getVertexId("R"), 4);
			Assert::AreEqual(graph.getVertexId("O"), 1);
		}

		TEST_METHOD(getNumOfVerticesTest)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			Assert::AreEqual(graph.getNumOfVertices(), 6);
		}

		TEST_METHOD(updateNetTest)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			vector<int> path = { -1, 0, 0, 1, 2, 3 };
			graph.updateNet(0, 5, 2, path);
			Assert::AreEqual(graph.getWeight(3, 5), 0);
			Assert::AreEqual(graph.getWeight(1, 3), 1);
			Assert::AreEqual(graph.getWeight(0, 1), 1);
		}

		TEST_METHOD(findFlowByPathTest)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			vector<int> path = { -1, 0, 0, 1, 2, 3 };
			int actualFlow = graph.findFlowByPath(0, 5, path);
			Assert::AreEqual(actualFlow, 2);
		}

		TEST_METHOD(isThereFlowTests)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			vector<int> actualPath;
			vector<int> expectedPath = { -1, 0, 0, 1, 2, 3 };
			Assert::IsTrue(isThereFlow(graph, 0, 5, actualPath));
			Assert::IsTrue(actualPath == expectedPath);
		}

		TEST_METHOD(fordFulkersonTest)
		{
			Graph graph("S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3\n");
			Assert::AreEqual(fordFulkerson(graph, "S", "T"), 5);
		}
	};
}
