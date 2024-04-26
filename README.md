Ion Haken Codegen

This code generator builds data stores which can be reconfigured without need for changing the application code. In many cases you do not know in advance what kind of data layout is optimal for you use cases as real usage will be revealed late in production. With the code generator you can change your data layout at any stage easily.


Features
--------
- Access data directly or using indices.
- Single memory block allocated per store to prevent data fragmentation
- Data version numbering to detect dangling identifiers. (#define ION_COMPONENT_VERSION_NUMBER 1)
- Race condition detection. (#define ION_ASSERTS_ENABLED 1) 
- Can generate serialization scaffoldings.


Data Model definition file
--------------------------

Data model defines data stores in JSON format as described below:


{
	"namespace" : <Name of data model namespace>,
	"model" : 
	[	
		{
			"name" 					: <Name of first store>,
			"resource"   			: <Memory resource (optional)>,
			"layout" 				: <remapped|lazy (default)>
			"indexMin"   			: <Minimum number of items in store (default 0)>, 
			"indexMax"   			: <Maximum number of items in store (mandatory to set, to define how large identifier is needed)>,
			"indexEstimate"   		: <Estimated number of items in store to reserve memory early (default 0)>,
			"stats"  				: <all|none (default)>,
			"allow_invalid_access" 	: <true|false (default)>,

			"header_includes" 		: [ <Array of header includes for generated header file (optional)> ],
			"header_includes_src" 	: [ <Array of header includes for generated source file (optional)> ],
			"reader"     			: <reader name for serialization (optional - only for serialization)>,
			"writer"     			: <writer name for serialization (optional - only for serialization)>,
			"row_reader" 			: <row reader name for serialization (optional - only for serialization)> 
			"row_writer" 			: <row writer name for serialization (optional - only for serialization)> 
			"precompiled_header"	: <Name of precompiled header (optional)
			"namespace" 			| <Name of store namespace (optional)>
			"data" : 
			[
				{
					"name" : <Name of first data element>,
					"type" : <modifiable|unique|const|transient (optional)> <type name (no space characters allowed)>,
					"group" : <group index (if not specified a unique group index)>
					"maxSize" : <Array size (default 1 - no array)>
					"reverseMap" : <copy|reference|none (default)>
				},
				{
					"name" : <Name of nth data element>,
					...
				},
			]
		},
		{
			"name" : <Name of nth store>,
			...
		}
}


layout:
	lazy - Element id equals index of data. Therefore data is non-contiquous and deleting an item will leave holes to data.  
	remapped - Element id refers to index of data. Therefore data can be kept contiquous and deleted item will be replaced with an item from end of data while indices are updated.

stats:
	all - experimental access tracking
	none - no stats
	
allow_invalid_access: 
	if enabled, first item created to the store is an item that will be accessed when using invalid store identifier.

data - optional type attributes:
	modifiable: Setter method is replaced by non-constant getter method 
	unique: As modifiable, but additionally copies are disabllowed - only moves are allowed for this type.
	const: no setter methods are generated - created item cannot be altered
	transient: no serialization
	
data - group:
	Group index of the data element. Elements with same index are ordered together. Basically, if all elements have same group index, data is AoS (array of structs) and if all elements have unique indices, data is SoA (struct of arrays). It's possible also use mix of this and have only few elements in SoA. You can omit this field to automatically have SoA.
	
data - reverseMap:
	Define reverseMap if you want to allow look ups with the data element to find item identifier.

	copy: Mapping returns by copy
	reference: Mapping returns by reference. Note: Arrays are always returned by reference
	none: No reverse mapping


Code generation
---------------

Run code generation from command line:

ion-codegen.exe <model file> <target directory>

Note that paths in generated files are relative to the current directory.


Data store application interface
--------------------------------

Create a new item

	ItemId Create(Data element 1, Data element n, ...)

Delete an item using item identifier
	
	void Delete(ItemId id)

Convert raw index to item identifier

	ItemId RawIndexToId(IndexType index) const

Get read/write accessor to an item	
	
	ItemComponent Get(ItemId id);
	ItemComponent Get(IndexType index); // Remapped layout only
	
Get read accessor to an item
	
	ConstItemComponent GetConst(ItemId id);
	ConstItemComponent GetConst(IndexType index); // Remapped layout only
	
Number of items in store.
	
	size_t Size() const

Maximum number of items in store.
	
	size_t MaxSize()

Iterating through all items when using "remapped" data layout. 

	// Since we know all indices point to a valid item, we can do this:	
	for (IndexType i = 0; i < store.Size(); ++i)
	{
		auto item(store.Get(index));
	}

