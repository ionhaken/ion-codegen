#include <ion/time/Clock.h>

#include "TestNamedObjectStore.generated.h"
#include "TestObjectFlatStore.generated.h"
#include "TestObjectStore.generated.h"
#include <ion/core/Engine.h>
#include <ion/string/StringFormatter.h>

#ifdef _DEBUG
static constexpr size_t numItems = 10000;
#else
static constexpr size_t numItems = 1000000;
#endif
static constexpr size_t holeSize = 100;

void TestTestObject()
{
	std::vector<TestObjectId> ids;
	ids.reserve(numItems);

	ion::RunningTimerUs timer;
	TestObjectStore* store = new TestObjectStore();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		ids.push_back(store->Create(1, 2, 3, std::vector<TestData>()));
	}

	ION_LOG_INFO("Object store fill time:" << timer.ElapsedSeconds());
	timer.Reset();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		auto testObjectSrc(store->Get(ids[numItems - i - 1]));
		auto testObjectDst(store->Get(ids[i]));
		testObjectDst.SetTestValue2(testObjectSrc.GetTestValue1());
	}
	ION_LOG_INFO("Object store read&write time:" << timer.ElapsedSeconds());
	{
		for (uint32_t i = 0; i < numItems; i++)
		{
			if (i % holeSize != 0)
			{
				store->Delete(ids[i]);
			}
		}

		timer.Reset();
		for (uint32_t i = 0; i < numItems; i += holeSize)
		{
			auto testObjectSrc(store->Get(ids[numItems - i - holeSize]));
			auto testObjectDst(store->Get(ids[i]));
			testObjectDst.SetTestValue2(testObjectSrc.GetTestValue1());
		}
		ION_LOG_INFO("Object store read&write (data with holes) time:" << timer.ElapsedSeconds());
	}

	timer.Reset();
	delete store;
	ION_LOG_INFO("Object store clear time:" << timer.ElapsedSeconds());
	
}

void TestTestObjectFlat()
{
	std::vector<TestObjectFlatId> ids;
	ids.reserve(numItems);

	ion::RunningTimerUs timer;
	TestObjectFlatStore* store = new TestObjectFlatStore();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		ids.push_back(store->Create(1, 2, 3, std::vector<TestData>()));
	}

	ION_LOG_INFO("Object flat store fill time:" << timer.ElapsedSeconds());
	timer.Reset();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		auto testObjectSrc(store->Get(ids[numItems - i - 1]));
		auto testObjectDst(store->Get(ids[i]));
		testObjectDst.SetTestValue2(testObjectSrc.GetTestValue1());
	}
	
	ION_LOG_INFO("Object flat store read&write time:" << timer.ElapsedSeconds());
	{
		for (uint32_t i = 0; i < numItems; i++)
		{
			if (i % holeSize != 0)
			{
				store->Delete(ids[i]);
			}
		}

		timer.Reset();
		for (uint32_t i = 0; i < numItems; i += holeSize)
		{
			auto testObjectSrc(store->Get(ids[numItems - i - holeSize]));
			auto testObjectDst(store->Get(ids[i]));
			testObjectDst.SetTestValue2(testObjectSrc.GetTestValue1());
		}
		ION_LOG_INFO("Object flat store read&write (data with holes) time:" << timer.ElapsedSeconds());
	}
	timer.Reset();
	delete store;
	ION_LOG_INFO("Object flat store clear time:" << timer.ElapsedSeconds());
}

void TestTestNamedObject()
{
	std::vector<TestNamedObjectId> ids;
	ids.reserve(numItems);

	ion::RunningTimerUs timer;
	TestNamedObjectStore* store = new TestNamedObjectStore();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		ion::StackStringFormatter<1024> str;
		str.Format("unique name %u", i);
		ids.push_back(store->Create(1, 2, 3, std::vector<TestData>(), i, str.CStr(), str.Length()));
	}

	ION_LOG_INFO("Named Object store fill time:" << timer.ElapsedSeconds());
	timer.Reset();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		auto testObjectSrc(store->Get(ids[numItems - i - 1]));
		auto testObjectDst(store->Get(ids[i]));
		testObjectDst.SetTestValue2(testObjectSrc.GetTestValue1());
	}
	ION_LOG_INFO("Named Object store read&write time:" << timer.ElapsedSeconds());
	timer.Reset();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		TestNamedObjectId id = store->FindUniqueId(i);
		auto testObjectSrc(store->Get(id));
		if (ids[i] != id)
		{
			auto testObjectDst(store->Get(ids[i]));
			testObjectDst.SetTestValue2(testObjectSrc.GetTestValue1());
		}
	}
	ION_LOG_INFO("Named Object store lookup&read&write time:" << timer.ElapsedSeconds());
	timer.Reset();
	delete store;
	ION_LOG_INFO("Named Object store clear time:" << timer.ElapsedSeconds());
}

void ReferenceStructOfArrays()
{
	struct RefSoA
	{
		ion::Vector<uint32_t> mTestValue1;
		ion::Vector<uint16_t> mTestValue2;
		ion::Vector<uint8_t> mTestValue3;
		ion::Vector<std::vector<TestData>> mTestData;
	};

	std::vector<uint32_t> ids;
	ids.reserve(numItems);

	ion::RunningTimerUs timer;
	RefSoA* store = new RefSoA();

	store->mTestValue1.Reserve(numItems);
	store->mTestValue2.Reserve(numItems);
	store->mTestValue3.Reserve(numItems);
	store->mTestData.Reserve(numItems);

	for (uint32_t i = 0; i < numItems; ++i)
	{
		store->mTestValue1.AddKeepCapacity(1);
		store->mTestValue2.AddKeepCapacity(2);
		store->mTestValue3.AddKeepCapacity(3);
		store->mTestData.EmplaceKeepCapacity(std::vector<TestData>());
		ids.push_back(i);
	}

	ION_LOG_INFO("Reference SoA fill time:" << timer.ElapsedSeconds());
	timer.Reset();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		store->mTestValue2[ids[i]] = store->mTestValue1[ids[numItems - i - 1]];
	}
	ION_LOG_INFO("Reference SoA read&write time:" << timer.ElapsedSeconds());

	timer.Reset();
	delete store;
	ION_LOG_INFO("Reference SoA store clear time:" << timer.ElapsedSeconds());
}

void ReferenceArrayOfStructs()
{
	struct RefAoS
	{
		uint32_t mTestValue1;
		uint16_t mTestValue2;
		uint8_t mTestValue3;
		std::vector<TestData> mTestData;
	};

	std::vector<uint32_t> ids;
	ids.reserve(numItems);

	ion::RunningTimerUs timer;
	ion::Vector<RefAoS> store;

	store.Reserve(numItems);

	for (uint32_t i = 0; i < numItems; ++i)
	{
		store.EmplaceKeepCapacity(RefAoS{1, 2, 3, std::vector<TestData>()});
		ids.push_back(i);
	}

	ION_LOG_INFO("Reference AoS fill time:" << timer.ElapsedSeconds());
	timer.Reset();

	for (uint32_t i = 0; i < numItems; ++i)
	{
		store[ids[i]].mTestValue2 = store[ids[numItems - i - 1]].mTestValue1;
	}
	ION_LOG_INFO("Reference AoS read&write time:" << timer.ElapsedSeconds());

	timer.Reset();
	store.Clear();
	store.ShrinkToFit();
	ION_LOG_INFO("Reference AoS store clear time:" << timer.ElapsedSeconds());
}

int main()
{
	ion::Engine e;

	ION_LOG_INFO("--- Store example1")
	ION_LOG_INFO("");
	ION_LOG_INFO("Store asserts enabled:" << (ION_ASSERTS_ENABLED ? "true" : "false"));
	ION_LOG_INFO("Store version numbers enabled:" << (ION_COMPONENT_VERSION_NUMBER ? "true" : "false"));
	ION_LOG_INFO("");
	ION_LOG_INFO("--- Store vs SoA vs AoS")
	
	TestTestObject(); // store with lazy layout. should match SoA in access speed
	
	TestTestObjectFlat(); // store with remapped layout. slower than SoA as this use case does not benefit from flat layout

	ReferenceStructOfArrays();
	ReferenceArrayOfStructs(); // should be slowest to access

	ION_LOG_INFO("--- Store with reverse lookups")
	TestTestNamedObject();
}
