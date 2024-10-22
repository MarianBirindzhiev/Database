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

 auto createColumn = [](auto* columnPtr) -> Column* {
        if (columnPtr == nullptr) {
            throw std::bad_alloc();
        }
        return columnPtr;
    };

    if (type == "int") {
        return createColumn(new(std::nothrow) IntColumn());
    }
    if (type == "string") {
        return createColumn(new(std::nothrow) StringColumn());
    }
    if (type == "float") {
        return createColumn(new(std::nothrow) FloatColumn());
    }

    std::cerr<<"Error: Unknown column type "<< type<<'\n';
    return nullptr;
}
