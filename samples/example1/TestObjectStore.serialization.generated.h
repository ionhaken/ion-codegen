/*
 * Auto-generated using Ion Haken Codegen - https://github.com/ionhaken/
 */
#pragma once
namespace serialization
{
	bool Serialize(const ion::Vector<TestObjectId>& ids, const TestObjectStore& store, ion::JSONArrayWriter& data)
	{
		bool isOk = true;
		ion::ForEach(ids, [&](const auto& id)
		{
			ion::JSONStructWriter arrElem(data);
			arrElem.mContext = data.mContext;
			ConstTestObjectComponent c(id, store);
			isOk &= serialization::Serialize<uint32_t>(c.GetTestValue1(), "testValue1", arrElem);
			isOk &= serialization::Serialize<uint16_t>(c.GetTestValue2(), "testValue2", arrElem);
			isOk &= serialization::Serialize<uint8_t>(c.GetTestValue3(), "testValue3", arrElem);
			isOk &= serialization::Serialize<std::vector<TestData>>(c.GetTestValue4(), "testValue4", arrElem);
			serialization::SerializeFinal(id, store, arrElem);
		});
		return isOk;
	}
	
	bool Deserialize(ion::Vector<TestObjectId>& ids, TestObjectStore& store, const ion::JSONArrayReader& data)
	{
		if (!data.IsValid())
		{
			return false;
		}
		bool isOk = true;
		ids.AddMultiple(data.Size(), [&](size_t index)
		{
			ion::JSONStructReader arrElem(data, index);
			arrElem.mContext = data.mContext;
			uint32_t aTestValue1;
			isOk &= serialization::Deserialize<uint32_t>(aTestValue1, "testValue1", arrElem);
			uint16_t aTestValue2;
			isOk &= serialization::Deserialize<uint16_t>(aTestValue2, "testValue2", arrElem);
			uint8_t aTestValue3;
			isOk &= serialization::Deserialize<uint8_t>(aTestValue3, "testValue3", arrElem);
			std::vector<TestData> aTestValue4;
			isOk &= serialization::Deserialize<std::vector<TestData>>(aTestValue4, "testValue4", arrElem);
			auto id = store.Create(aTestValue1, aTestValue2, aTestValue3, aTestValue4);
			serialization::DeserializeFinal(id, store, arrElem);
			return id;
		});
		return isOk;
	}
	
}
