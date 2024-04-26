/*
 * Auto-generated using Ion Haken Codegen - https://github.com/ionhaken/
 */
#include <./TestObjectStore.generated.h>
TestObjectStore::TestObjectStore()
{
	mBuffer = nullptr;
	mCapacity = 1000000;
	ResizeAndCopyBuffer(mCapacity, *this);
	SetName("TestObjectStore");
}

TestObjectStore::~TestObjectStore()
{
	Clear();
	ion::GlobalAllocator<uint8_t> allocator;
	allocator.deallocate(mBuffer.Get(), BufferSize(mCapacity));
}
void TestObjectStore::ResizeBuffer(uint32_t capacity)
{
	ion::GlobalAllocator<uint8_t> allocator;
	auto* oldBuffer = mBuffer.Get();
	auto oldCapacity = mCapacity;
	uint32_t itemCount = mIndexPool.Max() - 1;
	mBuffer = allocator.allocate(BufferSize(capacity));
	uint8_t* pos = mBuffer.Get();
	{
		pos = pos + 0;
		uintptr_t offset = reinterpret_cast<uintptr_t>(pos) % alignof(G0);
		mG0.Replace(ion::AssumeAligned(reinterpret_cast<G0*>(pos + (alignof(G0) - offset))), itemCount);
	}
	{
		pos = pos + 0 + sizeof(G0)*capacity + alignof(G0);
		uintptr_t offset = reinterpret_cast<uintptr_t>(pos) % alignof(G1);
		mG1.Replace(ion::AssumeAligned(reinterpret_cast<G1*>(pos + (alignof(G1) - offset))), itemCount);
	}
	{
		pos = pos + 0 + sizeof(G1)*capacity + alignof(G1);
		uintptr_t offset = reinterpret_cast<uintptr_t>(pos) % alignof(G2);
		mG2.Replace(ion::AssumeAligned(reinterpret_cast<G2*>(pos + (alignof(G2) - offset))), itemCount);
	}
	{
		pos = pos + 0 + sizeof(G2)*capacity + alignof(G2);
		uintptr_t offset = reinterpret_cast<uintptr_t>(pos) % alignof(G3);
		mG3.Replace(ion::AssumeAligned(reinterpret_cast<G3*>(pos + (alignof(G3) - offset))), itemCount);
	}
	mCapacity = capacity;
	allocator.deallocate(oldBuffer, BufferSize(oldCapacity));
}
void TestObjectStore::ResizeAndCopyBuffer(uint32_t capacity, [[maybe_unused]] const TestObjectStore& other)
{
	auto* oldBuffer = mBuffer.Get();
	auto oldCapacity = mCapacity;
	uint32_t itemCount = mIndexPool.Max();
	uint32_t otherItemCount = other.mIndexPool.Max();
	ion::GlobalAllocator<uint8_t> allocator;
	mBuffer = allocator.allocate(BufferSize(capacity));
	uint8_t* pos = mBuffer.Get();
	{
		pos = pos + 0;
		uintptr_t offset = reinterpret_cast<uintptr_t>(pos) % alignof(G0);
		mG0.Reset(itemCount, ion::AssumeAligned(reinterpret_cast<G0*>(pos + (alignof(G0) - offset))));
		mG0.CreateFrom(other.mG0.Get(), otherItemCount);
	}
	{
		pos = pos + 0 + sizeof(G0)*capacity + alignof(G0);
		uintptr_t offset = reinterpret_cast<uintptr_t>(pos) % alignof(G1);
		mG1.Reset(itemCount, ion::AssumeAligned(reinterpret_cast<G1*>(pos + (alignof(G1) - offset))));
		mG1.CreateFrom(other.mG1.Get(), otherItemCount);
	}
	{
		pos = pos + 0 + sizeof(G1)*capacity + alignof(G1);
		uintptr_t offset = reinterpret_cast<uintptr_t>(pos) % alignof(G2);
		mG2.Reset(itemCount, ion::AssumeAligned(reinterpret_cast<G2*>(pos + (alignof(G2) - offset))));
		mG2.CreateFrom(other.mG2.Get(), otherItemCount);
	}
	{
		pos = pos + 0 + sizeof(G2)*capacity + alignof(G2);
		uintptr_t offset = reinterpret_cast<uintptr_t>(pos) % alignof(G3);
		mG3.Reset(itemCount, ion::AssumeAligned(reinterpret_cast<G3*>(pos + (alignof(G3) - offset))));
		mG3.CreateFrom(other.mG3.Get(), otherItemCount);
	}
	mCapacity = capacity;
	if (oldBuffer)
	{
		allocator.deallocate(oldBuffer, BufferSize(oldCapacity));
	}
}
void TestObjectStore::CopyBuffer(const TestObjectStore& other)
{
	uint32_t itemCount = mIndexPool.Max();
	uint32_t otherItemCount = other.mIndexPool.Max();
	{
		mG0.CopyFrom(other.mG0.Get(), otherItemCount, itemCount);
	}
	{
		mG1.CopyFrom(other.mG1.Get(), otherItemCount, itemCount);
	}
	{
		mG2.CopyFrom(other.mG2.Get(), otherItemCount, itemCount);
	}
	{
		mG3.CopyFrom(other.mG3.Get(), otherItemCount, itemCount);
	}
}
void TestObjectStore::Clear()
{
	uint32_t itemCount = mIndexPool.Max();
	mG0.Clear(itemCount);
	mG1.Clear(itemCount);
	mG2.Clear(itemCount);
	mG3.Clear(itemCount);
}
