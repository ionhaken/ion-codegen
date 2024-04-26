/*
 * Auto-generated using Ion Haken Codegen - https://github.com/ionhaken/
 */
#pragma once
#include <ion/database/DBComponentStore.h>
#include <ion/util/Hasher.h>
class TestNamedObjectId : public ion::ComponentId<uint32_t>
{
public:
	friend class TestNamedObjectStore;
	friend class ion::ComponentStore<uint32_t>;
	constexpr TestNamedObjectId() : ion::ComponentId<uint32_t>() {}
private:
	#if ION_COMPONENT_VERSION_NUMBER
	constexpr TestNamedObjectId(const uint32_t index, const uint32_t version) : ion::ComponentId<uint32_t>(index, version) {}
	#else
	constexpr TestNamedObjectId(const uint32_t index) : ion::ComponentId<uint32_t>(index) {}
	#endif
};

namespace ion
{
	template<>
	inline size_t Hasher<::TestNamedObjectId>::operator() (const ::TestNamedObjectId& key) const
	{
		return Hasher<uint32_t>()(key.GetIndex());
	}
}
class TestObjectId : public ion::ComponentId<uint32_t>
{
public:
	friend class TestObjectStore;
	friend class ion::ComponentStore<uint32_t>;
	constexpr TestObjectId() : ion::ComponentId<uint32_t>() {}
private:
	#if ION_COMPONENT_VERSION_NUMBER
	constexpr TestObjectId(const uint32_t index, const uint32_t version) : ion::ComponentId<uint32_t>(index, version) {}
	#else
	constexpr TestObjectId(const uint32_t index) : ion::ComponentId<uint32_t>(index) {}
	#endif
};

namespace ion
{
	template<>
	inline size_t Hasher<::TestObjectId>::operator() (const ::TestObjectId& key) const
	{
		return Hasher<uint32_t>()(key.GetIndex());
	}
}
class TestObjectFlatId : public ion::ComponentId<uint32_t, 0>
{
public:
	friend class TestObjectFlatStore;
	friend class ion::ComponentStore<uint32_t>;
	constexpr TestObjectFlatId() : ion::ComponentId<uint32_t, 0>() {}
private:
	#if ION_COMPONENT_VERSION_NUMBER
	constexpr TestObjectFlatId(const uint32_t index, const uint32_t version) : ion::ComponentId<uint32_t, 0>(index, version) {}
	#else
	constexpr TestObjectFlatId(const uint32_t index) : ion::ComponentId<uint32_t, 0>(index) {}
	#endif
};

namespace ion
{
	template<>
	inline size_t Hasher<::TestObjectFlatId>::operator() (const ::TestObjectFlatId& key) const
	{
		return Hasher<uint32_t>()(key.GetIndex());
	}
}
