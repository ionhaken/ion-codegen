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
class TestObjectFlatComponent;
class ConstTestObjectFlatComponent;
class TestObjectFlatStore : public ion::ComponentStore<uint32_t>
{
public:
	using ComponentType = ion::ManualComponent;
	friend class TestObjectFlatId;
	friend class TestObjectFlatComponent;
	friend class ConstTestObjectFlatComponent;
	TestObjectFlatStore();
	
	~TestObjectFlatStore();
	inline TestObjectFlatComponent Get(size_t idx);
	
	inline ConstTestObjectFlatComponent GetConst(size_t idx) const;
	
	inline TestObjectFlatComponent Get(const TestObjectFlatId& id);
	
	inline ConstTestObjectFlatComponent GetConst(const TestObjectFlatId& id) const;
	
	TestObjectFlatId Create(const uint32_t& aTestValue1, const uint16_t& aTestValue2, const uint8_t& aTestValue3, const std::vector<TestData>& aTestValue4)
	{
		LockProtection();
		auto index = mIndexPool.Size();
		ION_ASSERT(index < 1000000, "Invalid index:" << index);
		ResizeProtection(index);
		auto reindex = mIndexPool.Reserve();
		{
			if (mCapacity == index)
			{
				ResizeBuffer(ion::SafeRangeCast<uint32_t>(ion::Min(size_t(index)*2, size_t(1000000))));
			}
			CreateInternal(index, aTestValue1, aTestValue2, aTestValue3, aTestValue4);
		}
		mRemap[reindex] = index;
		mReverseRemap[index] = reindex;
		#if ION_COMPONENT_VERSION_NUMBER
		auto version = GetVersion(reindex);
		#endif
		UnlockProtection();
		#if ION_COMPONENT_VERSION_NUMBER
		return TestObjectFlatId(reindex, version);
		#else
		return TestObjectFlatId(reindex);
		#endif
	}
	
	void Delete(const TestObjectFlatId& anId)
	{
		ION_ASSERT(anId.GetIndex() < 1000000, "Invalid index:" << anId.GetIndex());
		LockProtection();
		ION_ACCESS_GUARD_WRITE_BLOCK(mRemapGuard);
		auto index = Remap(anId);
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << GetVersion(anId.GetIndex()));
		#endif
		DeleteIndex(index, anId.GetIndex());
		auto lastIndex = mIndexPool.Size();
		if (lastIndex != index)
		{
			Move(index, lastIndex, mReverseRemap[lastIndex]);
			mRemap[mReverseRemap[lastIndex]] = index;
			mReverseRemap[index] = mReverseRemap[lastIndex];
		}
		mG0.Erase(lastIndex);
		mG1.Erase(lastIndex);
		mG2.Erase(lastIndex);
		mG3.Erase(lastIndex);
		UnlockProtection();
	}
	TestObjectFlatId GetId(size_t index) const
	{
		auto reindex = mReverseRemap[index];
		#if ION_COMPONENT_VERSION_NUMBER
		return TestObjectFlatId(reindex, GetVersion(reindex));
		#else
		return TestObjectFlatId(reindex);
		#endif
	}
	[[nodiscard]] inline size_t Size() const
	{
		return mIndexPool.Size();
	}
	[[nodiscard]] static constexpr size_t MaxSize()
	{
		return 1000000;
	}
	TestObjectFlatStore(const TestObjectFlatStore& other)
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
	const TestObjectFlatStore& operator=(const TestObjectFlatStore& other)
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
	uint32_t Remap(const TestObjectFlatId& id) const
	{
		return mRemap[id.GetIndex()];
	}
private:
	void CreateInternal(const uint32_t index, const uint32_t& aTestValue1, const uint16_t& aTestValue2, const uint8_t& aTestValue3, const std::vector<TestData>& aTestValue4)
	{
		mG0.Insert(index, (G0{(aTestValue1)}));
		mG1.Insert(index, (G1{(aTestValue2)}));
		mG2.Insert(index, (G2{(aTestValue3)}));
		mG3.Insert(index, (G3{(aTestValue4)}));
	}
	
	void Move(const uint32_t index, const uint32_t source, const uint32_t /*reindex*/)
	{
		mG0[index].mTestValue1 = (mG0[source].mTestValue1);
		mG1[index].mTestValue2 = (mG1[source].mTestValue2);
		mG2[index].mTestValue3 = (mG2[source].mTestValue3);
		mG3[index].mTestValue4 = (mG3[source].mTestValue4);
	}
	void DeleteIndex(const uint32_t /*index*/, const uint32_t reindex)
	{
		#if ION_COMPONENT_VERSION_NUMBER
		IncreaseVersion(reindex);
		#endif
		mIndexPool.Free(reindex);
	}
	void ResizeBuffer(uint32_t capacity);
	void ResizeAndCopyBuffer(uint32_t capacity, [[maybe_unused]] const TestObjectFlatStore& other);
	void CopyBuffer(const TestObjectFlatStore& other);
	void Clear();
	constexpr size_t BufferSize(size_t capacity) const
	{
		return 0 + sizeof(G0)*capacity + alignof(G0) + sizeof(G1)*capacity + alignof(G1) + sizeof(G2)*capacity + alignof(G2) + sizeof(G3)*capacity + alignof(G3) + sizeof(uint32_t)*capacity + alignof(uint32_t) + sizeof(uint32_t)*capacity + alignof(uint32_t);
	}
	ion::RawBuffer<uint8_t> mBuffer;
	uint32_t mCapacity = 0;
	ION_ACCESS_GUARD(mRemapGuard);
	ion::RawBuffer<uint32_t> mRemap;
	ion::RawBuffer<uint32_t> mReverseRemap;
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

class ConstTestObjectFlatComponent : public ion::ComponentStoreView<const TestObjectFlatStore>
{
	ION_CLASS_NON_COPYABLE_NOR_MOVABLE(ConstTestObjectFlatComponent);
	
public:
	#if (ION_ASSERTS_ENABLED == 0)
	constexpr
	#endif
	ConstTestObjectFlatComponent(const size_t index, const TestObjectFlatStore& aStore) : ion::ComponentStoreView<const TestObjectFlatStore>(aStore, static_cast<uint32_t>(index))
	{
		ION_ACCESS_GUARD_START_READING(aStore.mRemapGuard);
	}
	
	#if (ION_COMPONENT_VERSION_NUMBER == 0) && (ION_ASSERTS_ENABLED == 0)
	constexpr
	#endif
	ConstTestObjectFlatComponent(const TestObjectFlatId& anId, const TestObjectFlatStore& aStore) : ion::ComponentStoreView<const TestObjectFlatStore>(aStore, aStore.Remap(anId))
	{
		ION_ACCESS_GUARD_START_READING(aStore.mRemapGuard);
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == aStore.GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << aStore.GetVersion(anId.GetIndex()));
		#endif
	}
	
	~ConstTestObjectFlatComponent()
	{
		ION_ACCESS_GUARD_STOP_READING(mStore.mRemapGuard);
	}
	[[nodiscard]] constexpr const uint32_t& GetTestValue1() const { return mStore.mG0[mIndex].mTestValue1; }
	[[nodiscard]] constexpr const uint16_t& GetTestValue2() const { return mStore.mG1[mIndex].mTestValue2; }
	[[nodiscard]] constexpr const uint8_t& GetTestValue3() const { return mStore.mG2[mIndex].mTestValue3; }
	[[nodiscard]] constexpr const std::vector<TestData>& GetTestValue4() const { return mStore.mG3[mIndex].mTestValue4; }
};
inline ConstTestObjectFlatComponent TestObjectFlatStore::GetConst(size_t idx) const { return ConstTestObjectFlatComponent(idx, *this); }
inline ConstTestObjectFlatComponent TestObjectFlatStore::GetConst(const TestObjectFlatId& id) const { return ConstTestObjectFlatComponent(id, *this); }


class TestObjectFlatComponent : public ion::ComponentStoreView<TestObjectFlatStore>
{
	ION_CLASS_NON_COPYABLE_NOR_MOVABLE(TestObjectFlatComponent);
	
public:
	#if (ION_ASSERTS_ENABLED == 0)
	constexpr
	#endif
	TestObjectFlatComponent(const size_t index, TestObjectFlatStore& aStore) : ion::ComponentStoreView<TestObjectFlatStore>(aStore, static_cast<uint32_t>(index))
	{
		ION_ACCESS_GUARD_START_READING(aStore.mRemapGuard);
	}
	
	#if (ION_COMPONENT_VERSION_NUMBER == 0) && (ION_ASSERTS_ENABLED == 0)
	constexpr
	#endif
	TestObjectFlatComponent(const TestObjectFlatId& anId, TestObjectFlatStore& aStore) : ion::ComponentStoreView<TestObjectFlatStore>(aStore, aStore.Remap(anId))
	{
		ION_ACCESS_GUARD_START_READING(aStore.mRemapGuard);
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == aStore.GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << aStore.GetVersion(anId.GetIndex()));
		#endif
	}
	
	~TestObjectFlatComponent()
	{
		ION_ACCESS_GUARD_STOP_READING(mStore.mRemapGuard);
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
inline TestObjectFlatComponent TestObjectFlatStore::Get(size_t idx) { return TestObjectFlatComponent(idx, *this); }
inline TestObjectFlatComponent TestObjectFlatStore::Get(const TestObjectFlatId& id) { return TestObjectFlatComponent(id, *this); }

