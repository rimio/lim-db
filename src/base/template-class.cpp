// File comments
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#File_Comments
//

#include "template-class.hpp"

// Other #includes
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Names_and_Order_of_Includes
//
#include <cstring>
#include <cassert>

// Define functions
// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Function_Declarations_and_Definitions
//

TemplateClass::TemplateClass ()
{
	// members initialized on declaration are not necessarily included here (but they can be)
	// try to avoid doing complex operations that can fail
	memset (template_int_array_, 0, sizeof (template_int_array_));

	template_char_star_member_ = NULL;
	template_generic_pointer_member_ = NULL;
	template_class_reference_member_ = NULL;
}

TemplateClass::TemplateClass(const TemplateClass& other)
{
	// Copy fields.
	template_integer_member_ = other.template_integer_member_;

	// DO not do this: template_char_star_member_ = other.template_char_star_member_;
	// Do something like this:
	// strcpy (template_char_star_member_, other.template_char_star_member_)

	// Do not do this: template_generic_pointer_member_ = other.template_generic_pointer_member_
	// Allocate and copy memory (length must be known)

	// Impossible to happen, but assert it anyway
	assert (this != other.template_class_reference_member_);

	// Now copy the reference. Allocate memory and use operator = to copy values.
	template_class_reference_member_ = new TemplateClass;
	*template_class_reference_member_ = *other.template_class_reference_member_;
}

TemplateClass::~TemplateClass ()
{
	// Clear resources
	clear_internal ();
}

TemplateClass& TemplateClass::operator= (const TemplateClass& other)
{
	if (this != &other)
	{
		// Clear current resources
		clear_internal ();

		// Non-pointer fields can be assigned directly
		template_integer_member_ = other.template_integer_member_;

		// Fixed-size arrays can be copied using memcpy
		memcpy (template_int_array_, other.template_int_array_, sizeof (template_int_array_));

		// Pointer cannot be assigned directly. They must be allocated and only its contents must be copied
		template_class_reference_member_ = new TemplateClass;
		*template_class_reference_member_ = *other.template_class_reference_member_;
	}
	return *this;
}

void TemplateClass::clear_internal ()
{
	delete template_char_star_member_;
	delete template_generic_pointer_member_;
	delete template_class_reference_member_;
}

void TemplateClass::template_static_method ()
{
	// Nothing really
}

void TemplateClass::template_method ()
{
	// Nothing really
}