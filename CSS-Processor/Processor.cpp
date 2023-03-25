#include "Processor.h"

Processor::Processor()
{
    this->numberOfSections = 0;
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
    readCSS();
}

void Processor::stop()
{

}

void Processor::readCSS()
{
    char c;
    char buffer[100];
    int counter = 0;
    bool endOfLine = false;
    bool ignoreNextSpace = false;
    bool ignoreSpacesUntilNextQuotationMark = false;

    while (c = getchar())
    {
        if (c == '\n')
            endOfLine = true;
        else if (c == '\"')
        {
            ignoreSpacesUntilNextQuotationMark = !ignoreSpacesUntilNextQuotationMark;
        }
        else if (c == ' ' && !ignoreSpacesUntilNextQuotationMark)
        {
            if (ignoreNextSpace)
                ignoreNextSpace = false;
            else
                endOfLine = true;
        }
        else if (c == ',')
            ignoreNextSpace = true;

        if (endOfLine)
        {
            buffer[counter] = '\0';
            counter++;
            interpretCSS(buffer, counter);
            counter = 0;
            endOfLine = false;
            continue;
        }

        buffer[counter] = c;
        counter++;
    }
}

void Processor::interpretCSS(char* text, int length)
{
    if (this->isInSection)
    {
        if (this->isInBlock)
        {
            for (int i = 0; i < length; i++)
            {
                if (text[i] == '}')
                {
                    this->isInBlock = false;
                    this->isInSection = false;
                    text[i] = '\0';
                    break;
                }
            }

            if (this->wasPreviousElementAttributeName)
            {
                this->wasPreviousElementAttributeName = false;
                for (int i = 0; i < length; i++)
                {
                    if (text[i] == ';')
                    {
                        text[i] = '\0';
                        break;
                    }
                }

                std::cout << "Found attribute: " << this->prevAttributeName << " -> " << text << '\n';
            }
            else
            {
                checkAttribute(text, length);
            }
        }
        else
        {
            for (int i = 0; i < length; i++)
            {
                if (text[i] == '{')
                {
                    this->isInBlock = true;
                    text++;
                }
            }

            if (length > 1)
                checkAttribute(text, length - 1);
        }
    }
    else
    {
        bool foundColon = false;
        for (int i = 0; i < length; i++)
        {
            if (text[i] == ':')
            {
                foundColon = true;
                text[i] = '\0';
                break;
            }
        }

        if (foundColon)
        {
            this->prevAttributeName = text;
            this->isInSection = true;
            this->isInBlock = true;
            this->wasPreviousElementAttributeName = true;
        }
        else
        {
            std::cout << "Found selectors: " << text << '\n';
            this->isInSection = true;
        }
    }
}

void Processor::checkAttribute(char* text, int length)
{
    bool foundColon = false;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == ':')
        {
            foundColon = true;
            this->wasPreviousElementAttributeName = true;
        }
    }

    if (foundColon)
        this->prevAttributeName = text;
}