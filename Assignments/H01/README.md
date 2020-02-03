## Homework 1 - Basic OOP Terminology

- Taylor Mendez
- 02/04/2020
- Class: 2143 OOP

### Definitions

#### Abstraction

> The act of representing essential features without including the background detail/explanations. The principle is used to reduce complexity and allow efficient design and implementation

#### Attributes/properties

> Attributes store information about the instance. Properties are special values that are included within a class/object, usually (depending on the language being used) set using get or set method calls. These are often thought of as a special case that is "in between" a regular data member and a method

#### Class

> A user-defined type or data structure declared with keyword class that has data and functions as its members whose access is governed by the three access specifiers private, protected or public
><img src="https://ds055uzetaobb.cloudfront.net/image_optimizer/722c82aff075a14313be7fa7463f7fedad151a0a.png" width=400>

#### Class Variable

> A class variable is any variable declared with the static modifier of which a single copy exists, regardless of how many instances of the class exist

#### Composition

> The process of making one class a data member of another class. Composition is a "has a" relationship

#### Encapsulation

> Encapsulation is a process of combining data members and functions in a single unit called class
><img src="https://www.cpp.thiyagaraaj.com/cms/assets/cimages/encapsulation.png" width=400>

#### Friends

> Friend class: A friend class can access private and protected members of other class in which it is declared as friend. It is sometimes useful to allow a particular class to access private members of other class
> Friend function: A friend function can be given special grant to access private and protected members (a friend function can be a method of another class or a global function)
> Important note on friend functions and classes: (1) Friendship is not mutual (2) Friendship is not inherited

#### Inheritance

> Allows user to create a new class (derived class) from an existing class(base class). The derived class inherits all the features from the base class and can have additional features of its own

#### Instance Variable

> Instance variables are non-static variables and are declared in a class outside any method, constructor or block. As instance variables are declared in a class, these variables are created when an object of the class is created and destroyed when the object is destroyed

#### Member Variable

> In object-oriented programming, a member variable is a variable that is associated with a specific object, and accessible for all its methods

#### Method

> A method in object-oriented programming is a procedure associated with a class. A method defines the behavior of the objects that are created from the class

#### Multiple Inheritance

> Multiple inheritance is a feature of some object-oriented computer programming languages in which an object or class can inherit characteristics and features from more than one parent object or parent class

#### Object

> An instance of a class

#### Overloading

> Allows you to specify more than one definition for a function name or an operator in the same scope. An overloaded declaration is a declaration that is declared with the same name as a previously declared declaration in the same scope, except that both declarations have different arguments and different definition 

#### Polymorphism

> Polymorphism is the ability to use an operator or method in different ways. Polymorphism gives different meaning or functions to the operators or methods

#### Public/Private/Protected

> Private members are accessible within the same class in which they are declared. Protected members are accessible within the same class and within the derived/sub/child class (protected members cannot be accessed through the friend function). A public member is accessible from anywhere outside the class but within a program. You can set and get the value of public variables without any member.

#### Virtual

> A virtual function a member function which is declared within a base class and is re-defined(Overriden) by a derived class. When you refer to a derived class object using a pointer or a reference to the base class, you can call a virtual function for that object and execute the derived class’s version of the function. Virtual functions cannot be static and also cannot be a friend function of another class.
