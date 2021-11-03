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