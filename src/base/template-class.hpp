// Use Google coding stype:
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html
//

// Header file:
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Header_Files
//

// File naming:
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#File_Names
// All naming conventions:
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#General_Naming_Rules
//

// Generic rule: use comments
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Comment_Style
//

// Keep a formatting standard
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Formatting
// 

// Add header guard
#ifndef TEMPLATE_CLASS_H_
#define TEMPLATE_CLASS_H_

// Forward declarations
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Forward_Declarations
//

// #include
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Names_and_Order_of_Includes
//

// Inline functions
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Inline_Functions
//

// Use namespace only to avoid collisions
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Namespaces
//

// Type definitions
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Type_Names
// Macro definitions
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Macro_Names 
// Structures
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Structs_vs._Classes
// Enumerators
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Enumerator_Names
//

// Non-members and global functions
// Prefer namespace if used, but try to avoid
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Nonmember,_Static_Member,_and_Global_Functions
//

// Class. Only one main class per file. Nested classes can be used
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Classes
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Class_Comments
//
class TemplateClass // [ : public Base ]
					// Inheritance:
					// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Inheritance
{

	// Make data members private, and provide access to them through accessor functions as needed
	// Exception: static const data
	// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Access_Control
	//

	// Declare data members, nested classes, methods, constructors, destructors.
	// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Declaration_Order
	//

	// Your class definition should start with its public: section,
	// followed by its protected: section
	// and then its private: section.
	// If any of these sections are empty, omit them.
	//

	// Within each section, the declarations generally should be in the following order:
	// Typedefs and Enums
	// Constants (static const data members)
	// Constructors
	// Destructor
	// Methods, including static methods
	// Data Members (except static const data members)
	//
	// See all naming conventions

public:
	// Static constant members
	static const int kTemplateStaticConstantMember = 0;

	// Constructors
	TemplateClass ();
	// Other custom constructors with arguments
	// TemplateClass (__VA_ARGS__)

	// Copy constructor
	// Can miss if there is no pointer member
	// Can be declared as private if we want to avoid it completely
	TemplateClass (const TemplateClass& other);

	// Destructor
	~TemplateClass ();

	// Overload operator
	TemplateClass& operator = (const TemplateClass& other);

	// Methods
	// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Function_Parameter_Ordering
	//
	static void template_static_method ();

	void template_method ();

	// Avoid using public members

// protected: Ommit unused sections.

private:
	// Private constructors to avoid

	// Internal methods
	void clear_internal ();

	// Private members
	// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Initialization
	//
	int template_integer_member_ = -1;
	char* template_char_star_member_;
	void* template_generic_pointer_member_;
	int template_int_array_[100];
	TemplateClass* template_class_reference_member_;

	// Nested classes
};

// End header guard
#endif // TEMPLATE_CLASS_H_

