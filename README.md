## Laborator 4 - IEP

### Item 4

All members of these classes should be initialized before they are used. 

For the Toy class, the "name" member is initialized manually when it is declared (so it has a 
default value).  Also this member value can be changed with a function or when a new Toy object 
is created using a constructor with parameters and also an initializaton list, because the members of an
object are initialized before the body of a constructor is entered. 


### Item 5
To know exactly which constructor is used, we added a print statement inside all constructors / operators / destructors.


### Item 6
For the MinAgeToy class we disallow the use of COPY constructor by declaring the method private and
without any implementation. Another method would be signature_function = delete or to use the base class
Uncopyable.


### Item 10
For all assignment operators of this project, it was added a return reference to * this (in this project we only have copy assignment operators).


### Item 11
Inside all copy assignment operators within this project, the assignment to self was handled by checking if the object we want to be copied isn't the object itself, and if it's the case we return a reference to this before the actual copy is done.


### Item 12
Inside the copy assignment operator of the derived class was introduced a new line of code which calls also the copy assignment operator of the base class, to make sure that all parts of the object are copied.


### Item 13
I used two types of object in order to manage the resources: unique_ptr and shared_ptr. The main difference between these two types of objects is the fact that only one unique_ptr can point to 
a resource, but multiple shared_ptrs can point to the same resource. The resource is deleted (by the destructor of the smart pointer) when there is no longer a smart pointer pointing at it.


### Item 14
For my Lock class, I decided to prohibit the copy of a RAII object by using the Uncopyable class.