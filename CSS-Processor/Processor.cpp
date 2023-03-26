#include "Processor.h"

Processor::Processor()
{
    this->readMode = false;
    this->wasPreviousElementAttributeName = false;
    this->isInSection = false;
    this->isInBlock = false;
    this->prevAttributeName = " ";
}

Processor::~Processor()
{

}

void Processor::start()
{
    char c;
    char buffer[100];
    int counter = 0;
    bool endOfLine = false;
    bool ignoreNextSpace = false;
    bool ignoreSpacesUntilNextQuotationMark = false;

    while (c = getchar())
    {
        switch (c)
        {
            case '\n':
            {
                endOfLine = true;
                break;
            }
            case ',':
            {
                ignoreNextSpace = true;
                break;
            }
            case ' ':
            {
                if (ignoreSpacesUntilNextQuotationMark)
                    break;
                
                if (ignoreNextSpace)
                    ignoreNextSpace = false;
                else
                    endOfLine = true;
                
                break;
            }
            case '\"':
            {
                ignoreSpacesUntilNextQuotationMark = !ignoreSpacesUntilNextQuotationMark;
                break;
            }
            default:
            {
                ignoreNextSpace = false;
                break;
            }
        }

        if (endOfLine)
        {
            buffer[counter] = '\0';
            counter++;

            if (checkExtra(buffer, counter))
                readMode = !readMode;
            else
            {
                if (readMode)
                    interpretCommand(buffer, counter);
                else
                    interpretCSS(buffer, counter);
            }

            counter = 0;
            endOfLine = false;
            continue;
        }

        buffer[counter] = c;
        counter++;
    }
}

bool Processor::checkExtra(const char* text, int length)
{
    if (strcmp(text, "****") == 0 || strcmp(text, "????") == 0)
        return true;
    

    return false;
}

void Processor::interpretCSS(char* text, int length)
{
    if (this->isInSection)
    {
        if (this->isInBlock)
        {
            char* search = strchr(text, '}');
            if (search != NULL)
            {
                this->isInBlock = false;
                this->isInSection = false;
                *search = '\0';
            }

            if (this->wasPreviousElementAttributeName)
            {
                this->wasPreviousElementAttributeName = false;
                char* search = strchr(text, ';');
                if (search != NULL)
                    *search = '\0';
                
                this->list.last->attributes.add({ prevAttributeName, text });
            }
            else
            {
                checkAttribute(text, length);
            }
        }
        else
        {
            char* search = strchr(text, '{');
            if (search != NULL)
            {
                this->isInBlock = true;
                text++;
            }

            checkAttribute(text, length - 1);
        }
    }
    else
    {
        this->list.newNode();
        this->isInSection = true;
        char* search = strchr(text, ':');

        if (search != NULL)
        {
            this->prevAttributeName = text;
            this->isInBlock = true;
            this->wasPreviousElementAttributeName = true;
            *search = '\0';
        }
        else
        {
            this->list.last->selectors.add({ text });
        }
    }
}

void Processor::checkAttribute(char* text, int length)
{
    char* search = strchr(text, ':');
    if (search != NULL)
    {
        this->wasPreviousElementAttributeName = true;
        *search = '\0';
        this->prevAttributeName = text;
    }
}

void Processor::interpretCommand(char* text, int length)
{
    if (strcmp(text, "?") == 0)
    {
        for (int i = 0; i < list.numberOfNodes; i++)
        {
            ListNode* temp = list.getNode(i);
            std::cout << "Section nr. " << i << '\n';
            std::cout << "Selectors: " << temp->selectors.first->data[0] << '\n';
            ForwardListNode<Attribute>* attr = temp->attributes.first;
            for (int j = 0; j < (temp->attributes.numberOfElements / ForwardListNode<Attribute>::ARRAY_SIZE) + 1; j++)
            {
                for (int k = 0; k < attr->storedStructures; k++)
                {
                    std::cout << "Attribute: " << attr->data[k].name << " -> " << attr->data[k].value << '\n';
                }
                attr = attr->next;
            }
            std::cout << '\n';
        }
    }
}
