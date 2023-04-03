#include "Section.h"

void Section::print()
{
	ForwardListNode<String>* selec = this->selectors.first;
	while (selec != nullptr)
	{
		std::cout << "Selektor: " << selec->data << '\n';
		selec = selec->next;
	}

	ForwardListNode<Attribute>* attr = this->attributes.first;
	while (attr != nullptr)
	{
		std::cout << "Atrybut: " << attr->data.name << " -> " << attr->data.value << '\n';
		attr = attr->next;
	}
	std::cout << '\n';
}
