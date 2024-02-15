#include <iostream>

template <typename T> class SmartPointer {
	T* ptr = nullptr;
	int* numRef;
public:
	T* getPtr() const {
		return ptr;
	}
	int* getRef() const {
		return numRef;
	}
	void incRef(){
		(*numRef)++;
		std::cout<<"Incremented " << ptr << " usage to " << *numRef << "\n";
	}
	void decRef(){
		(*numRef)--;
		std::cout<<"Decremented " << ptr << " usage to " << *numRef << "\n";
	}
	SmartPointer(SmartPointer<T>& value){
		this->numRef = value.getRef();
		this->ptr = value.getPtr();
		incRef();
	}
	SmartPointer(T* value){
		ptr = value;
		numRef = new int(0);
		incRef();
	}
	~SmartPointer(){
		decRef();
		if(*numRef == 0){
			std::cout<<" Freeing mem " << ptr << ", was " << *ptr << "\n";
			delete ptr;
			delete numRef;
			ptr = nullptr;
		}
	}

	SmartPointer<T>& operator=(SmartPointer<T>& value){
		// Reassign to itself, no op
		if(&value == this)
			return *this;

		if(*getRef() == 1){
			std::cout<<"Reassigning " << ptr << " to " << value.getPtr() << "\n"
				<< " And freeing mem " << ptr << ", was " << *ptr << "\n";
			delete ptr;
			delete numRef;

			ptr = value.getPtr();
			value.incRef();
			numRef = value.getRef();
		} else {
			// Dunno how to deal with dangling pointers
			std::cout<<"Can't reassign because pointer was shared\n"
				<< " And I can't reassign those pointers to the new address\n"
				<< " Giving up\n";
		}

		return *this;
	}
};

int main(){
	std::cout<< "### Starting program ###" << std::endl;
	std::cout<< std::endl << "### Outer scope ###" << std::endl;
	SmartPointer<int> num(new int(4));
	std::cout<< std::endl << "### Inner scope ###" << std::endl;
	{
		num = num;
		// Uncomment to test dangling pointer
		SmartPointer<int> num2 = num;
		SmartPointer<int> num3(new int(10));
		//num = num3;
		std::cout<< std::endl << "### Outer scope ###" << std::endl;
	}
	std::cout<< std::endl << "### Exiting program ###" << std::endl;
	return 0;
}
