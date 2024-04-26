/*
 * Auto-generated using Ion Haken Codegen - https://github.com/ionhaken/
 */
#pragma once
#include <./ComponentModel.generated.h>
#include <ion/database/DBComponentStoreView.h>
#include <ion/database/DBComponentStore.h>
#include <ion/database/DBComponentDataVector.h>
#include <ion/database/DBComponent.h>
#include <ion/arena/ArenaVector.h>
#include <ion/arena/ArenaAllocator.h>
#include <ion/memory/AlignedAllocator.h>
#include <TestData.h>
#include <vector>
class TestObjectComponent;
class ConstTestObjectComponent;
class TestObjectStore : public ion::ComponentStore<uint32_t>
{
public:
	using ComponentType = ion::ManualComponent;
	friend class TestObjectId;
	friend class TestObjectComponent;
	friend class ConstTestObjectComponent;
	TestObjectStore();
	
	~TestObjectStore();
	inline TestObjectComponent Get(const TestObjectId& id);
	
	inline ConstTestObjectComponent GetConst(const TestObjectId& id) const;
	
	TestObjectId Create(const uint32_t& aTestValue1, const uint16_t& aTestValue2, const uint8_t& aTestValue3, const std::vector<TestData>& aTestValue4)
	{
		LockProtection();
		auto lastIndex = mIndexPool.Max();
		auto index = mIndexPool.Reserve();
		ION_ASSERT(index < 1000000, "Invalid index:" << index);
		ResizeProtection(index);
		if (index != lastIndex)
		{
			AssignInternal(index, aTestValue1, aTestValue2, aTestValue3, aTestValue4);
		}
		else
		{
			if (mCapacity == index)
			{
				ResizeBuffer(ion::SafeRangeCast<uint32_t>(ion::Min(size_t(index)*2, size_t(1000000))));
			}
			CreateInternal(index, aTestValue1, aTestValue2, aTestValue3, aTestValue4);
		}
		#if ION_COMPONENT_VERSION_NUMBER
		auto version = GetVersion(index);
		#endif
		UnlockProtection();
		#if ION_COMPONENT_VERSION_NUMBER
		return TestObjectId(index, version);
		#else
		return TestObjectId(index);
		#endif
	}
	
	TestObjectId RawIndexToId(uint32_t index) const
	{
		#if ION_COMPONENT_VERSION_NUMBER
		return TestObjectId(index, GetVersion(index));
		#else
		return (index);
		#endif
	}
	
	void Delete(const TestObjectId& anId)
	{
		ION_ASSERT(anId.GetIndex() < 1000000, "Invalid index:" << anId.GetIndex());
		LockProtection();
		auto index = anId.GetIndex();
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << GetVersion(anId.GetIndex()));
		#endif
		DeleteIndex(index);
		UnlockProtection();
	}
	[[nodiscard]] inline size_t Size() const
	{
		return mIndexPool.Size();
	}
	[[nodiscard]] static constexpr size_t MaxSize()
	{
		return 1000000;
	}
	TestObjectStore(const TestObjectStore& other)
	{
		LockProtection();
		other.LockProtection();
		CloneProtection(other);
		mBuffer = nullptr;
		ResizeAndCopyBuffer(other.mCapacity, other);
		mIndexPool = other.mIndexPool;
		UnlockProtection();
		other.UnlockProtection();
	}
	const TestObjectStore& operator=(const TestObjectStore& other)
	{
		LockProtection();
		other.LockProtection();
		CloneProtection(other);
		if (mCapacity != other.mCapacity)
		{
			ResizeAndCopyBuffer(other.mCapacity, other);
		}
		else
		{
			CopyBuffer(other);
		}
		mIndexPool = other.mIndexPool;
		UnlockProtection();
		other.UnlockProtection();
		return *this;
	}
private:
	void CreateInternal(const uint32_t index, const uint32_t& aTestValue1, const uint16_t& aTestValue2, const uint8_t& aTestValue3, const std::vector<TestData>& aTestValue4)
	{
		mG0.Insert(index, (G0{(aTestValue1)}));
		mG1.Insert(index, (G1{(aTestValue2)}));
		mG2.Insert(index, (G2{(aTestValue3)}));
		mG3.Insert(index, (G3{(aTestValue4)}));
	}
	
	void AssignInternal(const uint32_t index, const uint32_t& aTestValue1, const uint16_t& aTestValue2, const uint8_t& aTestValue3, const std::vector<TestData>& aTestValue4)
	{
		mG0[index].mTestValue1 = (aTestValue1);
		mG1[index].mTestValue2 = (aTestValue2);
		mG2[index].mTestValue3 = (aTestValue3);
		mG3[index].mTestValue4 = (aTestValue4);
	}
	
	void DeleteIndex(const uint32_t index)
	{
		#if ION_COMPONENT_VERSION_NUMBER
		IncreaseVersion(index);
		#endif
		mIndexPool.Free(index);
	}
	void ResizeBuffer(uint32_t capacity);
	void ResizeAndCopyBuffer(uint32_t capacity, [[maybe_unused]] const TestObjectStore& other);
	void CopyBuffer(const TestObjectStore& other);
	void Clear();
	constexpr size_t BufferSize(size_t capacity) const
	{
		return 0 + sizeof(G0)*capacity + alignof(G0) + sizeof(G1)*capacity + alignof(G1) + sizeof(G2)*capacity + alignof(G2) + sizeof(G3)*capacity + alignof(G3);
	}
	ion::RawBuffer<uint8_t> mBuffer;
	uint32_t mCapacity = 0;
	struct G0
	{
		uint32_t mTestValue1;
	};
	ion::RawBuffer<G0> mG0;
	struct G1
	{
		uint16_t mTestValue2;
	};
	ion::RawBuffer<G1> mG1;
	struct G2
	{
		uint8_t mTestValue3;
	};
	ion::RawBuffer<G2> mG2;
	struct G3
	{
		std::vector<TestData> mTestValue4;
	};
	ion::RawBuffer<G3> mG3;
};

class ConstTestObjectComponent : public ion::ComponentStoreView<const TestObjectStore>
{
	ION_CLASS_NON_COPYABLE_NOR_MOVABLE(ConstTestObjectComponent);
	
public:
	#if (ION_COMPONENT_VERSION_NUMBER == 0) && (ION_ASSERTS_ENABLED == 0)
	constexpr
	#endif
	ConstTestObjectComponent(const TestObjectId& anId, const TestObjectStore& aStore) : ion::ComponentStoreView<const TestObjectStore>(aStore, anId.GetIndex())
	{
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == aStore.GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << aStore.GetVersion(anId.GetIndex()));
		#endif
	}
	
	[[nodiscard]] constexpr const uint32_t& GetTestValue1() const { return mStore.mG0[mIndex].mTestValue1; }
	[[nodiscard]] constexpr const uint16_t& GetTestValue2() const { return mStore.mG1[mIndex].mTestValue2; }
	[[nodiscard]] constexpr const uint8_t& GetTestValue3() const { return mStore.mG2[mIndex].mTestValue3; }
	[[nodiscard]] constexpr const std::vector<TestData>& GetTestValue4() const { return mStore.mG3[mIndex].mTestValue4; }
};
inline ConstTestObjectComponent TestObjectStore::GetConst(const TestObjectId& id) const { return ConstTestObjectComponent(id, *this); }


class TestObjectComponent : public ion::ComponentStoreView<TestObjectStore>
{
	ION_CLASS_NON_COPYABLE_NOR_MOVABLE(TestObjectComponent);
	
public:
	#if (ION_COMPONENT_VERSION_NUMBER == 0) && (ION_ASSERTS_ENABLED == 0)
	constexpr
	#endif
	TestObjectComponent(const TestObjectId& anId, TestObjectStore& aStore) : ion::ComponentStoreView<TestObjectStore>(aStore, anId.GetIndex())
	{
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == aStore.GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << aStore.GetVersion(anId.GetIndex()));
		#endif
	}
	
	[[nodiscard]] constexpr const uint32_t& GetTestValue1() const { return mStore.mG0[mIndex].mTestValue1; }
	inline void SetTestValue1(const uint32_t& in) { mStore.mG0[mIndex].mTestValue1 = in; }
	[[nodiscard]] constexpr const uint16_t& GetTestValue2() const { return mStore.mG1[mIndex].mTestValue2; }
	inline void SetTestValue2(const uint16_t& in) { mStore.mG1[mIndex].mTestValue2 = in; }
	[[nodiscard]] constexpr const uint8_t& GetTestValue3() const { return mStore.mG2[mIndex].mTestValue3; }
	inline void SetTestValue3(const uint8_t& in) { mStore.mG2[mIndex].mTestValue3 = in; }
	[[nodiscard]] constexpr const std::vector<TestData>& GetTestValue4() const { return mStore.mG3[mIndex].mTestValue4; }
	inline void SetTestValue4(const std::vector<TestData>& in) { mStore.mG3[mIndex].mTestValue4 = in; }
};
inline TestObjectComponent TestObjectStore::Get(const TestObjectId& id) { return TestObjectComponent(id, *this); }

