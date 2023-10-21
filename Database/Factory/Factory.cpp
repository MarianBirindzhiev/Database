#include "Factory.h"

///Returns a reference to the Factory instance.
///This implementation follows the Singleton pattern, where a single instance of Factory is created and accessed globally.
///The instance is created only once, and subsequent calls to this function return the same instance.
Factory& Factory::getFactory()
{
	static Factory theFactory;
	return theFactory;
}

///Creates a new Column object based on the given type.
///- type: The type of column to create.
///  - If type is "int", an IntColumn object is created and returned.
///  - If type is "string", a StringColumn object is created and returned.
///  - If type is "float", a FloatColumn object is created and returned.
///  - If the type is not recognized, nullptr is returned.
Column* Factory::createColumn(const std::string& type)
{
	if (type == "int")
    {
		Column* intColumn = new(std::nothrow)IntColumn();
        if(intColumn == nullptr)
            throw std::bad_alloc();
        
        return intColumn;

    }
	if (type == "string")
	{
		Column* stringColumn = new(std::nothrow)StringColumn();
        if(stringColumn == nullptr)
            throw std::bad_alloc();
        
        return stringColumn;

    }
	if (type == "float")
	{
		Column* floatColumn = new(std::nothrow)FloatColumn();
        if(floatColumn == nullptr)
            throw std::bad_alloc();
        
        return floatColumn;

    }

	return nullptr;
}
