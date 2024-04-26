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
#include <ion/util/MultiData.h>
#include <TestData.h>
#include <vector>
class TestNamedObjectComponent;
class ConstTestNamedObjectComponent;
class TestNamedObjectStore : public ion::ComponentStore<uint32_t>
{
public:
	using ComponentType = ion::ManualComponent;
	friend class TestNamedObjectId;
	friend class TestNamedObjectComponent;
	friend class ConstTestNamedObjectComponent;
	TestNamedObjectStore();
	
	~TestNamedObjectStore();
	inline TestNamedObjectComponent Get(const TestNamedObjectId& id);
	
	inline ConstTestNamedObjectComponent GetConst(const TestNamedObjectId& id) const;
	
	TestNamedObjectId Create(const uint32_t& aTestValue1, const uint16_t& aTestValue2, const uint8_t& aTestValue3, const std::vector<TestData>& aTestValue4, const uint32_t& aUniqueId, const char* aUniqueName, uint8_t aUniqueNameSize)
	{
		LockProtection();
		auto lastIndex = mIndexPool.Max();
		auto index = mIndexPool.Reserve();
		ION_ASSERT(index < 1000000, "Invalid index:" << index);
		ResizeProtection(index);
		bool isReverseMapDirty = false;
		if (index != lastIndex)
		{
			AssignInternal(index, aTestValue1, aTestValue2, aTestValue3, aTestValue4, aUniqueId);
		}
		else
		{
			if (mCapacity == index)
			{
				isReverseMapDirty = ResizeBuffer(ion::SafeRangeCast<uint32_t>(ion::Min(size_t(index)*2, size_t(1000000))));
			}
			CreateInternal(index, aTestValue1, aTestValue2, aTestValue3, aTestValue4, aUniqueId);
		}
		{
			auto res = mDynamicData.mUniqueName.Add(aUniqueName, aUniqueNameSize);
			isReverseMapDirty |= res.isDirty;
			mG2[index].mUniqueName = res.pos;
		}
		if (isReverseMapDirty)
		{
			mUniqueNameToIndex.Clear();
			auto list = mIndexPool.CreateUsedIdList();
			for (auto iter = list.Begin(); iter != list.End(); ++iter)
			{
				if (*iter != index)
				{
					ION_ASSERT(mUniqueNameToIndex.Lookup(mDynamicData.mUniqueName.Get(mG2[*iter].mUniqueName)) == nullptr, "Data is not unique");
					mUniqueNameToIndex.Insert(mDynamicData.mUniqueName.Get(mG2[*iter].mUniqueName), *iter);
				}
			}
		}
		CreateReverseMapping(index);
		#if ION_COMPONENT_VERSION_NUMBER
		auto version = GetVersion(index);
		#endif
		UnlockProtection();
		#if ION_COMPONENT_VERSION_NUMBER
		return TestNamedObjectId(index, version);
		#else
		return TestNamedObjectId(index);
		#endif
	}
	
	TestNamedObjectId RawIndexToId(uint32_t index) const
	{
		#if ION_COMPONENT_VERSION_NUMBER
		return TestNamedObjectId(index, GetVersion(index));
		#else
		return (index);
		#endif
	}
	
	// Gets component with given value. Behaviour is undefined if component is not found
	TestNamedObjectId GetUniqueId(const uint32_t& aUniqueId) const
	{
		const auto index = mUniqueIdToIndex[aUniqueId];
		#if ION_COMPONENT_VERSION_NUMBER
		return TestNamedObjectId(index, GetVersion(index));
		#else
		return (index);
		#endif
	}
	
	// Finds component with given value. Returns invalid component if component is not found
	TestNamedObjectId FindUniqueId(const uint32_t& aUniqueId) const
	{
		auto index = mUniqueIdToIndex.Lookup(aUniqueId);
		#if ION_COMPONENT_VERSION_NUMBER
		return index != nullptr ? TestNamedObjectId(*index, GetVersion(*index)) : TestNamedObjectId();
		#else
		return index != nullptr ? TestNamedObjectId(*index) : TestNamedObjectId();
		#endif
	}
	
	// Gets component with given value. Behaviour is undefined if component is not found
	TestNamedObjectId GetUniqueName(const ion::MultiData<char, uint32_t> aUniqueName) const
	{
		const auto index = mUniqueNameToIndex[aUniqueName];
		#if ION_COMPONENT_VERSION_NUMBER
		return TestNamedObjectId(index, GetVersion(index));
		#else
		return (index);
		#endif
	}
	
	// Finds component with given value. Returns invalid component if component is not found
	TestNamedObjectId FindUniqueName(const ion::MultiData<char, uint32_t> aUniqueName) const
	{
		auto index = mUniqueNameToIndex.Lookup(aUniqueName);
		#if ION_COMPONENT_VERSION_NUMBER
		return index != nullptr ? TestNamedObjectId(*index, GetVersion(*index)) : TestNamedObjectId();
		#else
		return index != nullptr ? TestNamedObjectId(*index) : TestNamedObjectId();
		#endif
	}
	
	void Delete(const TestNamedObjectId& anId)
	{
		ION_ASSERT(anId.GetIndex() < 1000000, "Invalid index:" << anId.GetIndex());
		LockProtection();
		auto index = anId.GetIndex();
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << GetVersion(anId.GetIndex()));
		#endif
		mDynamicData.mUniqueName.Remove(mG2[index].mUniqueName);
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
	TestNamedObjectStore(const TestNamedObjectStore& other)
	:
	mDynamicData(other.mDynamicData)
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
	const TestNamedObjectStore& operator=(const TestNamedObjectStore& other)
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
	void CreateInternal(const uint32_t index, const uint32_t& aTestValue1, const uint16_t& aTestValue2, const uint8_t& aTestValue3, const std::vector<TestData>& aTestValue4, const uint32_t& aUniqueId)
	{
		mData.mUniqueId.Insert(index, (aUniqueId));
		mG0.Insert(index, (G0{(aTestValue1)}));
		mG1.Insert(index, (G1{(aTestValue2)}));
		mG2.Insert(index, (G2{(0), (aTestValue3)}));
		mG3.Insert(index, (G3{(aTestValue4)}));
	}
	
	void AssignInternal(const uint32_t index, const uint32_t& aTestValue1, const uint16_t& aTestValue2, const uint8_t& aTestValue3, const std::vector<TestData>& aTestValue4, const uint32_t& aUniqueId)
	{
		mData.mUniqueId[index] = (aUniqueId);
		mG2[index].mUniqueName = 0;
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
		RemoveReverseMapping(index);
		mIndexPool.Free(index);
	}
	bool ResizeBuffer(uint32_t capacity);
	void ResizeAndCopyBuffer(uint32_t capacity, [[maybe_unused]] const TestNamedObjectStore& other);
	void CreateReverseMapping(const uint32_t index)
	{
		ION_ASSERT(mUniqueIdToIndex.Lookup(mData.mUniqueId[index]) == nullptr, "Data is not unique");
		mUniqueIdToIndex.Insert(mData.mUniqueId[index], index);
		ION_ASSERT(mUniqueNameToIndex.Lookup(mDynamicData.mUniqueName.Get(mG2[index].mUniqueName)) == nullptr, "Data is not unique");
		mUniqueNameToIndex.Insert(mDynamicData.mUniqueName.Get(mG2[index].mUniqueName), index);
	}
	void RemoveReverseMapping(const uint32_t index)
	{
		mUniqueIdToIndex.Remove(mData.mUniqueId[index]);
		mUniqueNameToIndex.Remove(mDynamicData.mUniqueName.Get(mG2[index].mUniqueName));
	}
	void CopyBuffer(const TestNamedObjectStore& other);
	void Clear();
	constexpr size_t BufferSize(size_t capacity) const
	{
		return 0 + sizeof(G2)*capacity + alignof(G2) + sizeof(G0)*capacity + alignof(G0) + sizeof(G1)*capacity + alignof(G1) + sizeof(G3)*capacity + alignof(G3) + sizeof(uint32_t)*capacity + alignof(uint32_t);
	}
	ion::RawBuffer<uint8_t> mBuffer;
	uint32_t mCapacity = 0;
	ion::UnorderedMap<uint32_t, uint32_t, ion::Hasher<uint32_t>> mUniqueIdToIndex;
	ion::UnorderedMap<ion::MultiData<char, uint32_t>, uint32_t, ion::MultiData<char, uint32_t>::Hasher> mUniqueNameToIndex;
	struct
	{
		ion::RawBuffer<uint32_t> mUniqueId;
	} mData;
	struct Dynamic
	{
		Dynamic() {}
		Dynamic(size_t size) : 
		mUniqueName(static_cast<uint32_t>(size))
		{}
		ion::ComponentDataVector<char, uint32_t, uint8_t> mUniqueName;
	} mDynamicData;
	struct G2
	{
		uint32_t mUniqueName;
		uint8_t mTestValue3;
	};
	ion::RawBuffer<G2> mG2;
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
	struct G3
	{
		std::vector<TestData> mTestValue4;
	};
	ion::RawBuffer<G3> mG3;
};

class ConstTestNamedObjectComponent : public ion::ComponentStoreView<const TestNamedObjectStore>
{
	ION_CLASS_NON_COPYABLE_NOR_MOVABLE(ConstTestNamedObjectComponent);
	
public:
	#if (ION_COMPONENT_VERSION_NUMBER == 0) && (ION_ASSERTS_ENABLED == 0)
	constexpr
	#endif
	ConstTestNamedObjectComponent(const TestNamedObjectId& anId, const TestNamedObjectStore& aStore) : ion::ComponentStoreView<const TestNamedObjectStore>(aStore, anId.GetIndex())
	{
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == aStore.GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << aStore.GetVersion(anId.GetIndex()));
		#endif
	}
	
	[[nodiscard]] constexpr const uint32_t& GetUniqueId() const { return mStore.mData.mUniqueId[mIndex]; }
	[[nodiscard]] inline const ion::MultiData<char, uint32_t> GetUniqueName() const { return mStore.mDynamicData.mUniqueName.Get(mStore.mG2[mIndex].mUniqueName); }
	[[nodiscard]] constexpr const uint32_t& GetTestValue1() const { return mStore.mG0[mIndex].mTestValue1; }
	[[nodiscard]] constexpr const uint16_t& GetTestValue2() const { return mStore.mG1[mIndex].mTestValue2; }
	[[nodiscard]] constexpr const uint8_t& GetTestValue3() const { return mStore.mG2[mIndex].mTestValue3; }
	[[nodiscard]] constexpr const std::vector<TestData>& GetTestValue4() const { return mStore.mG3[mIndex].mTestValue4; }
};
inline ConstTestNamedObjectComponent TestNamedObjectStore::GetConst(const TestNamedObjectId& id) const { return ConstTestNamedObjectComponent(id, *this); }


class TestNamedObjectComponent : public ion::ComponentStoreView<TestNamedObjectStore>
{
	ION_CLASS_NON_COPYABLE_NOR_MOVABLE(TestNamedObjectComponent);
	
public:
	#if (ION_COMPONENT_VERSION_NUMBER == 0) && (ION_ASSERTS_ENABLED == 0)
	constexpr
	#endif
	TestNamedObjectComponent(const TestNamedObjectId& anId, TestNamedObjectStore& aStore) : ion::ComponentStoreView<TestNamedObjectStore>(aStore, anId.GetIndex())
	{
		#if ION_COMPONENT_VERSION_NUMBER
		ION_CHECK(anId.GetVersion() == aStore.GetVersion(anId.GetIndex()),
			"Invalid version " << anId.GetVersion() << ";expected:" << aStore.GetVersion(anId.GetIndex()));
		#endif
	}
	
	[[nodiscard]] constexpr const uint32_t& GetUniqueId() const { return mStore.mData.mUniqueId[mIndex]; }
	[[nodiscard]] inline const ion::MultiData<char, uint32_t> GetUniqueName() const { return mStore.mDynamicData.mUniqueName.Get(mStore.mG2[mIndex].mUniqueName); }
	[[nodiscard]] constexpr const uint32_t& GetTestValue1() const { return mStore.mG0[mIndex].mTestValue1; }
	inline void SetTestValue1(const uint32_t& in) { mStore.mG0[mIndex].mTestValue1 = in; }
	[[nodiscard]] constexpr const uint16_t& GetTestValue2() const { return mStore.mG1[mIndex].mTestValue2; }
	inline void SetTestValue2(const uint16_t& in) { mStore.mG1[mIndex].mTestValue2 = in; }
	[[nodiscard]] constexpr const uint8_t& GetTestValue3() const { return mStore.mG2[mIndex].mTestValue3; }
	inline void SetTestValue3(const uint8_t& in) { mStore.mG2[mIndex].mTestValue3 = in; }
	[[nodiscard]] constexpr const std::vector<TestData>& GetTestValue4() const { return mStore.mG3[mIndex].mTestValue4; }
	inline void SetTestValue4(const std::vector<TestData>& in) { mStore.mG3[mIndex].mTestValue4 = in; }
};
inline TestNamedObjectComponent TestNamedObjectStore::Get(const TestNamedObjectId& id) { return TestNamedObjectComponent(id, *this); }

